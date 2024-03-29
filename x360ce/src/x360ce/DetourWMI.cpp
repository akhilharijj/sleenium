#include "stdafx.h"
#define CINTERFACE
#define _WIN32_DCOM
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <ole2.h>
#include <oleauto.h>
#include <detours.h>

#include "utils.h"

#include <dinput.h>
#include "directinput.h"

#define _CRT_SECURE_NO_DEPRECATE
#define _WIN32_DCOM

extern WORD wFakeAPI;

HRESULT ( STDMETHODCALLTYPE *OldGet )( 
									  IWbemClassObject * This,
									  /* [string][in] */ LPCWSTR wszName,
									  /* [in] */ long lFlags,
									  /* [unique][in][out] */ VARIANT *pVal,
									  /* [unique][in][out] */ CIMTYPE *pType,
									  /* [unique][in][out] */ long *plFlavor) = NULL;

HRESULT STDMETHODCALLTYPE NewGet( 
								 IWbemClassObject * This,
								 /* [string][in] */ LPCWSTR wszName,
								 /* [in] */ long lFlags,
								 /* [unique][in][out] */ VARIANT *pVal,
								 /* [unique][in][out] */ CIMTYPE *pType,
								 /* [unique][in][out] */ long *plFlavor)
{
	WriteLog(_T("NewGet"));
	HRESULT hr;
	hr = OldGet(This,wszName,lFlags,pVal,pType,plFlavor);

	//WriteLog(_T("wszName %s pVal->vt %d"),wszName,pVal->vt);

	//BSTR bstrDeviceID = SysAllocString( L"DeviceID" );

	if( pVal->vt == VT_BSTR && pVal->bstrVal != NULL )
	{
		//WriteLog(_T("%s"),pVal->bstrVal); 
		DWORD dwPid = 0, dwVid = 0;
		WCHAR* strVid = wcsstr( pVal->bstrVal, L"VID_" );
		if(strVid && swscanf_s( strVid, L"VID_%4X", &dwVid ) != 1)
			return hr;
		WCHAR* strPid = wcsstr( pVal->bstrVal, L"PID_" );
		if(strPid && swscanf_s( strPid, L"PID_%4X", &dwPid ) !=1 )
			return hr;

		for(int i = 0; i < 4; i++)
		{
			if(Gamepad[i].vid != 0 && Gamepad[i].vid == dwVid )
			{
				if(Gamepad[i].pid != 0 && Gamepad[i].pid == dwPid)
				{
					WCHAR* strUSB = wcsstr( pVal->bstrVal, L"USB" );
					WCHAR tempstr[MAX_PATH];
					if( strUSB )
					{
						BSTR fakebstr=NULL;
						WriteLog(_T("Old DeviceID = %s"),pVal->bstrVal);
						swprintf_s(tempstr,L"USB\\VID_%04X&PID_%04X&IG_00",
							(wFakeAPI>=2) ? Gamepad[i].vid : 0x045E,
							(wFakeAPI>=2) ? Gamepad[i].pid : 0x028E );
						fakebstr=SysAllocString(tempstr);
						//fakebstr=SysAllocString(L"USB\\VID_045E&PID_028E&IG_00");
						pVal->bstrVal = fakebstr;
						SysFreeString(fakebstr);
						WriteLog(_T("New DeviceID = %s"),pVal->bstrVal);
						return hr;
					}
					WCHAR* strHID = wcsstr( pVal->bstrVal, L"HID" );
					if( strHID )
					{
						BSTR fakebstr=NULL;
						WriteLog(_T("Old DeviceID = %s"),pVal->bstrVal);
						swprintf_s(tempstr,L"HID\\VID_%04X&PID_%04X&IG_00",
							(wFakeAPI>=2) ? Gamepad[i].vid : 0x045E,
							(wFakeAPI>=2) ? Gamepad[i].pid : 0x028E );
						fakebstr=SysAllocString(tempstr);
						//fakebstr=SysAllocString( L"HID\\VID_045E&PID_028E&IG_00" );
						pVal->bstrVal = fakebstr;
						SysFreeString(fakebstr);
						WriteLog(_T("New DeviceID = %s"),pVal->bstrVal);
						return hr;
					}

				}

			} 
		}
	}

	return hr;
}

HRESULT ( STDMETHODCALLTYPE *OldNext )( 
									IEnumWbemClassObject * This,
									/* [in] */ long lTimeout,
									/* [in] */ ULONG uCount,
									/* [length_is][size_is][out] */ __RPC__out_ecount_part(uCount, *puReturned) IWbemClassObject **apObjects,
									/* [out] */ __RPC__out ULONG *puReturned) = NULL;

HRESULT STDMETHODCALLTYPE NewNext( 
									IEnumWbemClassObject * This,
									/* [in] */ long lTimeout,
									/* [in] */ ULONG uCount,
									/* [length_is][size_is][out] */ __RPC__out_ecount_part(uCount, *puReturned) IWbemClassObject **apObjects,
									/* [out] */ __RPC__out ULONG *puReturned)
{
	WriteLog(_T("NewNext"));
	HRESULT hr;
    IWbemClassObject* pDevices;

	hr = OldNext(This,lTimeout,uCount,apObjects,puReturned);

	if(apObjects!=NULL)
	{
		if(*apObjects!=NULL)
		{
			pDevices = *apObjects;
			if(OldGet == NULL)
			{

				OldGet = pDevices->lpVtbl->Get;

				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&)OldGet, NewGet);
				DetourTransactionCommit();
			}
		}
	}

	return hr;
}

HRESULT ( STDMETHODCALLTYPE *OldCreateInstanceEnum )( 
	IWbemServices * This,
	/* [in] */ __RPC__in const BSTR strFilter,
	/* [in] */ long lFlags,
	/* [in] */ __RPC__in_opt IWbemContext *pCtx,
	/* [out] */ __RPC__deref_out_opt IEnumWbemClassObject **ppEnum) = NULL;

HRESULT STDMETHODCALLTYPE NewCreateInstanceEnum( 
	IWbemServices * This,
	/* [in] */ __RPC__in const BSTR strFilter, 
	/* [in] */ long lFlags,
	/* [in] */ __RPC__in_opt IWbemContext *pCtx,
	/* [out] */ __RPC__deref_out_opt IEnumWbemClassObject **ppEnum)
{
	WriteLog(_T("NewCreateInstanceEnum"));
	HRESULT hr;
	IEnumWbemClassObject* pEnumDevices = NULL;

	hr = OldCreateInstanceEnum(This,strFilter,lFlags,pCtx,ppEnum);

	if(ppEnum != NULL)
	{
		if(*ppEnum != NULL)
		{
			pEnumDevices = *ppEnum;

			if(OldNext == NULL) 
			{
				OldNext = pEnumDevices->lpVtbl->Next;

				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&)OldNext, NewNext);
				DetourTransactionCommit();
			}
		}
	}

	return hr;
}

HRESULT ( STDMETHODCALLTYPE *OldConnectServer )( 
	IWbemLocator * This,
	/* [in] */ const BSTR strNetworkResource,
	/* [in] */ const BSTR strUser,
	/* [in] */ const BSTR strPassword,
	/* [in] */ const BSTR strLocale,
	/* [in] */ long lSecurityFlags,
	/* [in] */ const BSTR strAuthority,
	/* [in] */ IWbemContext *pCtx,
	/* [out] */ IWbemServices **ppNamespace) = NULL;

HRESULT STDMETHODCALLTYPE NewConnectServer( 
	IWbemLocator * This,
	/* [in] */ const BSTR strNetworkResource,
	/* [in] */ const BSTR strUser,
	/* [in] */ const BSTR strPassword,
	/* [in] */ const BSTR strLocale,
	/* [in] */ long lSecurityFlags,
	/* [in] */ const BSTR strAuthority,
	/* [in] */ IWbemContext *pCtx,
	/* [out] */ IWbemServices **ppNamespace)

{
	WriteLog(_T("NewConnectServer"));
	HRESULT hr;
	IWbemServices* pIWbemServices = NULL;

	hr = OldConnectServer(This,strNetworkResource,strUser,strPassword,strLocale,lSecurityFlags,strAuthority,pCtx,ppNamespace);

	if(ppNamespace != NULL)
	{
		if(*ppNamespace != NULL)
		{
			pIWbemServices = *ppNamespace;

			if(OldCreateInstanceEnum == NULL) 
			{
				OldCreateInstanceEnum = pIWbemServices->lpVtbl->CreateInstanceEnum;

				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&)OldCreateInstanceEnum, NewCreateInstanceEnum);
				DetourTransactionCommit();
			}
		}
	}

	return hr;
}

HRESULT (WINAPI *OldCoCreateInstance)(__in     REFCLSID rclsid, 
						   __in_opt LPUNKNOWN pUnkOuter,
						   __in     DWORD dwClsContext, 
						   __in     REFIID riid, 
						   __deref_out LPVOID FAR* ppv) = CoCreateInstance;

HRESULT WINAPI NewCoCreateInstance(__in     REFCLSID rclsid, 
						   __in_opt LPUNKNOWN pUnkOuter,
						   __in     DWORD dwClsContext, 
						   __in     REFIID riid, 
						   __deref_out LPVOID FAR* ppv)
{
	HRESULT hr;
	IWbemLocator* pIWbemLocator = NULL;
/*
	LPOLESTR str1;
	StringFromIID(rclsid,&str1);
	WriteLog(_T("rclsid: %s"),str1);

	WriteLog(_T("dwClsContext: %d"),dwClsContext);

	LPOLESTR str2;
	StringFromIID(riid,&str2);
	WriteLog(_T("riid: %s"),str2);
*/
	hr = OldCoCreateInstance(rclsid,pUnkOuter,dwClsContext,riid,ppv);

	if(ppv != NULL && riid == IID_IWbemLocator) 
	{
		//WriteLog(_T("NewCoCreateInstance if1 "));

		pIWbemLocator = (IWbemLocator *) *ppv;
		if(pIWbemLocator != NULL) 
		{
			//WriteLog(_T("NewCoCreateInstance if2"));
			if(OldConnectServer == NULL) 
			{

				OldConnectServer = pIWbemLocator->lpVtbl->ConnectServer;

				DetourTransactionBegin();
				DetourUpdateThread(GetCurrentThread());
				DetourAttach(&(PVOID&)OldConnectServer, NewConnectServer);
				DetourTransactionCommit();
			}
		}
	}

	return hr;
}

void FakeWMI()
{
	WriteLog(_T("FakeWMI"));

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)OldCoCreateInstance, NewCoCreateInstance);
	DetourTransactionCommit();

}
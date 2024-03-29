#include "stdafx.h"
#include "globals.h"
#include "utils.h"

TCHAR tstrConfigFile[MAX_PATH];	
BOOL writelog = 0;
LPTSTR logfilename;
BOOL logready = 0;
TCHAR szProcessName[MAX_PATH] = _T("Unknown");

LPCTSTR PIDName(DWORD processID){

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,FALSE, processID );

	// Get the process name.

	if (NULL != hProcess )
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
			&cbNeeded) )
		{
			GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName)/sizeof(TCHAR) );
		}
	}
	CloseHandle(hProcess);
	return (szProcessName);
}

VOID GetTime(INT &year, INT &month, INT &day, INT &hour, INT &min, INT &sec ){
	{
		time_t rawtime;
		struct tm timeinfo;
		time ( &rawtime );
		localtime_s(&timeinfo,&rawtime);  

		year = timeinfo.tm_year+1900;
		month = timeinfo.tm_mon+1;
		day = timeinfo.tm_mday;
		hour = timeinfo.tm_hour;
		min = timeinfo.tm_min;
		sec = timeinfo.tm_sec;

	}
}

INT ReadFromFile(LPCTSTR strFileSection, LPCTSTR strKey, LPTSTR strOutput)
{
	return ReadFromFile(strFileSection, strKey, strOutput, NULL);
}

INT ReadFromFile(LPCTSTR strFileSection, LPCTSTR strKey, LPTSTR strOutput, LPTSTR strDefault)
{
	return GetPrivateProfileString(strFileSection, strKey, strDefault, strOutput, MAX_PATH, tstrConfigFile);
}
LPTSTR const DXErrStr(HRESULT dierr) {
	if (dierr == DIERR_ACQUIRED) return _T("DIERR_ACQUIRED");
	if (dierr == DI_BUFFEROVERFLOW) return _T("DI_BUFFEROVERFLOW");
	if (dierr == DI_DOWNLOADSKIPPED) return _T("DI_DOWNLOADSKIPPED");
	if (dierr == DI_EFFECTRESTARTED) return _T("DI_EFFECTRESTARTED");
	if (dierr == DI_NOEFFECT) return _T("DI_NOEFFECT");
	if (dierr == DI_NOTATTACHED) return _T("DI_NOTATTACHED");
	if (dierr == DI_OK) return _T("DI_OK");
	if (dierr == DI_POLLEDDEVICE) return _T("DI_POLLEDDEVICE");
	if (dierr == DI_PROPNOEFFECT) return _T("DI_PROPNOEFFECT");
	if (dierr == DI_SETTINGSNOTSAVED) return _T("DI_SETTINGSNOTSAVED");
	if (dierr == DI_TRUNCATED) return _T("DI_TRUNCATED");
	if (dierr == DI_TRUNCATEDANDRESTARTED) return _T("DI_TRUNCATEDANDRESTARTED");
	if (dierr == DI_WRITEPROTECT) return _T("DI_WRITEPROTECT");
	if (dierr == DIERR_ACQUIRED) return _T("DIERR_ACQUIRED");
	if (dierr == DIERR_ALREADYINITIALIZED) return _T("DIERR_ALREADYINITIALIZED");
	if (dierr == DIERR_BADDRIVERVER) return _T("DIERR_BADDRIVERVER");
	if (dierr == DIERR_BETADIRECTINPUTVERSION) return _T("DIERR_BETADIRECTINPUTVERSION");
	if (dierr == DIERR_DEVICEFULL) return _T("DIERR_DEVICEFULL");
	if (dierr == DIERR_DEVICENOTREG) return _T("DIERR_DEVICENOTREG");
	if (dierr == DIERR_EFFECTPLAYING) return _T("DIERR_EFFECTPLAYING");
	if (dierr == DIERR_GENERIC) return _T("DIERR_GENERIC");
	if (dierr == DIERR_HANDLEEXISTS) return _T("DIERR_HANDLEEXISTS");
	if (dierr == DIERR_HASEFFECTS) return _T("DIERR_HASEFFECTS");
	if (dierr == DIERR_INCOMPLETEEFFECT) return _T("DIERR_INCOMPLETEEFFECT");
	if (dierr == DIERR_INPUTLOST) return _T("DIERR_INPUTLOST");
	if (dierr == DIERR_INVALIDPARAM) return _T("DIERR_INVALIDPARAM");
	if (dierr == DIERR_MAPFILEFAIL) return _T("DIERR_MAPFILEFAIL");
	if (dierr == DIERR_MOREDATA) return _T("DIERR_MOREDATA");
	if (dierr == DIERR_NOAGGREGATION) return _T("DIERR_NOAGGREGATION");
	if (dierr == DIERR_NOINTERFACE) return _T("DIERR_NOINTERFACE");
	if (dierr == DIERR_NOTACQUIRED) return _T("DIERR_NOTACQUIRED");
	if (dierr == DIERR_NOTBUFFERED) return _T("DIERR_NOTBUFFERED");
	if (dierr == DIERR_NOTDOWNLOADED) return _T("DIERR_NOTDOWNLOADED");
	if (dierr == DIERR_NOTEXCLUSIVEACQUIRED) return _T("DIERR_NOTEXCLUSIVEACQUIRED");
	if (dierr == DIERR_NOTFOUND) return _T("DIERR_NOTFOUND");
	if (dierr == DIERR_NOTINITIALIZED) return _T("DIERR_NOTINITIALIZED");
	if (dierr == DIERR_OBJECTNOTFOUND) return _T("DIERR_OBJECTNOTFOUND");
	if (dierr == DIERR_OLDDIRECTINPUTVERSION) return _T("DIERR_OLDDIRECTINPUTVERSION");
	if (dierr == DIERR_OTHERAPPHASPRIO) return _T("DIERR_OTHERAPPHASPRIO");
	if (dierr == DIERR_OUTOFMEMORY) return _T("DIERR_OUTOFMEMORY");
	if (dierr == DIERR_READONLY) return _T("DIERR_READONLY");
	if (dierr == DIERR_REPORTFULL) return _T("DIERR_REPORTFULL");
	if (dierr == DIERR_UNPLUGGED) return _T("DIERR_UNPLUGGED");
	if (dierr == DIERR_UNSUPPORTED) return _T("DIERR_UNSUPPORTED");
	if (dierr == E_HANDLE) return _T("E_HANDLE");
	if (dierr == E_PENDING) return _T("E_PENDING");
	if (dierr == E_POINTER) return _T("E_POINTER");
	
	TCHAR *buffer = NULL;
	_itot_s(dierr,buffer,arrayof(buffer),16);	//as hex
	return buffer;	//return value of HRESULT

}

INT WriteLog(LPCTSTR str,...)
{
	if (writelog){
		INT year = 0;
		INT month = 0;
		INT day = 0;
		INT hour = 0;
		INT min = 0;
		INT sec = 0;

		GetTime(year, month, day, hour, min, sec );

		if(logready == 0){ // checking if file name for log is ready, if not create it
			logfilename = new TCHAR[MAX_PATH];
			_stprintf_s(logfilename,MAX_PATH,_T("x360ce_logs\\x360ce %d%02d%02d-%02d%02d%02d.log"),year,month,day,hour,min,sec);
			logready = 1;
		}

		if(GetFileAttributes(_T("x360ce_logs")) == INVALID_FILE_ATTRIBUTES) CreateDirectory(_T("x360ce_logs"), NULL);
		FILE * fp;
		_tfopen_s(&fp,logfilename,_T("a"));

		//fp is null, file is not open.
		if (fp==NULL)
			return -1;
		_ftprintf (fp,_T("%02d:%02d:%02d.%d:: "),hour,min,sec,GetTickCount());
		va_list arglist;
		va_start(arglist,str);
		_vftprintf(fp,str,arglist);
		va_end(arglist);
		fprintf(fp," \n");
		fclose(fp);

		return 0;
	}
	return -1;
}


LONG clamp(LONG val, LONG min, LONG max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
LONG deadzone(LONG val, LONG min, LONG max, LONG lowerDZ, LONG upperDZ) {
	if (val < lowerDZ) return min;
	if (val > upperDZ) return max;
	return val;

}
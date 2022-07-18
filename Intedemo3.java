package com.javasection;

public class Intedemo3 implements IntdeMo,INterdem2 {

	@Override
	public void studntdep(String r) {
		System.out.println("studnt dep:"+r);
		
		
	}

	@Override
	public void sudentNam(String k) {
		System.out.println("studnt name:"+k);
		
		
	}

	@Override
	public void sudentPhn(int p) {
		System.out.println("studnt numbr:"+p);
		
		
	}
	public static void main(String[] args) {
		Intedemo3 i=new Intedemo3();
		i.sudentNam("akhil");
		i.studntdep("cs");
		i.sudentPhn(9000);
	}

}

package com.javasection;

public class ConstrDEmo {

	public ConstrDEmo(String r) {
		System.out.println("studnt name:"+r);
		
	}
	public ConstrDEmo(int e) {
		System.out.println("student rollno:"+e);
		
	}
	public static void main(String[] args) {
		ConstrDEmo c=new ConstrDEmo(12);
		ConstrDEmo c1=new ConstrDEmo("akhil");
	}
	

}

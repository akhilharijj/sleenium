package com.javasection;

public class Multiple extends Inher2 {
	
	public void dep(String d) {
		System.out.println("departmnt:"+d);
		
	}
	public static void main(String[] args) {
		Multiple m=new Multiple();
		m.name("akhil");
		m.rollno(12);
		m.clss(12);
		m.dep("comptr  scince");
		
	}

}

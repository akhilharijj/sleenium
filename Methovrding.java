package com.javasection;

public class Methovrding {
	public void studentData(String n) {
		System.out.println("studnt name:"+n);
		
	}
	public void studentData(int r) {
		System.out.println("stdnt rollno:"+r);
		
	}
	public static void main(String[] args) {
		Methovrding m=new Methovrding();
		m.studentData("akhil");
		m.studentData(12);
	}

}

package com.javasection;

public class Methovri2 extends Methovrding{

	public void studentData(String n) {
		super.studentData(n);
		
	}
	public void studentData(int r) {
		super.studentData(r);
		
	}
	public static void main(String[] args) {
		Methovri2 m1=new Methovri2();
		m1.studentData("akhil");
		m1.studentData(2);
		m1.studentData(12);
		m1.studentData("sai");
	}
}


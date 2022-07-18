package com.javasection;

public class Absdemo2 extends Abstrdemo {

	@Override
	public void rollno(int t) {
		System.out.println("studnt rollno:"+t);
		
		
	}

	@Override
	public void dept(String d) {
		System.out.println("studnt dep:"+d);
		
		
	}
	public static void main(String[] args) {
		Absdemo2 s= new Absdemo2();
		s.name("akhil");
		s.rollno(12);
		s.dept("comptsc");
	}

}

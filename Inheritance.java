package com.javasection;

public class Inheritance {
	public  void name(String r) {
		System.out.println("studnt name :"+r);
		
	}
	public void rollno(int i) {
		System.out.println("stdnt id:"+i);
		
	}
	public static void main(String[] args) {
		Inheritance h=new Inheritance();
		h.name("akhil");
		h.rollno(12);
	}

}

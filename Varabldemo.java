package com.javasection;

public class Varabldemo {
	int a=10;//cls varaible
	
	public void name() {
		int b=20;//method variable
		System.out.println(b);
		System.out.println(a);
		
		
		
		
	}
	static int c=40;//static varaible
	
	public static void main(String[] args) {
		Varabldemo v=new Varabldemo();
		v.name();
		System.out.println(c);
		
	}

}

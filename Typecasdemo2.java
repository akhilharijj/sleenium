package com.javasection;

//narrowing type casting

public class Typecasdemo2 {
	public static void main(String[] args) {
		double d=10.9;
		float f=(float)d;
		int i=(int)f;
		System.out.println("double value:"+d);
		System.out.println("int value changed:"+i);
		System.out.println("float value changed:"+f);
	}

}

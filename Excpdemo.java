package com.javasection;

public class Excpdemo {
	public static void main(String[] args) {
		System.out.println("start");
		System.out.println("1");
		System.out.println("2");
		System.out.println("3");
		try {
			System.out.println(10/0);
		}
		catch(ArithmeticException e) {
			System.out.println("dont/by zero");
		}
		finally {
			System.out.println("final");
		}
		System.out.println("end");
	}

}

package com.javasection;

import java.util.Scanner;

public class Scandemo {
	public static void main(String[] args) {
		Scanner s= new Scanner(System.in);
		System.out.println("enter the name");
		String s1=s.nextLine();
		System.out.println("enter the id");
		int s2=s.nextInt();
		System.out.println("enter the perctage");
		float s3=s.nextFloat();
		System.out.println("enter the lastname");
		String s4=s.next().concat(s1);
	}

}

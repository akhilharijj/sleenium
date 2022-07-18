package com.javasection;

public class StrinTYpDemo {
	public static void main(String[] args) {
		String s1="akhil";
		String s2="harii";
		int length=s1.length();
		System.out.println("charlength:"+length);
		boolean equals=s1.equalsIgnoreCase(s2);
		System.out.println("equals:"+equals);
		String[] cha=s1.split("");
		for(String string:cha) {
			System.out.println(string);
			
		}
		
		
		boolean dd=s1.startsWith(s1);
		System.out.println(dd);
		
	}

}

package com.javasection;

public class Stringdemo {
	public static void main(String[] args) {
		String s1="akhil";
		String s2="akhil";
		
		//it will share the duplicate value but concordination create new memory
		System.out.println("Immutable");
		System.out.println(System.identityHashCode(s1));
		System.out.println(System.identityHashCode(s2));
		String r=s1.concat(s2);
	System.out.println(r);
	System.out.println(System.identityHashCode(r));
	
	//duplicate will create new memory nd concordition will share the memory
	//string buffer nd string builder can be used
	
	     StringBuffer s=new StringBuffer("akhil");
	     StringBuffer g=new StringBuffer("akhil");
	      System.out.println(" ");
	      System.out.println("mutable");
	      System.out.println(System.identityHashCode(s));
	      System.out.println(System.identityHashCode(g));
	      s.append(g);
	      System.out.println(g);
	      System.out.println(System.identityHashCode(g));
		
	}

}

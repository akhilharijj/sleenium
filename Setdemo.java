package com.javasection;

///set 

import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;

public class Setdemo {
	public static void main(String[] args) {
		Set<Integer> e=new TreeSet<Integer>();
		e.add(20);
		e.add(20);
		e.add(40);
		e.add(50);
		//e.add(null);
		int i=e.size();
		System.out.println(e);
		System.out.println(i);
	}

}

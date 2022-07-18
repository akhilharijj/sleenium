package com.javasection;
///list

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Vector;

public class Collectiodemo {
	public static void main(String[] args) {
		List<Integer> e=new LinkedList<Integer>();
		e.add(10);
		e.add(20);
		e.add(30);
		e.add(40);
		e.set(1, 200);
		//e.clear();
		e.get(4);
		int i=e.size();
		System.out.println(i);
		System.out.println(e);
	}

}

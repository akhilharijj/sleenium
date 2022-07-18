package com.javasection;

import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

public class Mapdemo {
	public static void main(String[] args) {
		Map<String, Integer> m=new TreeMap<String,Integer>();
		m.put("bsc",23);
		m.put("ma",22);
		//m.put(null, null);
		System.out.println(m);
	}

}

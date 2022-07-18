package com.javasection;

import java.util.Arrays;

public class Array22demo {
	public static void main(String[] args) {
		int num[]=new int[4];
		 num[0]=10;
		 num[1]=20;
		 num[2]=30;
		 num[3]=40;
		 System.out.println(num[3]);
		
		 //to print in straight line in index based
		 int len=num.length;
		 
		 //to print straight line
		 for(int j:num) {
			 System.out.println(j);
		 }
		 //to print in straight line in index based
		 System.out.println(Arrays.toString(num));
		 
		
		
	}

}

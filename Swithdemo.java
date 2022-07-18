package com.javasection;

import java.util.Scanner;

public class Swithdemo {
	public static void main(String[] args) {
		Scanner s=new Scanner(System.in);
		for(int i=0;i<=4;i++) {
			System.out.println("colleges depatmnt");
			int college=s.nextInt();
			switch(college) {
			case 1:
				System.out.println("bsc");
				break;
			
			case 2:
				System.out.println("bcom");
				break;
			case 3:
				System.out.println("ba");
				break;
			case 4:
				System.out.println("ma");
				break;
				default :
					System.out.println("there is no depmnt");
					continue;
				
			}
		}
		
		
	}

}

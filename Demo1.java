package com.javasection;

public class Demo1 {
       public void name()
       {
    	   System.out.println("akhil");
       }

       public void roll(int i) {
    	   System.out.println("student id:"+i);
		
	}
       public static void main(String[] args) {
		Demo1 d=new Demo1();
		d.name();
		d.roll(12);
	}
}

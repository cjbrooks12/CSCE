//CSCE 111, Chapter 4, Problem 6

import java.util.*;
import java.text.*;
class Ch4pr06 {
	public static void main(String[] args) {
	
		Scanner scanner;
		scanner = new Scanner(System.in);
		
		//Input the number of tickets sold for each section
		int numberOfA_Seats, numberOfB_Seats, numberOfC_Seats;
			System.out.println("Please enter the number of A tickets sold: ");
				numberOfA_Seats = scanner.nextInt( );
			System.out.println("Please enter the number of B tickets sold: ");
				numberOfB_Seats = scanner.nextInt( );
			System.out.println("Please enter the number of C tickets sold: ");
				numberOfC_Seats = scanner.nextInt( );
				
		//Input the price per ticket for each section in dollars and cents (e.g., 12.50)
		double pricePerA_Seat, pricePerB_Seat, pricePerC_Seat, totalSales;
			System.out.println("Please enter the price per section A ticket: ");
				pricePerA_Seat = scanner.nextDouble( );
			System.out.println("Please enter the price per section B ticket: ");
				pricePerB_Seat = scanner.nextDouble( );
			System.out.println("Please enter the price per section C ticket: ");
				pricePerC_Seat = scanner.nextDouble( );
			
		//Calculate the total sales
		totalSales = 	numberOfA_Seats * pricePerA_Seat + 
						numberOfB_Seats * pricePerB_Seat + 
						numberOfC_Seats * pricePerC_Seat;
						
		//Output the total sales in dollar format
		DecimalFormat df = new DecimalFormat("0.00");
		System.out.print("$ " + df.format(totalSales));
		
	}
}
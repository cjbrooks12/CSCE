//package myutil;
import java.util.*;
public class Balance {
	
	//Data values
	Scanner scanner = new Scanner(System.in);
	int add = 0;
	int balance = 0;
	int balanceTest = 0;
	int subtract = 0;
	int initialBalance = 0;
	
	//Constructor
	public Balance( ) {
		System.out.println("A standard card is issued with 100 points. Would you like to get a card with a different number of points? [Enter 1 for yes, 0 for no]: ");
		initialBalance = scanner.nextInt( );
		if (initialBalance == 1) {
			System.out.println("Please enter how many points you would like: ");
			balance = scanner.nextInt( );
		}
		else {
			balance = 100;
		}
		System.out.println("You now have a meal card with " + balance + " points.");
	}
	
	public void add( ) {
		System.out.println("Please enter how many points you would like to add: ");
		add = scanner.nextInt( );
		balance = balance + add;
		System.out.println("You added " + add + " points and have " + balance + " points remaining.");
	}
		
	public void food( ) {
		System.out.println("Please enter how many points your food purchase is: ");
		subtract = scanner.nextInt( );
		balanceTest = balance - subtract;
		if (balanceTest < 0){
			System.out.println("Insufficient funds, transction declined. Item costs " + subtract + " points, but you only have " 
								+ balance + " points in your account.");
		}
		else {
			balance = balance - subtract; 
			System.out.println("You spent " + subtract + " points and have " + balance + " points remaining.");
		}
	}
	
	public void getBalance( ) {
		System.out.println("You have " + balance + " points remaining.");
	}
	
}
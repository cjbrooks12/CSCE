import java.util.*;
class Ch5pr12 {
	public static void main(String[] args) {
	
	System.out.println("Please enter a year, to test if it is a leap year.");
	Scanner scanner = new Scanner(System.in);
	int year, a, b, c;
	year = scanner.nextInt();
	
	a = year % 4;
	b = year % 100;
	c = year % 400;
	
	if (a == 0) {
		if (b == 0) {
			if (c == 0)
				System.out.println("The year " + year + "is a leap year.");
			else
				System.out.println("The year " + year + " is not a leap year.");
		}
		else
				System.out.println("The year " + year + " is a leap year.");
	}

	else
		System.out.println("The year " + year + "is a not leap year.");
	
	}
}
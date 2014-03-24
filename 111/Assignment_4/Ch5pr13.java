import java.util.*;
import java.text.*;
class Ch5pr13 {
	public static void main(String[] args) {
	
	//Create and define variables used
	System.out.println("Please enter the number of hours worked: ");
	Scanner scanner = new Scanner(System.in);
	int hours, overtime, output;
		hours = scanner.nextInt( );
		overtime = 0;
		output = 0;
	System.out.println("Please enter the total(in USD) in sales: ");
	double sales, wage, commission, earnings;
		sales = scanner.nextDouble( );
		wage = 0;
		commission = 0;
		earnings = 0;
	DecimalFormat df = new DecimalFormat("0.00");
	
	//Calculate the total earned based on number of hours worked
	overtime = hours - 40;
	if (hours >= 0 && hours <= 40)
		wage = hours * 7.25;
	else if (hours > 40)
		wage = ((hours - overtime) * 7.25) + (overtime * 10.875);
	else {
		System.out.print("Hours: Invalid input. ");
		output = 1;
	}
		
	//Calculate the total earned based on sales commission
	if (sales >= 1.00 && sales < 100.00)
		commission = sales * 0.05;
	else if (sales >= 100.00 && sales < 300.00)
		commission = sales * 0.10;
	else if (sales >= 300.00)
		commission = sales * 0.15;
	else {
		System.out.print("Sales: Invalid input. ");
		output = 1;
	}
	
	//Output
	if (output == 1) 
		System.out.print("Please reenter data.");
	else	{
		earnings = wage + commission;
		System.out.println("You worked " + hours + " hours and earned $" + wage + " in hourly wages.");
		System.out.println("You sold $" + sales + " and earned $" + commission + " in commission.");
		System.out.println("You made $" + df.format(earnings) + " in total earnings.");
	}
	
	}
}
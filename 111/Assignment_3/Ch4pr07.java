import java.util.*;
class Ch4pr07 {
	public static void main(String[] args) {
	
	//Initialize all variables and creates a scanner
	Temperature temp1 = new Temperature( );	
	Scanner scanner = new Scanner(System.in);
	double temp2;
	
	System.out.println("Please enter the temperature in farenheit");
	temp1.setFarenheit(scanner.nextDouble( ));
	temp2 = temp1.toCelsius( );
	System.out.println(temp2 + " degrees celsius");
	}
}
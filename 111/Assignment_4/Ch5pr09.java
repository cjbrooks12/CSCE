import java.util.*;
class Ch5pr9 {
	public static void main(String[] args) {
	
	System.out.println("Please enter a power of ten as an integer");
	Scanner scanner = new Scanner(System.in);
	int power = scanner.nextInt();

	if (power >= 6 && power <9) 
		System.out.println("Million");
		
	else if (power >= 9 && power <12) 
		System.out.println("Billion");
		
	else if (power >= 12 && power <15) 
		System.out.println("Trillion");
	
	else if (power >= 15 && power <18) 
		System.out.println("Quadrillion");
	
	else if (power >= 18 && power <21) 
		System.out.println("Quintillion");
		
	else if (power >= 21 && power <30) 
		System.out.println("Sextillion");
	
	else if (power >=30 && power <100) 
		System.out.println("nonillion");
	
	else if (power >= 100) 
		System.out.println("Googol");
		
	else 
		System.out.println("Invalid selection");
	}
}
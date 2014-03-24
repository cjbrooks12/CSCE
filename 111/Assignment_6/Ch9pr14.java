import java.util.*;
import java.lang.*;
class Ch9pr14 { 
	private static Scanner scanner = new Scanner(System.in);
	public static void main(String[] args) {
	System.out.println("Please enter a string, which you wish to know the count of all uppercase characters in the string: ");
		start( );
	}
	
	private static void start( ) {
		String str = scanner.nextLine( );
		test(str);
		System.out.println("To test another string, type in a new string. To exit, hit [ENTER].");
			if (str.length( ) == 0){
			}
			else { 
				start( );
			}
	}
	
	private static void test(String str) {	
		int upperCount = 0;
		for (int i = 0; i < str.length( ); i++) {
			char letter = str.charAt(i);			
			if (testForUpperCase(letter) == true) {
				upperCount++;
			}
			else if (testForUpperCase(letter) == false) {
			}
		}
		System.out.println("# of capital letters: " + upperCount);
	}
	
	private static boolean testForUpperCase(char letter){ 
	
		if (letter >= 65 && letter <= 90) {
			return true;
		}
		else {
			return false;
		}	
	}
}
import java.util.*;
class Ch9pr11 {	

	private static Scanner scanner = new Scanner(System.in);
	public static void main(String[] args) {
	System.out.println("Please enter a string, which you wish to know the count of all lowercase vowels in the string: ");
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
		char letter;
		int aCount = 0;
		int eCount = 0;
		int iCount = 0;
		int oCount = 0;
		int uCount = 0;
			
		for (int i = 0; i < str.length( ); i++) {
			letter = str.charAt(i);
			
			if (letter == 'a') {
				aCount++;
			}
			else if (letter == 'e') {
				eCount++;
			}
			else if (letter == 'i') {
				iCount++;
			}
			else if (letter == 'o') {
				oCount++;
			}
			else if (letter == 'u') {
				uCount++;
			}
		}
		
		System.out.println("# of 'a' : " + aCount);
		System.out.println("# of 'e' : " + eCount);
		System.out.println("# of 'i' : " + iCount);
		System.out.println("# of 'o' : " + oCount);
		System.out.println("# of 'u' : " + uCount);
	}
}
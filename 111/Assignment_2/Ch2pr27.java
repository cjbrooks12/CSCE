// CSCE 111, Chapter 2, Problem 27

import java.util.*; 
import javax.swing.*;
class Ch2pr27 {
	public static void main(String[] arg) {
		Scanner scanner;
		scanner = new Scanner(System.in);
		
		String lineSeparator = System.getProperty("line.separator");
			scanner.useDelimiter(lineSeparator);
			
		String string1, string2, string3;
			System.out.print("Please enter anything: ");
			string1 = scanner.next();
			string2 = string1.substring(0, 1);
			string3 = string1.substring(string1.length( ) - 1, string1.length( ));
			
		System.out.println(string1.length( ));	
		System.out.println(string2);
		System.out.println(string3);
	}
}
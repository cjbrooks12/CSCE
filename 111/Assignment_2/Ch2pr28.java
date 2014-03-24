// CSCE 111, Chapter 2, Problem 28

import java.util.*; 
import javax.swing.*;
class Ch2pr28 {
	public static void main(String[] arg) {
		Scanner scanner;
		scanner = new Scanner(System.in);
		
		String lineSeparator = System.getProperty("line.separator");
			scanner.useDelimiter(lineSeparator);
			
		String string1, string2, string3;
			System.out.print("Please enter a single word: ");
			string1 = scanner.next();
			System.out.print(string1.substring(string1.length( ) / 2, string1.length( ) / 2 + 1));
	}
}
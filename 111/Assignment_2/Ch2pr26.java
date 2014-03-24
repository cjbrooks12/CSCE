// CSCE 111, Chapter 2, Problem 26

import java.util.*; 
import javax.swing.*;
class Ch2pr26 {
	public static void main(String[] arg) {
		Scanner scanner;
		scanner = new Scanner(System.in);
		
		String lineSeparator = System.getProperty("line.separator");
			scanner.useDelimiter(lineSeparator);
			
		String string1, string2, string3;
			System.out.print("Please enter anything, adding a single exclaimation mark wherever you would like: ");
			string1 = scanner.next();
			
		string2 = string1.substring(0, string1.indexOf("!"));
			System.out.println(string2);			
		string3 = string1.substring(string1.indexOf("!") + 1, string1.length( ));
			System.out.println(string3);
	}
}
// CSCE 111, Chapter 2, Problem 18

import java.util.*; 
import javax.swing.*;
class Ch2pr18 {
	public static void main(String[] arg) {
		Scanner scanner;
		scanner = new Scanner(System.in);
		String firstName, lastName;
			System.out.print("Please enter your first name: ");
			firstName = scanner.next( );
	
			System.out.print("Please enter your last name: ");
			lastName = scanner.next( );
			
		JFrame window;
			window = new JFrame();
			window.setSize(300, 200);
			window.setTitle(lastName + ", " + firstName);
			window.setVisible(true);
	}
}
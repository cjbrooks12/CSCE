import java.util.*;
public class Hangman {
	public static void main(String[] args) {
		Hangman hangman = new Hangman( );
		hangman.start( );
	}

	public Hangman( ) {
	}
	
	private void start( ) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Let's play hangman! Enter a phrase to be guessed.");
		String word = scanner.nextLine( );
		System.out.println(word);
		
		String[ ][ ] letter = new String[word.length( )][2];
		for (int i = 0; i < word.length( ); i++) {
			letter[i][0] = word.substring(i,i + 1);
			letter[i][1] = null;
			System.out.print(letter[i][0] + " ");
			System.out.println(letter[i][1]);
			
		}
		
		
		
		
	}
}
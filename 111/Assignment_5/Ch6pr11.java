import java.util.*;
class Ch6pr11 {
	private static enum Response {YES, NO}
	
	//Data members
	private Scanner scanner;
	private final int MAX_GUESSES_ALLOWED = 6;
	private int LOWER_BOUND;
	private int UPPER_BOUND;
	private int secretNumber;
	private Random random;
	
	public static void main(String[] args) {
		HiLo game = new HiLo( );
		game.start( );
	}
	
	//Constructor
	public HiLo( ) {
		scanner = new Scanner(System.in);
		random = new Random( );
	}
	
	public void start( ) {
		Response answer;
		describeRules( );
		answer = prompt("Do you want to play a game of Hi-Lo?");
		while (answer == Response.YES) {
			setBounds( );
			generateSecretNumber( );
			playGame( );
			answer = prompt("Do you want to play another game of Hi-Lo?");
		}
		System.out.println("Thank you for playing Hi-Lo!");
	}
	
	//Describes the rules to the user. Will only be shown once, not every time a user wants to play again.
	private void describeRules( ) {
		System.out.println("You will be asked to enter a lower bound and an upper bound to play with. The computer will generate a random number " + 
							"between the two set bounds, and you will be given 6 tries to guess the number. Each time the computer will give you a hint, " + 
							"telling you whether your guess is too high or too low.");
	}
	
	//Lets the user set the bounds of play.
	private void setBounds( ) {
		System.out.println("Enter a value for the lower bound: ");
			LOWER_BOUND = scanner.nextInt( );
			System.out.println("Lower bound is set to " + LOWER_BOUND);
		System.out.println("Enter a value for the upper bound: ");
			UPPER_BOUND = scanner.nextInt( );
			System.out.println("Upper bound is set to " + UPPER_BOUND);
	}
	
	//Generates the secret number
	private void generateSecretNumber( ) {
		secretNumber = random.nextInt(UPPER_BOUND - LOWER_BOUND + 1) + LOWER_BOUND;
			//System.out.println("Secret Number: " + secretNumber);
	}
	
	//Plays te game
	private void playGame( ) {
		int guessCount = 0;
		int guess;
		
		do {
			//Get the next guess
			guess = getNextGuess( );
			guessCount++;
			
			//Check the guess
			if (guess < secretNumber) {
				System.out.println("Your guess is too low");
			}
			else if (guess > secretNumber) {
				System.out.println("Your guess is too high");
			}
		}
		while (guessCount < MAX_GUESSES_ALLOWED && guess != secretNumber);
		
		//output appropriate message
		if (guess == secretNumber) {
			System.out.println("You guessed the number in " + guessCount + " tries");
		}
		else {
			System.out.println("You lost, the secret number was " + secretNumber);
		}
	}
	
	//Prompts the user to input their next guess.
	private int getNextGuess( ) {
		int input;
		while (true) {
			System.out.print("Next guess: ");
			input = scanner.nextInt( );
			
			if (LOWER_BOUND <= input && input <= UPPER_BOUND) {
				return input;
			}
			System.out.println("Invalid input. Must be between " + LOWER_BOUND + " and " + UPPER_BOUND);
			}
		}

	//Prompts player to play a game.
	private Response prompt(String question) {
		String input;
		Response response = Response.NO;
		System.out.print(question + " (Yes - y; No - n): ");
		input = scanner.next( );
		if (input.equals("Y") || input.equals("y")) {
			response = Response.YES;
		}
		return response;
	}
}
import java.util.*;
public class Towers_of_Hanoi {
	public static void main(String[] args) {
		Towers_of_Hanoi game = new Towers_of_Hanoi( );
		game.startGame( );
	}
	public Towers_of_Hanoi() {	
	}

	public void startGame( ) {
		initialize( );
	}
	
	private void initialize( ) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("[Enter how many discs you want to play with, from 3 to 7]");
		try {
			//creates three towers of an input size
			int numberOfDiscs = scanner.nextInt( );
			if (numberOfDiscs >= 3 && numberOfDiscs <= 7) {
				int[ ] tower1 = new int[numberOfDiscs];
				for (int i = 0; i < numberOfDiscs; i++) {
					int j = 1 + i;
					tower1[i] = j;
			
				}
				int[ ] tower2 = new int[numberOfDiscs];
				int[ ] tower3 = new int[numberOfDiscs];
				for (int i = 0; i < numberOfDiscs; i++) {
					tower2[i] = 0;
					tower3[i] = 0;
				}
				//Print out the values of the three towers
				output(numberOfDiscs, tower1, tower2, tower3);
				playGame(numberOfDiscs, tower1, tower2, tower3);
			}
			else {
				startGame( );
			}
		}
		catch (InputMismatchException e) {
			System.out.println("Please enter integer values only.");
			startGame( );
		}
	}
	
	private void playGame(int numberOfDiscs, int[ ] tower1, int[ ] tower2, int[ ] tower3) {
		Scanner scanner = new Scanner(System.in);
		int indexOfMinimum_from = 0;
		int indexOfMinimum_to = 0;
		//Selects the tower to move a disc from. Calls and indexes the smallest(lowest number) disc for whichever tower is chosen.
		System.out.println("select a tower to move from: ");
		int from = scanner.nextInt( );
		if (from == 1) {
			indexOfMinimum_from = findSmallest(tower1);
		}
		else if (from == 2) {
			indexOfMinimum_from = findSmallest(tower2);
		}
		else if (from == 3) {
			indexOfMinimum_from = findSmallest(tower3);
		}
		else {
		}
		//Selects the tower to move a disc to, Indexes the smallest disc on that tower.
		int to = scanner.nextInt( );
		if (to == 1 && to != from) {
			indexOfMinimum_to = findSmallest(tower1);
		}
		else if (to == 2 && to != from) {
			indexOfMinimum_to = findSmallest(tower2);
		}
		else if (to == 3 && to != from) {
			indexOfMinimum_to = findSmallest(tower3);
		}
		else {
		}
		//moves a disc from the "from" tower to the "to" tower
		System.out.println("from tower: " + indexOfMinimum_from + " " + tower1[indexOfMinimum_from]);
		System.out.println("to tower: " + indexOfMinimum_to + " " + tower3[indexOfMinimum_to]);
	}
	
	private int findSmallest(int[ ] tower) {
		int length = tower.length;
		int indexOfMinimum = 0;
		for (int i = 0; i < length; i++) {
			if (tower[i] < tower[indexOfMinimum]) {
				indexOfMinimum = i;
			}
		}
		return indexOfMinimum;
	}
	
	private void output(int numberOfDiscs, int[ ] tower1, int[ ] tower2, int[ ] tower3) {
		for (int i = 0; i < numberOfDiscs; i++) {
			if (i == 0) System.out.println("Tower 1   " + "Tower 2   " + "Tower 3");
			System.out.print(tower1[i] + "         ");
			System.out.print(tower2[i] + "         ");
			System.out.print(tower3[i] + "         ");
			System.out.println("");
		}
	} 
}
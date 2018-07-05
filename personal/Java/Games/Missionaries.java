import java.util.*;
public class Missionaries {
	public static void main(String[] args) {
		Missionaries game = new Missionaries( );
		game.start( );
	}
	
	public Missionaries( ) {
	}

	private void start( ) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Let's play a game of Missionaries and Cannibals. Do you want to see the rules? [Y/N]");
		String answer = scanner.next( );
		if (answer.equals("Y") || answer.equals("y")) {
			System.out.println("A group of missionaries has landed on a remote island with the intent to share the ");
			System.out.println("love of Jesus with the natives. However, the natives prove to be particularly hostile ");
			System.out.println("to the missionaries, to the point of trying to kill and eat them. But the missionaries ");
			System.out.println("can't give up, and so have decided to take a few natives back to base camp on the other ");
			System.out.println("side of the river.");
			System.out.println("");
			System.out.println("There are three missionaries and three cannibals that need to cross the river, from ");
			System.out.println("the west bank to the east bank, by means of a small boat. The boat can only hold two ");
			System.out.println("people or else it will sink, and it must be operated by at least 1 person, either ");
			System.out.println("missionary or cannibal. In addition, the hostility of the cannibals can only be kept ");
			System.out.println("in check if there are as many or more missionaries than there are cannibals on each ");
			System.out.println("side of the river. Your job is to get everyone safely across the river.");
			System.out.println("");
			System.out.println("Let's Begin!");
			scanner.close( );
			begin(3,0,3,0,0);
		}
		else {
			System.out.println("");
			System.out.println("Let's Begin!");
			scanner.close( );
			begin(3,0,3,0,0);
		}
	}
	
	//Value of each category indicates how many of that type are presently on shore. This accounts for who in in the boat.
	//The value of bank determines which shore the boat is currently on. 0 = west shore, 1 = east shore.
	private void begin(int missionaries_west, int missionaries_east, int cannibals_west, int cannibals_east, int bank) {
		Scanner scanner = new Scanner(System.in);
		String[ ] boat = new String[2]; 
		
		System.out.println("");
		System.out.println("You have " + missionaries_west + " missionaries and " + cannibals_west + " cannibals on the west bank.");
		System.out.println("You have " + missionaries_east + " missionaries and " + cannibals_east + " cannibals on the east bank.");
		//if boat is on western shore
		if (bank == 0) {
			System.out.println("The boat is currently on the western shore.");
			System.out.println("Who would you like to put in the boat first? [M]issionary, [C]annibal");		
			boat[0] = scanner.next( ); 
			System.out.println("Who would you like to put in the boat second?  [M]issionary, [C]annibal, [E]mpty");
			boat[1] = scanner.next( );
			
			//Prints out the state of the system before the boat has left. Includes how many are on the western bank and in the boat
			if (boat[0].equals(boat[1]) && boat[0].equals("M")) {
				if (missionaries_west >= 2 && missionaries_west <= 3) {
					missionaries_west--;
					missionaries_west--;
					System.out.print("Boat is on the western shore with two missionaries.");
				}
				else {
					System.out.println("You don't have that many missionaries on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[0].equals(boat[1]) && boat[0].equals("C")) {
				if (cannibals_west >= 2 && cannibals_west <= 3) {
					cannibals_west--;
					cannibals_west--;
					System.out.print("Boat is on the western shore with two cannibals.");
				}
				else {
					System.out.println("You don't have that many cannibals on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[0].equals("M") && !(boat[0].equals(boat[1]))) {
				if (missionaries_west >= 1 && missionaries_west <= 3) {
					missionaries_west--;
					System.out.print("Boat is on the western shore with a missionary ");
				}
				else {
					System.out.println("You don't have that many missionaries on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[0].equals("C") && !(boat[0].equals(boat[1]))) {
				if (cannibals_west >= 1 && cannibals_west <= 3) {
					cannibals_west--;
					System.out.print("Boat is on the western shore with a cannibal ");
				}
				else {
					System.out.println("You don't have that many cannibals on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[1].equals("M") && !(boat[0].equals(boat[1]))) {
				if (missionaries_west >= 1 && missionaries_west <= 3) {
					missionaries_west--;
					System.out.print("and a missionary.");
				}
				else {
					System.out.println("You don't have that many missionaries on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[1].equals("C") && !(boat[0].equals(boat[1]))) {
				if (cannibals_west >= 1 && cannibals_west <= 3) {
					cannibals_west--;
					System.out.print("and a cannibal.");
				}
				else {
					System.out.println("You don't have that many cannibals on the west bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[1].equals("E")) {
				System.out.print("by himself.");
			}
			
			if (cannibals_west > missionaries_west && missionaries_west != 0) {
				System.out.println("");
				System.out.println("You have " + missionaries_west + " missionaries and " + cannibals_west + " cannibals on the west bank.");
				System.out.println("Moving the boat now would make more cannibals than missionaries. Please choose again.");
				if (boat[0].equals("M")) {
					missionaries_west++;
				}
				else if (boat[0].equals("C")) {
					cannibals_west++;
				}
				if (boat[1].equals("M")) {
					missionaries_west++;
				}
				else if (boat[1].equals("C")) {
					cannibals_west++;
				}
				begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
			}
			else {
				System.out.println("");
				System.out.println("You have " + missionaries_west + " missionaries and " + cannibals_west + " cannibals on the west bank.");
				System.out.println("Boat is ready to move on.");
				if (boat[0].equals("M")) {
					missionaries_east++;
				}
				else if (boat[0].equals("C")) {
					cannibals_east++;
				}
				if (boat[1].equals("M")) {
					missionaries_east++;
				}
				else if (boat[1].equals("C")) {
					cannibals_east++;
				}
				bank = 1;
				if (missionaries_east == 3 && cannibals_east == 3 && bank == 1) {
					end( );
					scanner.close( );
					return;
				}
				else {
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
		}
		//if boat is on eastern shore
		if (bank == 1) {
			System.out.println("The boat is currently on the eastern shore.");
			System.out.println("Who would you like to put in the boat first? [M]issionary, [C]annibal");		
			boat[0] = scanner.next( ); 
			System.out.println("Who would you like to put in the boat second?  [M]issionary, [C]annibal, [E]mpty");
			boat[1] = scanner.next( );
			
			//Prints out the state of the system before the boat has left. Includes how many are on the eastern bank and in the boat
			if (boat[0].equals(boat[1]) && boat[0].equals("M")) {
				if (missionaries_east >= 2 && missionaries_east <= 3) {
					missionaries_east--;
					missionaries_east--;
					System.out.print("Boat is on the eastern shore with two missionaries.");
				}
				else {
					System.out.println("You don't have that many missionaries on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[0].equals(boat[1]) && boat[0].equals("C")) {
				if (cannibals_east >= 2 && cannibals_east <= 3) {
					cannibals_east--;
					cannibals_east--;
					System.out.print("Boat is on the eastern shore with two cannibals.");
				}
				else {
					System.out.println("You don't have that many cannibals on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[0].equals("M") && !(boat[0].equals(boat[1]))) {
				if (missionaries_east >= 1 && missionaries_east <= 3) {
					missionaries_east--;
					System.out.print("Boat is on the eastern shore with a missionary ");
				}
				else {
					System.out.println("You don't have that many missionaries on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[0].equals("C") && !(boat[0].equals(boat[1]))) {
				if (cannibals_east >= 1 && cannibals_east <= 3) {
					cannibals_east--;
					System.out.print("Boat is on the eastern shore with a cannibal ");
				}
				else {
					System.out.println("You don't have that many cannibals on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			if (boat[1].equals("M") && !(boat[0].equals(boat[1]))) {
				if (missionaries_east >= 1 && missionaries_east <= 3) {
					missionaries_east--;
					System.out.print("and a missionary.");
				}
				else {
					System.out.println("You don't have that many missionaries on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[1].equals("C") && !(boat[0].equals(boat[1]))) {
				if (cannibals_east >= 1 && cannibals_east <= 3) {
					cannibals_east--;
					System.out.print("and a cannibal.");
				}
				else {
					System.out.println("You don't have that many cannibals on the east bank!");
					begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
				}
			}
			else if (boat[1].equals("E")) {
				System.out.print("by himself.");
			}
			
			if (cannibals_east > missionaries_east && missionaries_east != 0) {
				System.out.println("");
				System.out.println("You have " + missionaries_east + " missionaries and " + cannibals_east + " cannibals on the east bank.");
				System.out.println("Moving the boat now would make more cannibals than missionaries. Please choose again.");
				if (boat[0].equals("M")) {
					missionaries_east++;
				}
				else if (boat[0].equals("C")) {
					cannibals_east++;
				}
				if (boat[1].equals("M")) {
					missionaries_east++;
				}
				else if (boat[1].equals("C")) {
					cannibals_east++;
				}
				begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
			}
			else {
				System.out.println("");
				System.out.println("You have " + missionaries_east + " missionaries and " + cannibals_east + " cannibals on the west bank.");
				System.out.println("Boat is ready to move on.");
				if (boat[0].equals("M")) {
					missionaries_west++;
				}
				else if (boat[0].equals("C")) {
					cannibals_west++;
				}
				if (boat[1].equals("M")) {
					missionaries_west++;
				}
				else if (boat[1].equals("C")) {
					cannibals_west++;
				}
				bank = 0;
				begin(missionaries_west, missionaries_east, cannibals_west, cannibals_east, bank);
			}
		}
	}
	
	private void end( ) {
		System.out.println("Congratuations, you have successfully gotten everyone across the river!");
		System.out.println("Do you want to play again?");
	}
}
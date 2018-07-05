import java.util.*;
import java.lang.*;
public class Balance { 
	public static void main(String[] args) {
		
		System.out.println("Please enter a chemical equation to be balancedd.");
		System.out.println(start( ));
	}
	
	private static Scanner scanner = new Scanner(System.in);
	private static final int Na = 3;
	private static final int Cl = -1;
	
	
	public static String start( ) {
		int Charge = Na + Cl;
		if (Charge == 0) {
			return "FeCl3 is a neutral molecule.";
		}
		else {
			return "Molecule is not balanced.";
			makeBalanced( );
		}
	}
	
	public static String makeBalanced( ) {
		subscript = Cl
		
	}

}

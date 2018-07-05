//Need to throw and catch exceptions for negative inputs. See if I can work in some more intense string processing in the selection process. Also
//include a method to return the first n primes.
//
//Add additional methods to output various other common number sequences (i.e. Happy Numbers, Factorials, Deficient Numbers, Abundant numbers, Semiperfect Numbers, Weird Numbers, Factorization of a number, Lucky Numbers, Kolakoski Sequence, Look-And-Say Sequence, Juggler Sequence, Trianguar Numbers)
//
//Also consider making various math-related games (i.e. Tower of Hanoi, Chopsticks, Peg Solitaire, Switch State game(Like mine from Minecraft), Othello,
//Go, Connect Four, Checkers, Chinese Checkers, Catan, Conway's Game of Life, Missionaries and Cannibals)


// -help
import java.text.*; //For Math class(decimalFormat) (log(x))
import java.util.*; //For Scanner class
class PrimeCalc {
	public static void main(String[] args) {
		PrimeCalc number = new PrimeCalc( );

		number.start( );
	}

//These are the methods and values that are defined outside the individual methods. For example, Scanner is used by multiple methods, so is more
//efficient to declare outside of any single method. Alternatively, some values need to remain constant when a method is called multipe times, and in this case
//these need to be defined outside the method, so as to not get reset every time the method is called. These values are then reset upon conclusion
//of that pass through the method.
	static DecimalFormat df = new DecimalFormat("0.00");
	static int numberOfPrimes = 0;

//Constructor
	public PrimeCalc( ) {
	}

//Starts the program. Gives a brief statement of what it can do, which will not be displayed again.
	public void start( ) {
		selection( );
	}

//Selection step of the program. Any new major methods will be called using this. end method redirects any major method back to here, to make
//it a continuous program.
	private void selection( ) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("[FACTORS = 1] [PRIMES = 2] [FIBONACCI = 3]");
		try {
			int response = scanner.nextInt( );
			switch (response) {
			case 1: {
				System.out.println("Please enter a positive number, whose factors you would like to know: ");
				factors( );
				break;
			}
			case 2: {
				System.out.println("Please enter a positive number, up to which you want to know all prime numbers: ");
				primes( );
				primeArray.clear( );
				numberOfPrimes = 0;
				break;
			}
			case 3: {
				System.out.println("Please enter a positive number, up to which you want to know the Fibonacci Sequence: ");
				int upperBound = scanner.nextInt( );
				fibonacciSequence(upperBound);
				break;
			}
			default :{
				System.out.println("Invalid input. ");
				selection( );
			}
			}
		}
		catch (InputMismatchException e) {
			System.out.println("Please enter integer data only.");
			start( );
		}
	}

//Termination of the program. At the end of a major method, will come here, and then the user can continue to use other method, or else will
//terminate the program.
	private void end( ) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Do you want to test another number? [Y/N]");
		String response = scanner.next( );
		if (response.equals("y") || response.equals("Y")) {
			selection( );
		}
		else if (response.equals("n") || response.equals("N")) {
		}
		else {
			end( );
		}
	}

//Major method. Prompts the user to enter a number, and will print the contents of an array containing all the prime numbers up to and including that
//number. Will also print out the total number of prime numbers found, and an estimate of how many primes there should be to that number based on
//the formula "number of primes ~ n / ln(n)".
	static ArrayList primeArray = new ArrayList( );
	private void primes( ) {
		Scanner scanner = new Scanner(System.in);
		try {
			int i = 1;
			int j = scanner.nextInt( );
			if (j < 0) {
				System.out.println("Please enter only positive integers.");
				primes( );
			}
			else {
				System.out.println("Prime numbers up to " + j + ": ");
				for (i = 1; i <= j; i ++) {
					tester(i, j);
					i = i ++;
				}
			end( );
		}
		}
		catch (InputMismatchException e) {
			System.out.println("Please enter only positive integers.");
			primes( );
		}
	}

	private void primeOutput(int numberOfPrimes, int total) {
		for (int i = 0; i < numberOfPrimes; i++) {
			if (i < numberOfPrimes - 1) {
				System.out.print(primeArray.get(i) + ", ");
			}
			else if (i == numberOfPrimes - 1) {
				System.out.print(primeArray.get(i));
				System.out.println("");
			}
		}
			double estimate = total / Math.log(total);
			System.out.println("(" + numberOfPrimes + " primes total up to " + total + " with an estimate of " +df.format(estimate) + ")");
	}

//Major method. Prompts the user to enter a number, and will print the contents of an array containing all the factors of that number. Will also
//print out the total number of factors that number has. If the input is a prime number, it will tell the user.
	static ArrayList factorArray = new ArrayList( );
	private void factors( ) {
		Scanner scanner = new Scanner(System.in);
		int i = scanner.nextInt( );
		if (i >= 0) {
			tester(i, -1);
			factorArray.clear( );
			end( );
		}
		else {
			System.out.println("Invalid input, please enter a positive integer.");
			factors( );
		}
	}

	private void factorOutput(int count, int number, int test) {
		factorArray.add(number);
		if (number == test) {
			for (int i = 0; i < count; i++) {
				if (count != 2) {
					if (i < count - 1) {
						System.out.print(factorArray.get(i) + ", ");
					}
					else if (i == count - 1) {
						System.out.print(factorArray.get(i));
						System.out.println("");
					}
				}
			}
			if (count != 2) {
				System.out.println("(" + count + " factors total.)");
			}
		}
		if (count == 2 && number == test) {
			System.out.println(test + " is prime.");
		}
	}

//This method accepts the number to be tested and tests it, either for the prime numbers, or its factors. Both are contained within the same loop, but
//the second parameter allows the program to keep track of the count for factors or primes independantly.
	private void tester(int test, int total) {
		int pCount = 0;
		int fCount = 0;
		int number = 1;
		int remainder = 0;

		while (number <= test) {
			remainder = test % number;
				if (remainder == 0 && total == -1) {
					fCount++;
					factorOutput(fCount, number, test);
				}
			number = number + 1;
				if (remainder == 0 && number != test) {
					pCount++;
				}
				else if (remainder == 0) {
					pCount++;
				}
		}
		if (pCount == 2) {
			primeArray.add(test);
			numberOfPrimes++;
		}
		if (total == test) {
			primeOutput(numberOfPrimes, total);
		}
	}

//Accepts a number and outputs that many terms of the Fibonacci Sequence
	private void fibonacciSequence(int upperBound) {
		int[] fibonacciArray = new int[upperBound];
		fibonacciArray[0] = 0;
		fibonacciArray[1] = 1;
		for (int i = 2; i < upperBound; i++) {
			fibonacciArray[i] = fibonacciArray[i-1] + fibonacciArray[i - 2];
		}
		for (int k = 0; k < upperBound; k++) {
			if (k < upperBound - 1) {
				System.out.print(fibonacciArray[k] + ", ");
			}
			else if (k == upperBound - 1) {
				System.out.print(fibonacciArray[k]);
				System.out.println("");
			}
		}
		end( );
	}
}

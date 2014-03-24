import java.util.*;
class Ch4pr14 {
	public static void main(String[] args) {
	
	//Initializes all variables, creates a scanner, and inputs the relative gravity of earth.
	Scanner scanner = new Scanner(System.in);
	
	//Craetes an object and inputs the gravity relative to Eath
	WeightConvertor moonWeight, mercuryWeight, venusWeight, jupiterWeight, saturnWeight;
	moonWeight = new WeightConvertor(0.167);
	mercuryWeight = new WeightConvertor(0.4);
	venusWeight = new WeightConvertor(0.9);
	jupiterWeight = new WeightConvertor(2.5);
	saturnWeight = new WeightConvertor(1.1);
	
	//Inputs the user's weight
	System.out.println("Please enter the weight to be converted");
	double weight;
	weight = scanner.nextDouble( );
	
	
	//Converts the user's weight into the relative weight on the Moon, Mercury, Venus, Jupiter, and Saturn
	System.out.println("You weight: ");
	moonWeight.convert(weight);
		System.out.println(moonWeight.getWeight( ) + " on the Moon.");
	mercuryWeight.convert(weight);
		System.out.println(mercuryWeight.getWeight( ) + " on the Mercury.");
	venusWeight.convert(weight);
		System.out.println(venusWeight.getWeight( ) + " on the venus.");
	jupiterWeight.convert(weight);
		System.out.println(jupiterWeight.getWeight( ) + " on the Jupiter.");
	saturnWeight.convert(weight);
		System.out.println(saturnWeight.getWeight( ) + " on the Saturn.");
	}
}
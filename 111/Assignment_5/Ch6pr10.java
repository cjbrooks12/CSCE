/* The price table for carpet we printed out in section 6.6 contains index values for width and length, but not labels to identify them. Write 
a program that generates the table shown next. */

class Ch6pr10 {
	public static void main(String[] args) {
	
	int price;
	
	System.out.println("                    Length");
	System.out.println("            5    10   15   20   25");
	System.out.println("");
	for (int width = 11; width <= 14; width ++) {
		System.out.print("        " + width + " ");
		for (int length = 5; length <= 25; length += 5) {
			price = width * length * 19; //$19 per square foot
			System.out.print(" " + price);
		}
		System.out.println("     ");
	}
	System.out.print("Width");
	for (int width = 15; width <= 15; width ++) {
		System.out.print("   " + width + " ");
		for (int length = 5; length <= 25; length += 5) {
			price = width * length * 19; //$19 per square foot
			System.out.print(" " + price);
		}
		System.out.println("     ");
	}
	
	for (int width = 16; width <= 20; width ++) {
		System.out.print("        " + width + " ");
		for (int length = 5; length <= 25; length += 5) {
			price = width * length * 19; //$19 per square foot
			System.out.print(" " + price);
		}
		System.out.println("     ");
	}
	
	}
}
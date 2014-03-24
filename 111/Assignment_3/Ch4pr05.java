class Ch4pr05 {

	public static void main(String[] args) {
	
		Die die;
		die = new Die();
		
		die.roll();
		System.out.println("The first roll is: " + die.getNumber( ));
		
		die.roll();
		System.out.println("The second roll is: " + die.getNumber( ));
		
		die.roll();
		System.out.println("The third roll is: " + die.getNumber( ));
	}
}
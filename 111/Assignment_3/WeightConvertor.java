class WeightConvertor {
	
	//Data member
	private double weight1, weight2, gravity;
	
	//Constructor
	public WeightConvertor(double grav1) {
		gravity = grav1;
	}
			
	//Returns value of celsius
	public double convert(double weight1){
		weight2 = (weight1) * (gravity);
		return weight2;
	}
	
	public double getWeight( ) {
		return weight2;
	}
}
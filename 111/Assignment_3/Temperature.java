class Temperature {
	
	//Data member
	private double farenheit, celsius;
	
	//Constructor
	public Temperature( ) {
		farenheit = 0;
		celsius = 0;
	}
	
	//assigns the value of farenheit
	public void setFarenheit(double temp1) {
		farenheit = temp1;
		farenheit = (farenheit -32) * 5 / 9;
	}
	//Returns value of celsius
	public double toCelsius( ){
		return farenheit;
	}
	
	//assigns the value of celsius
	public void setCelsius(double temp2) {
		celsius = temp2;
		celsius = (celsius * 9 / 5) + 32;
	}
	//Returns value of celsiusOut
	public double toFarenheit( ){
		return celsius;
	}
}
	
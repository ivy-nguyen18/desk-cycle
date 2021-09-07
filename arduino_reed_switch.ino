int Sensor_pin = A0 ; // initializing A0 as sensor pin
int Led_pin = 12 ;  // initializing pin 12 as led pin
int Value = 0 ;  // initializing a variable to store sensor value
void setup ( ) {
  pinMode ( Led_pin, OUTPUT ) ;  // declaring pin 12 as output pin
  Serial.begin ( 9600 ) ; // Setting baud rate at 9600
}

void loop ( ) {
  Value = analogRead ( Sensor_pin ) ; // reading from the sensor
  digitalWrite ( Led_pin, HIGH ) ;
  delay (Value ) ;
  digitalWrite ( Led_pin, LOW ) ;
  delay ( Value ) ;
  Serial.print( "SENSOR PIN A0:" ) ;
  Serial.println ( Value, DEC ) ;// displaying the value on serial monitor
  if(Value == 76){
    Serial.println("On");
  }
}
// set up the variables
#define LED A3
#define HALL A4
int revolutions = 0;
const int radius = 9; //wheel radius in inches
float circumference; 
long timer = 0; // time ebtween one full rotation (in ms)
float velocity = 0.00; // miles per hours
int maxHallCounter = 100; //min time (in ms) of one rotation (for debouncing)
int hallCounter;
volatile long temp, counter = 0;
int hallVal;

void setup() {
  circumference = M_PI * 2 * radius;
  hallCounter = maxHallCounter;

  // set up of ENCODER
  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);
   
  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);

  //set up of HE-SENSOR
  pinMode(LED, OUTPUT);
  pinMode(HALL, INPUT);

  //TIMER SETUP - timer interrupt allows precise timed measurements of the switch
  cli(); //stop interrupts

  //set timer1 intterupt at 1kHz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // set entire TCCR1B register to 0
  TCNT1 = 0; // set entire TCNT1 register to 0

  //set timer count for 1khz increments
  OCR1A = 1999; //(1/1000) / ((1/16*10^6)) * 8) - 1
  //turn on CTC 
  TCCR1B |= (1 << WGM12);
  //set CS11 bit for 8 prescaler
  TCCR1B |= (1 << CS11);
  //enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //allow interrupts
  //END TIMER SETUP

  Serial.begin (9600);

}

ISR(TIMER1_COMPA_vect){ //interrupt at freq of 1kHZ to measure reed switch
  hallVal = digitalRead(HALL); //get val of HALL
  if (hallVal){ ///if switch is closed
    if( hallCounter == 0){//min time between pulses has passed
      velocity = (56.8 * float(circumference)) / float(timer); //calculate
      timer = 0; //reset timer
      hallCounter = maxHallCounter; //reset hallCounter
    } else {
      if(hallCounter > 0) { // don't let counter go negative
        hallCounter -=1; //decrement hallCounter
      }
    }
  } else {// if switch is open
    if(hallCounter > 0) { // don't let counter go negative
        hallCounter -=1; //decrement hallCounter
      }
  }

  if( timer > 2000){
    velocity = 0; //if no new pulses from switch -> tire is still, set velocity to 0
  } else {
    timer += 1;
  }
}

void loop(){
  //HE-SENSOR code
  //Serial.println(digitalRead(HALL));

  //if magnet is read, increment revolutions
  if(digitalRead(HALL) == 1){
    revolutions ++;
  }

  // Send the value of counter
  if( counter != temp ){
    Serial.println (counter);
    temp = counter;
  }
  
  Serial.println(velocity);
   
  delay(1000); //delay for 1 second 
}

void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
    counter++;
    }else{
      counter--;
    }
}
   
  void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
    counter--;
    }else{
      counter++;
    }
}

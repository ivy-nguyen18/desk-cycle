#define LED A3
#define HALL A4

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(HALL, INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(digitalRead(HALL));
  if(digitalRead(HALL) == 0){
    digitalWrite(LED, HIGH);
  }else{
    digitalWrite(LED, LOW);
  }
}

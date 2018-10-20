 /* 
  Code Produced
  By Mark Landergan
  10/20/2018
  
  Automated Keurig machine
  Version 1
  Purpose: Pump water into keurig, turn on power button to keurig, hit brew button based on time 
*/ 

#include <Servo.h>

Servo powerButton;
Servo brewButton;
bool waterDeployed = false;
bool coffeeRequest = true; // TODO: change to read data from local webserver
const int outlet = 8;
const int largeCoffeeTime = 112000; // time required to transfer 2 1/2 cups of water (full cup)

void setup() {
  Serial.begin(9600); // pour yourself a bowl of serial
  pinMode(outlet, OUTPUT);
  powerButton.attach(9);
  brewButton.attach(10);
  powerButton.write(0);
  brewButton.write(0);
}

void loop() {
  // listen for coffeeRequests from webServer
  
  if(coffeeRequest){
    makeCoffee(largeCoffeeTime);
    coffeeRequest = false;
  }
}
 
// drive given servo object and integer to deseried position maxVal (degrees)
void pushButton(Servo myservo, int maxVal){
  int pos = 0;
  for(pos = 0; pos <= maxVal; pos++){
    myservo.write(pos);
    delay(15);
    }
  }

// drive to 0 degrees given servo object and starting position maxVal (degrees)
void liftButton(Servo myServo, int minVal){
  int pos = 0;
  for(pos = minVal; pos >= 0; pos--){
    myServo.write(pos);
    delay(15);
    }
  }

void makeCoffee(int timeSizeCoffee){
  if(waterDeployed == false){
    digitalWrite(outlet, HIGH);   // turn the Relay HIGH, enabling pump, no power to keurig
    delay(timeSizeCoffee); // delay the desiered amount requried for specific size coffee
    waterDeployed = true;
  }
  digitalWrite(outlet, LOW);    // turn the Relay LOW, disabiling pump, power to keurig

  // turn on Keurig machine
  pushButton(powerButton, 35); 
  delay(1000);
  liftButton(powerButton, 35);
  
  delay(2000); // wait 2 seconds for keurig to warm up

  // press the brew button
  liftButton(brewButton, 170);
  delay(1000);
  pushButton(brewButton, 170);
  }

void testingFunctions(){
  if(waterDeployed == false){
    Serial.println("Deploying Water!");
    digitalWrite(outlet, HIGH);   // turn the Relay HIGH, enabling pump, no power to keurig
    //delay(112000);  time for one full cup of water
    //delay(100); // testing purposes keep this short
    waterDeployed = true;
  }
  digitalWrite(outlet, LOW);    // turn the Relay LOW, disabiling pump, power to keurig
  
  Serial.println("Pressing the power button");
  pushButton(powerButton, 35);
  delay(1000);
  liftButton(powerButton, 35);
  delay(1000);
  Serial.println("Pressing the brew button");  
  liftButton(brewButton, 170);
  delay(1000);
  pushButton(brewButton, 170);  
}

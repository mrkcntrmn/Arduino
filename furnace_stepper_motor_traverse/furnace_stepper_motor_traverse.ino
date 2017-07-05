//Uploaded 7-3-17


long steps = 0;

long offset = 3000+14000;

long traverseSteps = 198000 - offset -14000;

int pitch = 1150;

boolean reverse = true  ;

void setup() {
  // put your setup code here, to run once:
/*Code from http://www.schmalzhaus.com/EasyDriver/Examples/Ea... */

 // Record the number of steps we've taken void setup() {
Serial.begin(9600);

pinMode(4, INPUT);  
   
pinMode(8, OUTPUT);

pinMode(9, OUTPUT);

digitalWrite(8, reverse);

digitalWrite(9, LOW);


goHome();
Serial.println("Home");

homeOffset();


}

void loop() {
  
  // move one step
  digitalWrite(9, HIGH);
  delayMicroseconds(100);
  digitalWrite(9, LOW);
  delayMicroseconds(100);

  steps++;
  
  delayMicroseconds(pitch);

  if (steps == traverseSteps){
    reverse = !reverse;
    digitalWrite(8, reverse);
    pitch = pitch+5;
    steps = 0;
  }


}

void homeOffset(){
  
  for (int i=0; i <= offset; i++){
    
    // set direction to forward
    reverse = false;
    digitalWrite(8, reverse);  
    
    //move one step
    digitalWrite(9, HIGH);
    delayMicroseconds(100);
    digitalWrite(9, LOW);
    delayMicroseconds(100);
    
    // determines step speed
    delayMicroseconds(100);
    
  }
  
  delay(1000);
  
}



// returns carriage home and sets direction forward
void goHome(){
  
  // checks to see if home sensor is on
  while (digitalRead(4)){

    // set direction to reverse
    reverse = true;
    digitalWrite(8, reverse);  
    
    //move one step
    digitalWrite(9, HIGH);
    delayMicroseconds(100);
    digitalWrite(9, LOW);
    delayMicroseconds(100);
    
    // determines step speed
    delayMicroseconds(100);  

  }  
  
  // direction is set forward
  reverse = false;
  digitalWrite(8, reverse); 

}
  

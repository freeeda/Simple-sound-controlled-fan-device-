int red = 7;
int green = 2;
int fan = 9;

float loudness = 0;
float sensorValue;
float sensorPrevious;

void setup() {
  Serial.begin(9600);

  //digital output
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  
  pinMode(fan, OUTPUT);

}

void loop() {
  loudness = 0;
  float totalSamples = 100;
  
  for (float i = 0; i < totalSamples; i++) {
    // read the sensor:
    sensorValue = analogRead(A0);
    //frame differencing: calculates change of current over previous between samples and takes
    //absolute value, loudness is constantly getting larger as it reads data
    loudness += abs(sensorValue - sensorPrevious);

    //this constantly saves the previous value to calculate the difference
    sensorPrevious = sensorValue;
  }
  
  int vol = map(loudness, 3000, 45000, 0, 255);

  Serial.println(loudness);
  //Serial.println(vol);

  if (loudness > 15000) {
    //sound variation is detected and turn on the green light
    //turn off the red light
    //set fan on to be true
    digitalWrite(red,LOW);
    //delay(100);
    digitalWrite(green, HIGH);
    //delay(100);
    analogWrite(fan, vol);
    
 
   }

  else{
    //turn off the green light
    //turn on red light to indicate currently there is no obvious sound signal
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    //turn off fan
    analogWrite(fan,0);

   }



}

#define DistanceEn_Pin 2
 
int i = 0;
long unsigned distance = 0;
uint8_t distanceValue[4] = {0,0,0,0};
void setup() 
{
  Serial.begin(115200);
  pinMode(DistanceEn_Pin,OUTPUT);
  digitalWrite(DistanceEn_Pin,1);
}
 
void Distance()
{
  while( Serial.read() >= 0 );         //Empty the serial buffer
  digitalWrite(DistanceEn_Pin,0);      //Ultrasound can open
  while(Serial.available() <= 4)       //Waiting for the ultrasonic data window
  { 
  }
  distanceValue[0] = Serial.read();    //Extract the data
  if( distanceValue[0] == 0xff )       //Determine if data for ultrasonic module
  {
    for(i = 1;i <= 3;i ++)
    {
      distanceValue[i] = Serial.read();
    }
   }
 
  digitalWrite(DistanceEn_Pin,1);       //Ultrasound can make
 
  distance = distanceValue[1] * 256 + distanceValue[2];                   //Data processing, calculating distance
  if((distanceValue[3] == distanceValue[1] + distanceValue[2] - 1))       //Data and check, can be removed
  {
    Serial.print("The distance is : ");
    Serial.print(distance);
    Serial.println(" mm");
  }
}
 
void loop() 
{
  Distance();
}

                        /*     pins      */
/////////////////////////////////////////////////////////////////////////////////////
//Front sensor and vibration
#define TRIG_PIN_FRONT 12
#define ECHO_PIN_FRONT 3
#define VIBRATION_PIN_FRONT 11

//Right sensor and vibration
#define TRIG_PIN_RIGHT 7
#define ECHO_PIN_RIGHT 2
#define VIBRATION_PIN_RIGHT 9

//Left sensor and vibration
#define TRIG_PIN_LEFT 4
#define ECHO_PIN_LEFT 6
#define VIBRATION_PIN_LEFT 10
/////////////////////////////////////////////////////////////////////////////////////

                   /*variables*/
//////////////////////////////////////////////////////////////////////
unsigned long prevTimeFront ;
unsigned long prevTimeRight ;
unsigned long prevTimeLeft ;
/////////////////////////////////////////////////////////////////////
void setup() {
  
  Serial.begin(9600);    
                /*initializing pins*/
  ///////////////////////////////////////////////// 
  //Initializing Front pins
  pinMode(TRIG_PIN_FRONT,OUTPUT);
  pinMode(ECHO_PIN_FRONT,INPUT);
  pinMode(VIBRATION_PIN_FRONT,OUTPUT);
  
  //Initializing Right pins
  pinMode(TRIG_PIN_RIGHT,OUTPUT);
  pinMode(ECHO_PIN_RIGHT,INPUT);
  pinMode(VIBRATION_PIN_RIGHT,OUTPUT);
  
  //Initializing Front pins
  pinMode(TRIG_PIN_LEFT,OUTPUT);
  pinMode(ECHO_PIN_LEFT,INPUT);
  pinMode(VIBRATION_PIN_LEFT,OUTPUT);
  //////////////////////////////////////////////////
  prevTimeFront = millis();
  prevTimeRight = millis();
  prevTimeLeft = millis();
  
}


void loop() {
            /*getting the appropriate vibration for the FRONT sensor*/
////////////////////////////////////////////////////////////////////////////////////////
//getting 3 reads from the front sensor
  double distanceF1=getDis(TRIG_PIN_FRONT,ECHO_PIN_FRONT);
  double distanceF2=getDis(TRIG_PIN_FRONT,ECHO_PIN_FRONT);
  double distanceF3=getDis(TRIG_PIN_FRONT,ECHO_PIN_FRONT);
//calculating the min distance to avoid error
  double minDistanceF = getMin(distanceF1,distanceF2,distanceF3);
//vibrating the the vibration motor according to the distance
  vibrate(minDistanceF , VIBRATION_PIN_FRONT ,prevTimeFront);
///////////////////////////////////////////////////////////////////////////////////////////  



            /*getting the appropriate vibration for the RIGHT sensor*/

////////////////////////////////////////////////////////////////////////////////////////

//getting 3 reads from the right sensor
  double distanceR1=getDis(TRIG_PIN_RIGHT,ECHO_PIN_RIGHT);
  double distanceR2=getDis(TRIG_PIN_RIGHT,ECHO_PIN_RIGHT);
  double distanceR3=getDis(TRIG_PIN_RIGHT,ECHO_PIN_RIGHT);
//calculating the min distance to avoid error
  double minDistanceR = getMin(distanceR1,distanceR2,distanceR3);
//vibrating the the vibration motor according to the distance
  vibrate(minDistanceR , VIBRATION_PIN_RIGHT ,prevTimeRight);
  
///////////////////////////////////////////////////////////////////////////////////////////  



            /*getting the appropriate vibration for the LEFT sensor*/
////////////////////////////////////////////////////////////////////////////////////////

//getting 3 reads from the left sensor
  double distanceL1=getDis(TRIG_PIN_LEFT,ECHO_PIN_LEFT);
  double distanceL2=getDis(TRIG_PIN_LEFT,ECHO_PIN_LEFT);
  double distanceL3=getDis(TRIG_PIN_LEFT,ECHO_PIN_LEFT);
//calculating the min distance to avoid error
  double minDistanceL = getMin(distanceL1,distanceL2,distanceL3);
//vibrating the the vibration motor according to the distance
  vibrate(minDistanceL , VIBRATION_PIN_LEFT ,prevTimeLeft);
  
///////////////////////////////////////////////////////////////////////////////////////////  

    
  
}

                                          /*functions*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * this function calculates the distance in cm from te ultrasonic sensor
 * parameters: 
 * 1- trig:the triger pin of the sensor
 * 2- echo:the echo pin of the sensor
 */
double getDis(int trig , int echo ){
  
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  //calculating duration and distance
 double duration = pulseIn(echo,HIGH,15000);
 if(duration==0)
 {
  pinMode(echo,OUTPUT);
  digitalWrite(echo,LOW);
  delayMicroseconds(200);
  pinMode(echo,INPUT);
 }
 return (duration/2.0)/29.1;
   }

/*
 *this function calculates the min number of the 3 inputs numbers 
 */
double getMin(double x , double y , double z){
  double minDistance = x;

  if(minDistance > y)
  {
    minDistance = y;
  }
  if(minDistance >z)
  {
    minDistance = z;    
  }

  return minDistance;
}

/*
 * giving the vibration motor the appropriate volt (PWM) according to the distance 
 * and according to the previous time
 * 
 * parameters:
 * 1-distance : the distance from the ultrasonic sensor
 * 2-vibrationPin : the pin which the ouput volt will be given to
 * 3-prev Time
 */
void vibrate(double distance , int vibrationPin ,unsigned long& prevTime){
   if(distance > 3 && distance <=75)
    {
      Serial.print(distance);    
      Serial.println(vibrationPin);
      Serial.println(" Close");
      analogWrite(vibrationPin,200);

      prevTime = millis();
      
    }
    
    else if(distance > 75 && distance <=150)
    {
      Serial.print(distance);
      Serial.println(vibrationPin);    
      Serial.println(" Far");
      analogWrite(vibrationPin,150);

      prevTime = millis();
       
    }
    else if ((distance < 3 || distance >150) && ((millis() - prevTime) > 300)) {
    analogWrite(vibrationPin,00);
    Serial.println(vibrationPin);
    Serial.println(" out of range");
    } 
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

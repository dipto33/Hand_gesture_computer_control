const int trigger1 = 2; //Trigger pin of left Sesnor
const int echo1 = 3; //Echo pin of left Sesnor
const int trigger2 = 4; //Trigger pin of right Sesnor
const int echo2 = 5;//Echo pin of right Sesnor

const int IR_SensorL = 12;
const int IR_SensorR = 8;

long time_taken;
int dist, distL, distR;



void setup() {
  Serial.begin(9600);

  pinMode(trigger1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(IR_SensorL, INPUT);
  pinMode(IR_SensorR, INPUT);
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  time_taken = pulseIn(echo, HIGH);
  dist = time_taken * 0.034 / 2;
  if (dist > 50)
    dist = 50;
}

void loop() { //infinite loopy

  if (digitalRead(IR_SensorL) == LOW)   //Check the sensor output

  {
    Serial.println("Leftclicked");
    delay(200);

  }

  if (digitalRead(IR_SensorR) == LOW)   //Check the sensor output

  {
    //digitalWrite(13, HIGH);   // set the LED on
    Serial.println("Rightclicked");
    delay(200);

  }
  calculate_distance(trigger1, echo1);
  distL = dist; //get distance of left sensor

  calculate_distance(trigger2, echo2);
  distR = dist; //get distance of right sensor

  //Uncomment for debudding
  /*Serial.print("L=");
    Serial.println(distL);
    Serial.print("R=");
    Serial.println(distR);
  */

  //Pause Modes -Hold
  if ((distL > 40 && distR > 40) && (distL < 50 && distR < 50)) //Detect both hands
  {
    Serial.println("Play/Pause");
    delay (500);
  }

  calculate_distance(trigger1, echo1);
  distL = dist;
  //Serial.println(distL);

  calculate_distance(trigger2, echo2);
  distR = dist;
  //Serial.println(distR);



  //Control Modes
  //Lock Left - Control Mode
  if (distL >= 13 && distL <= 17)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger1, echo1);
    distL = dist;
    if (distL >= 13 && distL <= 17)
    {
      Serial.println("Left Locked");
      while (distL <= 40)
      {
        calculate_distance(trigger1, echo1);
        distL = dist;
        if (distL < 10) //Hand pushed in
        {
          Serial.println ("Vdown");
          delay (300);
        }
        if (distL > 20) //Hand pulled out
        {
          Serial.println ("Vup");
          delay (300);
        }
      }
    }
  }

  //Lock Right - Control Mode
  if (distR >= 13 && distR <= 17)
  {
    delay(100); //Hand Hold Time
    calculate_distance(trigger2, echo2);
    distR = dist;
    if (distR >= 13 && distR <= 17)
    {
      Serial.println("Right Locked");
      while (distR <= 40)
      {
        calculate_distance(trigger2, echo2);
        distR = dist;
        if (distR < 10) //Right hand pushed in
        {
          Serial.println ("Backward");
          delay (300);
        }
        if (distR > 20) //Right hand pulled out
        {
          Serial.println ("Forward");
          delay (300);
        }
      }
    }
  }

  delay(200);
}

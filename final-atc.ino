//Mux control pins
int s0 = 3;
int s1 = 4;
int s2 = 5;
int s3 = 6;

#define ledA1 A5
#define ledA2 A4
#define ledA3 A3  //s pins are 3 4 5 6

#define ledB1 10
#define ledB2 11
#define ledB3 12

#define ledC1 7
#define ledC2 8
#define ledC3 9


#define ledD1 A2
#define ledD2 A1
#define ledD3 13
//
//#define ledZ1 A5 //AMBI-SIGNAL
//#define ledZ2 A4
//#define ledZ3 A3
int a1,a2,b1,b2,c1,c2,d1,d2,t,z1,z2,EMV;





//Mux in "SIG" pin
const int SIG_pin = A0;
const int EN = 7;// Enable pin 
const int controlPin[4] = {s0,s1,s2,s3};

void setup() {
  


 Serial.begin(9600);

  pinMode(ledA1, OUTPUT);
  pinMode(ledA2, OUTPUT);
  pinMode(ledA3, OUTPUT);

  pinMode(ledB1, OUTPUT);
  pinMode(ledB2, OUTPUT);
  pinMode(ledB3, OUTPUT);

  pinMode(ledC1, OUTPUT);
  pinMode(ledC2, OUTPUT);
  pinMode(ledC3, OUTPUT);

  pinMode(ledD1, OUTPUT);
  pinMode(ledD2, OUTPUT);
  pinMode(ledD3, OUTPUT);



 pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 
  
  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);




 

}

int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

//  loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
  }

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
return val;

 
 
}


void loop(){

readval();


//if(EMV<800)
//{
//  Serial.println("*************************Ambulance detected on lane A******************************");
//  greenchannel();
//}
//else
//{
//  Serial.println("Ambulance not detected on any lane");
//
//}

if(a2 <500 || b1 <500 || b2 < 500)
{
 laneA();
// if(EMV<800)
// {
//  greenchannel();
// }
 if(c1 < 500 || c2 < 500 || d1 < 500 || d2 < 500)
 {
  laneB();
 }
 else if(a2 <500 && b1 <500 && c2 < 500 )
{
  laneA();
}
}
else if(c1 < 500 || c2 < 500 || d1 < 500 || d2 < 500)
{
  laneB();
//  if(EMV<800)
// {
//  greenchannel();
// }
  if(a2 <500 || b1 <500 || b2 < 500)
  {
    laneA();
  }
}

else if(c1 < 500 && c2 < 500 && d1 < 500 && d2 < 500)
{
  laneB();
}
else
{
  digitalWrite(ledA3,HIGH);
  digitalWrite(ledB3,HIGH);
  digitalWrite(ledC3,HIGH);
  digitalWrite(ledD3,HIGH);
}



}





void readval()
{
  
  a2 = readMux(1);
  d1 = readMux(6);
  d2 = readMux(7);
  b1 = readMux(4);
  b2 = readMux(5);
  c1 = readMux(2);
  c2 = readMux(3);
  z1 = readMux(13);
  z2 = readMux(14);
  t=analogRead(readMux(10)); 
  EMV=readMux(12);
//delay(100);
  for(int i = 0; i < 11; i ++){
    Serial.print("Value at channel ");
 
    
    Serial.print(i);
    Serial.print("is : ");
    Serial.println(readMux(i));
   
    }
}

void laneA()
{
  digitalWrite(ledA3, LOW);
  digitalWrite(ledB3,LOW);
  
  digitalWrite(ledA1, HIGH);
  digitalWrite(ledB1,HIGH);
  
  digitalWrite(ledC3, HIGH);
  digitalWrite(ledD3, HIGH);
  delay(10000);
  digitalWrite(ledA2, HIGH);
  digitalWrite(ledB2, HIGH);

  digitalWrite(ledA1, LOW);
  digitalWrite(ledB1, LOW);
  

  delay(1000);
  digitalWrite(ledA2, LOW);
  digitalWrite(ledB2,LOW);

  
 readval();
}

void laneB()
{
  digitalWrite(ledC3, LOW);
  digitalWrite(ledD3,LOW);
  
  digitalWrite(ledC1, HIGH);
  digitalWrite(ledD1,HIGH);
  
  digitalWrite(ledA3, HIGH);
  digitalWrite(ledB3, HIGH);
  
  delay(10000);
   digitalWrite(ledC2, HIGH);
  digitalWrite(ledD2, HIGH);
  
  digitalWrite(ledC1, LOW);
  digitalWrite(ledD1, LOW);
 
  delay(1000);
  digitalWrite(ledC2, LOW);
  digitalWrite(ledD2,LOW);

  
  readval();
}

void greenchannel()
{
  digitalWrite(ledA3, LOW);
  
  digitalWrite(ledA1, HIGH);
  digitalWrite(ledB3,HIGH);
  
  digitalWrite(ledC3, HIGH);
  digitalWrite(ledD3, HIGH);
  delay(10000);
  digitalWrite(ledA2, HIGH);
  
  digitalWrite(ledA1, LOW);

  

  delay(1000);
  digitalWrite(ledA2, LOW);
  
  readval();
}

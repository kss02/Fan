#include <RBDdimmer.h>//https://github.com/RobotDynOfficial/RBDDimmer//
#include <WiFi.h>// esp32 library
#include <ArduinoJson.h>
#include <IOXhop_FirebaseESP32.h> firebase library
//------------------ Firebase connection parameters-----------------
#define FIREBASE_HOST "ceilingfanregulation-default-rtdb.firebaseio.com"// URL
#define FIREBASE_AUTH "KyUyCT2zo45IWqxlt6lmL5tYDalrLxhva9SwLcw9"// secret token key
//-----------------------Wifi Credentials-----------------------------
#define WIFI_SSID "SCRC_LAB"// SSID or Name
#define WIFI_PASSWORD "Scrciiith@123" // Password
//--------------------------Parameters---------------------------------
String Resivedata="";// Recieve data from Firebase
const int Speed1=14;
const int Speed2=25;
const int Speed3=14;
const int Speed4=27;

//Variables
int power  = 0;// Power Output for Load

    bool speed1_flag = 1;
    bool speed2_flag = 1;
    bool speed3_flag = 1;
    bool speed4_flag = 1;
    bool speed0_flag = 1;


void setup(){
  pinMode(Speed1,OUTPUT);
  pinMode(Speed2,OUTPUT);
  //pinMode(Speed4,OUTPUT);
  
  digitalWrite(Speed1, LOW);
  digitalWrite(Speed2, HIGH);
  //digitalWrite(Speed4, LOW);
  
   //Init Serial USB
   Serial.begin(115200);//Begin Serial Monitor
   Serial.println(F("ESP32 System"));

   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);// WiFi connection
   Serial.print("connecting");
   while (WiFi.status() != WL_CONNECTED)// checking if WiFi is connected or not
   {
        Serial.print(".");
        delay(500);
   }
   Serial.println();
   Serial.print("connected: ");
   Serial.println(WiFi.localIP());//Printing WiFi IP Address
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);//Firebase Connection
    
}

void loop(){
  testDimmer();
}

void testDimmer(){/* function testDimmer */ 
  //Sweep light power to test dimmer
  Resivedata = Firebase.getString("CeilingFanRegulator/Variable/Value");//recieving data from Firebase
  power=Resivedata.toInt();//converting String to Integer
  //power=map(Resivedata.toInt(), 15, 73, 0, 100);
  
  Serial.println(power);
    delay(100);

if(power <=15)
{
  speed0();
  Serial.println("SPEED 0");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 0;
}
else if(power >15 && power <=40 && speed1_flag == 1)
{
  speed1();
  Serial.println("SPEED 1");
    speed1_flag = 0;
    speed2_flag = 1;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;
}
else if(power >40 && power <=60 &&speed2_flag == 1)
{
  speed2();
  Serial.println("SPEED 2");
    speed1_flag = 1;
    speed2_flag = 0;
    speed3_flag = 1;
    speed4_flag = 1;
    speed0_flag = 1;
}
else if(power >60 &&speed3_flag == 1 )
{
  speed3();
  Serial.println("SPEED 3");
    speed1_flag = 1;
    speed2_flag = 1;
    speed3_flag = 0;
    speed4_flag = 1;
    speed0_flag = 1;
}

}
void speed0()
{
  digitalWrite(Speed1, LOW);
  digitalWrite(Speed2, LOW);
//  digitalWrite(Speed4, HIGH);

}

void speed1()
{
  //Speed1 Relay On - Fan at speed 1
  digitalWrite(Speed2, LOW);
 // digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed1, HIGH);
}

void speed2()
{
  //Speed2 Relay On - Fan at speed 2

  digitalWrite(Speed1, LOW);
  //digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed2, HIGH);
}

void speed3()
{
  //Speed1 & Speed2 Relays On - Fan at speed 3

  digitalWrite(Speed1, LOW);
  digitalWrite(Speed2, LOW);
  //digitalWrite(Speed4, HIGH);
  delay(500);
  digitalWrite(Speed1,HIGH);
  digitalWrite(Speed2, HIGH);

}

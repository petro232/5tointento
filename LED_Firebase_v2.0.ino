#include <ArduinoJson.h>
#include <IOXhop_FirebaseESP32.h>
#include <WiFi.h>                                                // esp32 library
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define FIREBASE_HOST "prueba-arduino-b9160.firebaseio.com"                     // the project name address from firebase id
#define FIREBASE_AUTH "TQeum8lWY1Eh4dei8hCJLaXq7xcO1y6Xn6FAfymY"                   // the secret key generated from firebase
#define WIFI_SSID "The Chuli's House"                                          // input your home or public wifi name
#define WIFI_PASSWORD "chuli351624"                                    //password of wifi ssid
#define DHTPIN 19
#define DHTTYPE    DHT11

const int PWMPIN = 18;
bool banio = "";                                                     // led status received from firebase
bool cocina = ""; 
bool cochera = ""; 
int pwmfromfirebase = 0;
int pwmalmacenado = 0;
DHT dht(DHTPIN, DHTTYPE);

const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int led = 2;  
short contador; 
float t = 0;
float h = 0;

void setup() {

  Serial.begin(9600);
  delay(1000);
  pinMode(2, OUTPUT);      
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);   
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(PWMPIN, ledChannel);    
  dht.begin();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi

  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    
    Serial.print(".");
    delay(500);

  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  
}

void loop() {

// LEDs Semaforo

  banio = Firebase.getBool("led/banio");                     // get led status input from firebase 

  if (banio) {                         // compare the input of led status received from firebase
    Serial.println("Baño ON");                 
    digitalWrite(2, HIGH);                                                         // make output led ON
  }

  else if (!banio) {              // compare the input of led status received from firebase
    Serial.println("Baño OFF");
    digitalWrite(2, LOW);                                                         // make output led OFF
  }

  else {
    Serial.println("Comando erróneo");
  }
  
  cocina = Firebase.getBool("led/cocina");  
  
    if (cocina) {                         // compare the input of led status received from firebase
    Serial.println("Cocina ON");                 
    digitalWrite(4, HIGH);                                                         // make output led ON

  }

  else if (!cocina) {              // compare the input of led status received from firebase
    Serial.println("Cocina OFF");
    digitalWrite(4, LOW);                                                         // make output led OFF
  }

  else {
    Serial.println("Comando erróneo");
  }
  
  cochera = Firebase.getBool("led/cochera"); 

    if (cochera) {                         // compare the input of led status received from firebase
    Serial.println("Cochera ON");                 
    digitalWrite(16, HIGH);                                                         // make output led ON
  }

  else if (!cochera) {              // compare the input of led status received from firebase
    Serial.println("Cochera OFF");
    digitalWrite(16, LOW);                                                         // make output led OFF
  }

  else {
    Serial.println("Comando erróneo");
  }

// LED PWM 

  pwmfromfirebase = Firebase.getInt("intensidad/int1");
  Serial.println("LED PWM");
  Serial.println(pwmfromfirebase);
  if (pwmfromfirebase>pwmalmacenado){
      for(int dutyCycle = pwmalmacenado; dutyCycle <= pwmfromfirebase; dutyCycle++){   
        ledcWrite(ledChannel, dutyCycle);
        delay(15);
      }
  }
  
  else if (pwmfromfirebase<pwmalmacenado) {
      for(int dutyCycle = pwmalmacenado; dutyCycle >= pwmfromfirebase; dutyCycle--){
        ledcWrite(ledChannel, dutyCycle);   
        delay(15);
      }
  }
  
  pwmalmacenado = pwmfromfirebase;

  
  // Sensor dth11
  contador ++;


if (contador = 1200);{
    
  t = dht.readTemperature(); 
  h = dht.readHumidity();
  
  Firebase.set("meteorologia/temperatura", t);
  Firebase.set("meteorologia/humedad", h);

    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("%  Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print("\n");

  contador = 0;
  }
  
}

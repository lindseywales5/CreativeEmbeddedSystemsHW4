#include <ESP32Servo.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>
  
const char *ssid     = "myguestnetwork"; 
const char *password = "mnwguest";
WiFiUDP Udp;
unsigned int localUdpPort = 4210; 
char incomingPacket[255];  

Servo myservo;  
int posVal = 0;    
int servoPin = 15; 

int outPorts[] = {14, 27, 26, 25};

bool activate = false;

void setup() {
  //wifi stuff 
  int status = WL_IDLE_STATUS;
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to wifi");
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  // we recv one packet from the remote so we can know its IP and port
  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
     {
      // receive incoming UDP packets
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      readPacket = true;
    } 
  }
  
  //servo stuff
  myservo.setPeriodHertz(50);          
  myservo.attach(servoPin, 500, 2500); 
  //stepper stuff
  for (int i = 0; i < 4; i++) {
    pinMode(outPorts[i], OUTPUT);
  }
}
void loop() {
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.printf("Hi");
  Udp.endPacket();
  delay(1000);

  bool readPacket = false;
  while (!readPacket) {
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
      Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
      int len = Udp.read(incomingPacket, 255);
      if (len > 0)
      {
        incomingPacket[len] = 0;
      }
      Serial.printf("UDP packet contents: %s\n", incomingPacket);
      if (strcmp(incomingPacket,"True") == 0){
        activate = true;
      } 
    }
    if (activate == true){
      for (posVal = 0; posVal <= 180; posVal += 1) { 
        myservo.write(posVal);       
        delay(15);                   
      }
      for (posVal = 180; posVal >= 0; posVal -= 1) { 
        myservo.write(posVal);       
        delay(15);                   
      }
      moveSteps(true, 32 * 64, 3);
      delay(1000);
      activate = false;
      readPacket = true;
    }
  }
}
void moveSteps(bool dir, int steps, byte ms) {
  for (unsigned long i = 0; i < steps; i++) {
    moveOneStep(dir); 
    delay(constrain(ms,3,20));       
  }
}
void moveOneStep(bool dir) {
  static byte out = 0x01;
  if (dir) {  
    out != 0x08 ? out = out << 1 : out = 0x01;
  }
  else {     
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  for (int i = 0; i < 4; i++) {
    digitalWrite(outPorts[i], (out & (0x01 << i)) ? HIGH : LOW);
  }
}

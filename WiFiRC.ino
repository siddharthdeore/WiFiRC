/*
   Program takes compressed input from UDP and sets the value of reqired variable
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
/////////////////////////////////////

String s1, s2, s3, s4, s5, s6, s7, s0;
char Str1[3] = "X";
char Str2[3] = "Y";
char Str3[3] = "Z";
char Str4[3] = "B";
char Str5[3] = "X";
char Str6[3] = "Y";
char Str7[3] = "Z";
char Str8[3] = "B";

int Buttons; //Digital Buttons

int ch[8]; //Analog

uint32_t packetCount = 0, last_sent = 0;


#define LEDPin 2
WiFiUDP port;
const char* ssid = "ssid";
const char* password = "pass";

char packetBuffer[255];
unsigned int localPort = 2055;
boolean _ledState = 1;
//////////////////////////////////////////////
void setup() {
  pinMode(LEDPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  port.begin(localPort);

  Serial.println("\r\nConnecting to ");
  Serial.print(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    digitalWrite(2, _ledState);
    _ledState = !_ledState;
  }
  Serial.println("\r\nWiFi connected");
  Serial.print("IP");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(localPort);
}

void loop() {

  int packetSize = port.parsePacket();
  // Serial.println(packetSize);
  if (packetSize) {
    int len = port.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.println(packetBuffer);
    digitalWrite(LEDPin, HIGH);

    s1 = "";
    s2 = "";
    s3 = "";
    s4 = "";
    s5 = "";
    s6 = "";
    s7 = "";
    s0 = "";

    if (packetBuffer[0] == '#' && packetBuffer[17] == '$')
    {
      s1 = s1 + packetBuffer[1] + packetBuffer[2];
      s2 = s2 + packetBuffer[3] + packetBuffer[4];
      s3 = s3 + packetBuffer[5] + packetBuffer[5];
      s4 = s4 + packetBuffer[7] + packetBuffer[6];
      s5 = s5 + packetBuffer[9] + packetBuffer[10];
      s6 = s6 + packetBuffer[11] + packetBuffer[12];
      s7 = s7 + packetBuffer[13] + packetBuffer[14];
      s0 = s0 + packetBuffer[15] + packetBuffer[16];
    }

    if (s1.length() == 2 && s2.length() == 2)
    {
      s1.toCharArray(Str1, s1.length() + 1);
      s2.toCharArray(Str2, s2.length() + 1);
      s3.toCharArray(Str3, s3.length() + 1);
      s4.toCharArray(Str4, s4.length() + 1);
      s5.toCharArray(Str5, s5.length() + 1);
      s6.toCharArray(Str6, s6.length() + 1);
      s7.toCharArray(Str7, s7.length() + 1);
      s0.toCharArray(Str8, s0.length() + 1);

      ch[0] = String2Dec(Str1) % 4096;
      ch[1] = String2Dec(Str2) % 4096;
      ch[2] = String2Dec(Str3) % 4096;
      ch[3] = String2Dec(Str4) % 4096;
      ch[4] = String2Dec(Str5) % 4096;
      ch[5] = String2Dec(Str6) % 4096;
      ch[6] = String2Dec(Str7) % 4096;
      ch[7] = String2Dec(Str8) % 4096;
      packetCount++;

      Serial.print(packetCount);
      Serial.print(" #");
      Serial.print(s1);
      Serial.print(s2);
      Serial.print(s3);
      Serial.print(s4);
      Serial.print(s5);
      Serial.print(s6);
      Serial.print(s7);
      Serial.print(s0);
      Serial.print("$ CH0 ");     Serial.print(ch[0]);
      Serial.print(" CH1 ");      Serial.print(ch[1]);
      Serial.print(" CH2 ");      Serial.print(ch[2]);
      Serial.print(" CH3 ");      Serial.print(ch[3]);
      Serial.print(" CH4 ");      Serial.print(ch[4]);
      Serial.print(" CH5 ");      Serial.print(ch[5]);
      Serial.print(" CH6 ");      Serial.print(ch[6]);
      Serial.print(" CH7 ");      Serial.print(ch[7]);
      Serial.println();

    }
  }
  //port.beginPacket(port.remoteIP(), port.remotePort());
  //port.write("Your UDP packet was received OK\r\n");
  //port.endPacket();

  digitalWrite(LEDPin, LOW);
  delay(50);
}


/* Funcction to convert base 64 string to its decimal equivalent*/
int String2Dec(char *s)
{
  int x = 0;
  for (;;)
  {
    char chu = *s;
    if (chu >= '0')
    {
      x = x * 64 + (chu - '0');
    }
    else break;
    s++;
  }
  return x;
}

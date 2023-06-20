
#define BLYNK_TEMPLATE_ID "TMPL6Y4rxJIpb"
#define BLYNK_TEMPLATE_NAME "GasSensor"
#define BLYNK_AUTH_TOKEN "xcQ8pNURiA8fzg-WvXofACodv58k9iqX"

char ssid[] = "TurkTelekom_TP6EA0_2.4GHz";
char pass[] = "wgMvaFdAuDh7";

// define the GPIO connected with Sensors & LEDs
#define MQ2_SENSOR    35


//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <Blynk.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

int MQ2_SENSOR_Value = 0;

bool isconnected = false;
char auth[] = BLYNK_AUTH_TOKEN;

#define VPIN_BUTTON_1    V1 
#define VPIN_BUTTON_2    V2

void checkBlynkStatus() { // called every 2 seconds by SimpleTimer
  isconnected = Blynk.connected();
  if (isconnected == true) {
  
    sendData();
    //Serial.println("Blynk Connected");
  }
  else{
  
    Serial.println("Blynk Not Connected");
  }
}

void getSensorData()
{
  MQ2_SENSOR_Value = map(analogRead(MQ2_SENSOR), 0, 4095, 0, 100);

}

void sendData()
{  
  Blynk.virtualWrite(VPIN_BUTTON_1, MQ2_SENSOR_Value);
  if (MQ2_SENSOR_Value > 50 )
  {
    Blynk.logEvent("gassensorevent", String("Gaz Kaçağı Uyarısı"));
    Blynk.setProperty(VPIN_BUTTON_1, "label", "Gaz Kaçağı Derecesi");
    Serial.println("Gas Detected");
  }

}

void setup()
{
  Serial.begin(9600);
 
  pinMode(MQ2_SENSOR, INPUT);

  WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  Blynk.config(auth);
  delay(1000);
}



void loop()
{
  getSensorData();
  Blynk.run();
  timer.run();
}


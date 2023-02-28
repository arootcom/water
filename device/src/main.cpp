#include <Arduino.h>
#include "config.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <stdlib.h>
#include "HX711.h" 
#include "GyverFilters.h"
HX711 scale;
GFilterRA analog0;

const char *ssid = wifi_ssid;
const char *passwd = wifi_pass;

long lastMsg = 0;
char message[20];

float units;
float ounces;

WiFiClient wlancclient;
PubSubClient mqttClient(wlancclient); 


void mqttconnect() 
{
  while (!mqttClient.connected())
  {
    Serial.print("MQTT connecting ...");
    String clientId = "ESP8266Client";

    if(mqttClient.connect(clientId.c_str(), mqtt_login, mqtt_pass))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("faled, status code = ");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 second");

      delay(5000);
    }
  }
}

void getMA(double **x, int n, int size) {
  // size - количество отсчетов интервала усреднения
  double sumx = 0; // сумма отсчетов на интервале
  double *mas; // массив для хранения size отсчетов
  int index = 0; // индекс элемента массива
  mas = new double[size];
  for (int i = 0; i<size; i++) mas[i] = 0;
  for (int i = 0; i<n; i++) {
    sumx -= mas[index];
    mas[index] = x[1][i];
    sumx += mas[index];
    index++;
    if (index >= size)
      index = 0; // возврат к началу "окна"
    x[2][i] = sumx / size;
  }
  return;
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, passwd);
  
  scale.begin(DT, SCK);
  scale.set_scale();
  scale.tare();
  scale.set_scale(calibration_factor);

  analog0.setCoef(0.01);
  analog0.setStep(10);

  Serial.print("Connecting to AP ");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }
  Serial.print ("Connected to WiFi AP, Got an IP address :");
  Serial.print(WiFi.localIP());

  mqttClient.setServer(mqtt_server, mqtt_port);
  
}

void loop() {
  if (!mqttClient.connected())
  {
    mqttconnect();
  }

  long now = millis();
  if (now - lastMsg > 300)
  {
    for(int i = 0; i < 10; i++) {
      units += scale.get_units();
    }
    units = units / 10;
    ounces = (units * 0.035274)*10;
    Serial.print(" ");
    ounces = analog0.filteredTime(ounces);
    Serial.print(ounces);

    Serial.println(ounces);
    lastMsg = now;
    sniprintf(message, 20, "%d", (int)ceil((ounces / FULL) * 100));
    mqttClient.publish(mqtt_topic_out, message);
    mqttClient.publish(latitude_topic_out, "55");
    mqttClient.publish(longitude_topic_out, "37");
  }
}
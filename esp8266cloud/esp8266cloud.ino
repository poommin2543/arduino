#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "phinphimai" 
#define WIFI_PASSWORD "0861107657"

#define FIREBASE_HOST "databaseesp8266-42176-default-rtdb.firebaseio.com"
#define FIREBASE_KEY "A2NwKDnmBYcfzMa8BwJTb6L9lyurFKZYHPgGUzFR"
#define DHT22_Pin D5
#include "DHTesp.h"
DHTesp dht;


FirebaseData firebaseData;
bool state = false;
long randNumber;


void setup() {
    randomSeed(analogRead(0));
    connectWifi();
    Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
    dht.setup(DHT22_Pin, DHTesp::DHT22); // Connect DHT sensor to GPIO D5
}

void loop() {
    delay(dht.getMinimumSamplingPeriod());
    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();
    //state = !state;
    randNumber = random(300);
    state = !state;
    double Temperature = temperature;
    double Humidity = humidity;
    double Random = randNumber;
    
    FirebaseJson location;
    location.set("Temperature", Temperature);
    location.set("Humidity", Humidity);
    
    FirebaseJson data;
    data.set("Data", location);
    data.set("isOn", state);
    data.set("Random", Random);

    if(Firebase.setJSON(firebaseData, "/Poommin Data", data)) {
    Serial.println("Added"); 
    Serial.print("Temperature : "); 
    Serial.println(Temperature); 
    Serial.print("Humidity : "); 
    Serial.println(Humidity);
    } else {
        Serial.println("Error : " + firebaseData.errorReason());
    }
    
   /*if(Firebase.deleteNode(firebaseData, "/wio-link-01")) {
    Serial.println("Deleted"); 
    } else {
    Serial.println("Error : " + firebaseData.errorReason());
    }*/
}

void connectWifi() {
    Serial.begin(9600);
    Serial.println(WiFi.localIP());
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
}

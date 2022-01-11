#include "mainWindow.h"

// inicialização MQTT
Watchy smartWatch;

void setup(){

  Serial.begin(115200);
  Serial.println("iniciando setup...");


  // WiFiClient espClient;
  // PubSubClient client(espClient);

    
  // smartWatch.initConnect();
  smartWatch.init();
 
}


void loop(){
}

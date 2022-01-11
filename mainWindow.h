#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// bibliotecas
#include <Watchy.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

// imagens
#include "./images/italo.h"
#include "./images/jabilLogo.h"
#include "./images/displayMain.h"
#include "./images/imageBattery.h"
#include "./images/imageWifi.h"
#include "./images/imageNoWifi.h"

// relaciona os botoes e o evento de precionar aos GPIOs do relogio
#define IS_MENU             (wakeupBit & MENU_BTN_MASK && guiState == WATCHFACE_STATE)
#define IS_UP               (wakeupBit & UP_BTN_MASK && guiState == WATCHFACE_STATE)
#define IS_BACK             (wakeupBit & BACK_BTN_MASK && guiState == WATCHFACE_STATE)
#define IS_DOWN             (wakeupBit & DOWN_BTN_MASK && guiState == WATCHFACE_STATE)

// constantes
// WIFI
#define NETWORKID           "Rafael"
#define PASSW               "11112222"
// MQTT
#define MQTT_BROKER         "test.mosquitto.org"
#define MQTT_TOPIC          "jabil/smartwatch"
#define MQTT_PORT           1883

class mainWindow: public Watchy{
    public:  // variaveis globais da classe
        bool wifiEnable = false;
        bool mqttEnable = false;
     
    public: 
        mainWindow();
        
        virtual void init();
        void initConnect();
        int wifiConnect();
        // int mqttConnect();
        virtual void handleButtonPress();
        void drawWatchFace();
};


// Relaciona o estado atual do botão 
extern RTC_DATA_ATTR int guiState;

#endif 


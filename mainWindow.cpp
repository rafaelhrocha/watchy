#include "mainWindow.h"

mainWindow::mainWindow(){} //constructor

void mainWindow::init(){
    Wire.begin(SDA, SCL); //init i2c
    display.init(0, displayFullInit, 10, true);
    display.epd2.setBusyCallback(displayBusyCallback);
    initConnect();
}


void mainWindow::initConnect(){
    wifiConnect();
    // mqttConnect();
}


void mainWindow::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);

    display.drawBitmap(0, 0, epd_bitmap_main, 200, 200, GxEPD_WHITE);
    display.drawBitmap(45, 170, epd_bitmap_jabil, 110, 28, GxEPD_WHITE);
    display.drawBitmap(15, 7, epd_bitmap_battery, 26, 18, GxEPD_WHITE);

    if( wifiEnable == true){
        display.drawBitmap(165, 5, epd_bitmap_wifi , 26, 18, GxEPD_WHITE);
    }
    else{
        display.drawBitmap(165, 5, epd_bitmap_wifioff , 26, 18, GxEPD_WHITE);
    }
    

    display.setTextSize(6);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(25, 45);
    display.println("12");
    display.setCursor(105, 45);
    display.print("00");

}


void mainWindow::handleButtonPress(){

    uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

    if (IS_MENU){

        display.setFullWindow();
        display.fillScreen(GxEPD_BLACK);
        display.drawBitmap(0, 0, epd_bitmap_italo, 200, 200, GxEPD_WHITE);

        display.display(true);
        guiState = WATCHFACE_STATE;
    }
       

    if (IS_BACK){
        wifiConnect();
        showWatchFace(true);
    }   

    if (IS_UP){
        // client.publish(MQTT_TOPIC,"test");
        Serial.println("clicado;");
    }

}

int mainWindow::wifiConnect(){
     Serial.println("Iniciando Wifi function");
    if(WiFi.status() != WL_CONNECTED){
       
        WiFi.disconnect();
        WiFi.mode(WIFI_STA);
        WiFi.begin( NETWORKID, PASSW);
        // Wait for wifi to be connected
        uint32_t notConnectedCounter = 0;
        while (WiFi.status() != WL_CONNECTED) {
            delay(100);
            Serial.println("Wifi connecting...");
            notConnectedCounter++;
            if(notConnectedCounter > 150) { // Reset board if not connected after 5s
                Serial.println("No Wifi connect...");
                wifiEnable = false;
                return 0;
            }
        }
    }
    else if (WiFi.status() == WL_CONNECTED){
        Serial.print("Wifi connected, IP address: ");
        Serial.println(WiFi.localIP());
        wifiEnable = true;
    }
    return 0;
        
    
}


// int mainWindow::mqttConnect(){
    
//     if( !client.connected()){
//         uint32_t notConnectedCounter = 0;
//         while(!client.connected()){
//             delay(100);
//             Serial.println("Try connect MQTT Broker...");
//             client.setServer(MQTT_BROKER, MQTT_PORT);
//             client.connect("smartWatch");
//             notConnectedCounter++;
//             if(notConnectedCounter > 150) { // Reset board if not connected after 5s
//                 Serial.println("MQTT no connect...");
//                 wifiEnable = false;
//                 return 0;
//             }
//         }   
//     }

//     else if( client.connected()){
//         Serial.println("MQTT connected.");
//     }
//     return 0;
    
    
// }

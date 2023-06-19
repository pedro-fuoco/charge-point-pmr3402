#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOcpp.h>

#define STASSID "Fuoco"
#define STAPSK  "suxp6897"

//  Settings which worked for my SteVe instance:

#define OCPP_HOST "seven-dancers-watch.loca.lt"
#define OCPP_PORT 80
#define OCPP_URL "ws://seven-dancers-watch.loca.lt/steve/websocket/CentralSystemService/PROTOTIPO-01"

void ocpp_setup(void);

void charger_loop(void);
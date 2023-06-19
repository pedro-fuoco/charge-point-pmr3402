#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOcpp.h>
#include <freertos/queue.h>
#include "definicoes.h"

#define STASSID "Fuoco"
#define STAPSK  "suxp6897"

#define OCPP_HOST "pmr3402.loca.lt"
#define OCPP_PORT 80
#define OCPP_URL "ws://pmr3402.loca.lt/steve/websocket/CentralSystemService/PROTOTIPO-01"
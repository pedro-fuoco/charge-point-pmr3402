#include "ocpp.h"

void ocpp_setup() {
    Serial.begin(115200);

    Serial.print(F("[main] Wait for WiFi: "));


    WiFi.begin(STASSID, STAPSK);
    while (!WiFi.isConnected()) {
        Serial.print('.');
        delay(1000);
    }

    Serial.println(F(" connected!"));

    OCPP_initialize(OCPP_HOST, OCPP_PORT, OCPP_URL);

    setEnergyMeterInput([]() {
        //take the energy register of the main electricity meter and return the value in watt-hours
        return 0.f;
    });

    bootNotification("PROTOTIPO-01", "PMR3402");
}

void charger_loop() {
    while(true)
    {
        OCPP_loop();

        if (ocppPermitsCharge()) {
            //OCPP set up and transaction running. Energize the EV plug here
        } else {
            //No transaction running at the moment. De-energize EV plug
        }

        if (/* RFID chip detected? */ false) {
            String idTag = "0123456789ABCD"; //e.g. idTag = RFID.readIdTag();

            if (!getTransactionIdTag()) {
                //no idTag registered yet. Start a new transaction

                authorize(idTag.c_str(), [idTag] (JsonObject response) {
                    //check if user with idTag is authorized
                    if (!strcmp("Accepted", response["idTagInfo"]["status"] | "Invalid")){
                        Serial.println(F("[main] User is authorized to start a transaction"));

                        auto ret = beginTransaction(idTag.c_str()); //begin Tx locally

                        if (ret) {
                            Serial.println(F("[main] Transaction initiated. StartTransaction will be sent when ConnectorPlugged Input becomes true"));
                        } else {
                            Serial.println(F("[main] No transaction initiated"));
                        }
                    } else {
                        Serial.printf("[main] Authorize denied. Reason: %s\n", response["idTagInfo"]["status"] | "");
                    }
                });
                Serial.printf("[main] Authorizing user with idTag %s\n", idTag.c_str());
            } else {
                //Transaction already initiated. Check if to stop current Tx by RFID card
                if (idTag.equals(getTransactionIdTag())) {
                    //card matches -> user can stop Tx
                    Serial.println(F("[main] End transaction by RFID card"));

                    endTransaction();
                } else {
                    Serial.println(F("[main] Cannot end transaction by RFID card (different card?)"));
                }
            }
        }
    }
}
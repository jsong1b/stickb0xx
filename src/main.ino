#include "../config.h"

#include <Arduino.h>
#include <BleGamepad.h>



void scanMatrix();
void printActiveKeys(int active_keys_len);



void setup() {
    for (int i = 0; i < ROWS; i++) {
        pinMode(row_pins[i], OUTPUT);
        digitalWrite(row_pins[i], HIGH);
        for (int j = 0; j < COLS; j++) {
            active_keys_arr[i * j][0] = 0;
            active_keys_arr[i * j][1] = 0;
        }
    }
    for (int i = 0; i < COLS; i++) pinMode(col_pins[i], INPUT_PULLUP);

    Serial.begin(115200);
    delay(1000);
    Serial.println("serial up");

    ble_gamepad.begin();
    delay(1000);
    Serial.println("blekeyboard up");
}

void loop() {
    scanMatrix();
    if (print_matrix == true) printActiveKeys();

    if (ble_gamepad.isConnected() == true) {
        hybridStickLayout();
    }
    delay(10);
}



void scanMatrix() {
    active_keys_len = 0;

    for (int i = 0; i < ROWS; i++) {
        digitalWrite(row_pins[i], LOW);

        for (int j = 0; j < COLS; j++) {
            if (digitalRead(col_pins[j]) != LOW) continue;
            active_keys_arr[active_keys_len][0] = i;
            active_keys_arr[active_keys_len][1] = j;
            active_keys_len++;
        }

        digitalWrite(row_pins[i], HIGH);
    }
}

void printActiveKeys() {
    Serial.print("[");
    for (int i = 0; i < active_keys_len; i++) {
        Serial.print("{");
        Serial.print(active_keys_arr[i][0]);
        Serial.print(", ");
        Serial.print(active_keys_arr[i][1]);
        Serial.print("}");
        if (active_keys_len - 1 > i) Serial.print(", ");
    }
    Serial.print("]\n");
}
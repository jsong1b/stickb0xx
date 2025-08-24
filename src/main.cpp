#include "../config.h"

#include <Arduino.h>


int active_keys_arr[ROWS * COLS][2];

int scanMatrix();
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
    Serial.println("Serial up");
}

void loop() {
    int active_keys_len = scanMatrix();
    if (print_matrix == true) printActiveKeys(active_keys_len);
    delay(10);
}

int scanMatrix() {
    int len = 0;

    for (int i = 0; i < ROWS; i++) {
        digitalWrite(row_pins[i], LOW);

        for (int j = 0; j < COLS; j++) {
            if (digitalRead(col_pins[j]) != LOW) continue;
            active_keys_arr[len][0] = i;
            active_keys_arr[len][1] = j;
            len++;
        }

        digitalWrite(row_pins[i], HIGH);
    }

    return len;
}

void printActiveKeys(int active_keys_len) {
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
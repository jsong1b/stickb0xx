#include "../config.h"

#include <Arduino.h>
#include <BleGamepad.h>



void (*layout)(SocdCleaner) = NULL;
SocdCleaner socd_cleaner = NONE;



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
}

void loop() {
    scanMatrix();
    if (print_matrix == true) printActiveKeys();

    Serial.println(in_layout_switcher);

    if (in_layout_switcher == false) {
        in_layout_switcher = true;

        for (int i = 0; i < LAYOUT_SWITCHER_COMBO_LEN; i++) {
            if (inMatrix(layout_switcher_combo[i]) == false) {
                in_layout_switcher = false;
                break;
            }
        }

        if (in_layout_switcher == true) {
                ble_gamepad.end();
                ble_gamepad_name = "stickb0xx";
                ble_gamepad = BleGamepad(ble_gamepad_name);
                delay(1000);
            layout = NULL;
        } else (*layout)(socd_cleaner);
    } else {

        for (int i = 0; i < LAYOUTS_LEN; i++) {
            if (inMatrix(layouts_binds[i]) == true) {
                ble_gamepad_name += " - " + layouts_names[i];
                layout = layout_functions[i];
                break;
            }
        }

        bool new_socd_cleaner = false;
        for (int i = 0; i < SOCD_CLEANERS_LEN; i++) {
            if (inMatrix(socd_cleaner_binds[i]) == true) {
                ble_gamepad_name += " - " + socd_cleaner_names[i];
                socd_cleaner = (SocdCleaner)i;
                new_socd_cleaner = true;
                break;
            }
        }
        if (new_socd_cleaner == false) ble_gamepad_name += " - " + socd_cleaner_names[(int)socd_cleaner];

        if (layout != NULL) {
            ble_gamepad = BleGamepad(ble_gamepad_name);
            in_layout_switcher = false;
            ble_gamepad.begin();
            delay(1000);
        }
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
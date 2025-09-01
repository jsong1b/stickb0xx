#ifndef CONFIG_H
#define CONFIG_H

#include <BleGamepad.h>

#define ROWS 4
#define COLS 9
const int row_pins[ROWS] = {17, 19, 20, 18};
const int col_pins[COLS] = {16, 23, 22, 21, 2, 1, 0, 5, 7};
const bool print_matrix = true;

const int lever_up[2]    = {3, 0};
const int lever_down[2]  = {1, 0};
const int lever_left[2]  = {0, 0};
const int lever_right[2] = {2, 0};

const int thumb_left[2]     = {0, 2};
const int thumb_midleft[2]  = {0, 3};
const int thumb_middle[2]      = {0, 4};
const int thumb_midright[2] = {0, 5};
const int thumb_right[2]    = {0, 6};

const int left_pinky_top[2]  = {3, 1};
const int left_pinky_mid[2]  = {2, 1};
const int left_pinky_bot[2]  = {1, 1};
const int left_ring_top[2]   = {3, 2};
const int left_ring_mid[2]   = {2, 2};
const int left_ring_bot[2]   = {1, 2};
const int left_middle_top[2] = {3, 3};
const int left_middle_mid[2] = {2, 3};
const int left_middle_bot[2] = {1, 3};
const int left_index_top[2]  = {3, 4};
const int left_index_mid[2]  = {2, 4};
const int left_index_bot[2]  = {1, 4};

const int right_pinky_mid[2]  = {2, 8};
const int right_pinky_bot[2]  = {1, 8};
const int right_ring_top[2]   = {3, 7};
const int right_ring_mid[2]   = {2, 7};
const int right_ring_bot[2]   = {1, 7};
const int right_middle_top[2] = {3, 6};
const int right_middle_mid[2] = {2, 6};
const int right_middle_bot[2] = {1, 6};
const int right_index_top[2]  = {3, 5};
const int right_index_mid[2]  = {2, 5};
const int right_index_bot[2]  = {1, 5};



#define LAYOUT_SWITCHER_COMBO_LEN 5
bool in_layout_switcher = true;
const int* layout_switcher_combo[LAYOUT_SWITCHER_COMBO_LEN] = {thumb_left, thumb_midleft, thumb_middle, thumb_midright, thumb_right};

#define SOCD_CLEANERS_LEN 4
typedef enum SocdCleaner {
    NEUTRAL                  = 0,
    LRN_UDU                  = 1, /* left + right = neutral, up + down = up */
    LIP                      = 2, /* last input priority */
    B0XX_NEUTRAL_TRAVEL_TIME = 3  /* for things like melee ruleset */
} SocdCleaner;
const int* socd_cleaner_binds[SOCD_CLEANERS_LEN]  = {left_index_mid, left_middle_mid, left_ring_mid, left_pinky_mid};





/* DO NOT EDIT */
int active_keys_arr[ROWS * COLS][2];
int active_keys_len = 0;
bool inMatrix(const int *matrix_coord);

void leverLayout(SocdCleaner socd_cleaner);
void hitboxLayout(SocdCleaner socd_cleaner);
void wasdHitboxLayout(SocdCleaner socd_cleaner);
void b0xxLayout(SocdCleaner socd_cleaner);
void arcadeButtons(void);
void dpadButtons(const int* dpad_buttons[4], SocdCleaner socd_cleaner);
/* DO NOT EDIT */



BleGamepad ble_gamepad("stickb0xx");



#define LAYOUTS_LEN 4
const int* layouts_binds[LAYOUTS_LEN]              = {right_index_mid, right_middle_mid, right_ring_mid,    right_pinky_mid};
void (*layout_functions[LAYOUTS_LEN])(SocdCleaner) = {&leverLayout,    &hitboxLayout,    &wasdHitboxLayout, &b0xxLayout};

const int* lever_layout_dpad[4] = {lever_up, lever_down, lever_left, lever_right};
void leverLayout(SocdCleaner socd_cleaner) {
    arcadeButtons();
    dpadButtons(lever_layout_dpad, socd_cleaner);
    return;
}

const int* hitbox_layout_dpad[4] = {thumb_middle, left_middle_mid, left_ring_mid, left_index_mid};
void hitboxLayout(SocdCleaner socd_cleaner) {
    arcadeButtons();
    Serial.println("hitbox layout");
    dpadButtons(hitbox_layout_dpad, socd_cleaner);
    return;
}

const int* wasd_hitbox_layout_dpad[4] = {left_middle_top, left_middle_mid, left_ring_mid, left_index_mid};
void wasdHitboxLayout(SocdCleaner socd_cleaner) {
    arcadeButtons();
    dpadButtons(wasd_hitbox_layout_dpad, socd_cleaner);
    return;
}

void b0xxLayout(SocdCleaner socd_cleaner) {
    Serial.println("b0xxLayout");
    return;
}

#define ARCADE_BUTTONS_LEN 12
/* =====================================================  A                B                 X                Y                 R1/RB           R2/RT           L1/LB            L2/LT            L3               R3                START           SELECT */
const int* arcade_buttons_physical[ARCADE_BUTTONS_LEN] = {right_index_bot, right_middle_bot, right_index_mid, right_middle_mid, right_ring_mid, right_ring_bot, right_pinky_mid, right_pinky_bot, right_index_top, right_middle_top, left_pinky_top, right_ring_top};
const int arcade_buttons_binds[ARCADE_BUTTONS_LEN]     = {BUTTON_1,        BUTTON_2,         BUTTON_3,        BUTTON_4,         BUTTON_5,       BUTTON_6,       BUTTON_7,        BUTTON_8,        BUTTON_9,        BUTTON_10,        BUTTON_11,      BUTTON_12};
void arcadeButtons(void) {
    for (int i = 0; i < ARCADE_BUTTONS_LEN; i++) {
        if (inMatrix(arcade_buttons_physical[i]) == true) ble_gamepad.press(arcade_buttons_binds[i]);
        else                                              ble_gamepad.release(arcade_buttons_binds[i]);
    }
}

int cur_buttons[4] = { 0 };
void dpadButtons(const int* dpad_buttons[4], SocdCleaner socd_cleaner) {
    switch (socd_cleaner) {
    case LRN_UDU:
        if (inMatrix(dpad_buttons[0]) == true) {
            /* up */
            if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false)      ble_gamepad.setHat1(DPAD_UP_LEFT);  /* up left */
            else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_UP_RIGHT); /* up right */
            else                                                                              ble_gamepad.setHat1(DPAD_UP);       /* up */
        } else if (inMatrix(dpad_buttons[1]) == true) {
            /* down */
            if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false)      ble_gamepad.setHat1(DPAD_DOWN_LEFT);  /* down left */
            else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_DOWN_RIGHT); /* down right */
            else                                                                              ble_gamepad.setHat1(DPAD_DOWN);       /* down */
        }
        else if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false) ble_gamepad.setHat1(DPAD_LEFT);
        else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_RIGHT);
        else                                                                              ble_gamepad.setHat1(DPAD_CENTERED);

        break;
    case LIP:
        if (inMatrix(dpad_buttons[0]) == true && cur_buttons[0] == 0) {
            cur_buttons[0] = 1;
            cur_buttons[1] = -1;
        } else if (inMatrix(dpad_buttons[1]) == true && cur_buttons[1] == 0) {
            cur_buttons[1] = 1;
            cur_buttons[0] = -1;
        } else if (inMatrix(dpad_buttons[0]) == false && cur_buttons[1] == -1) {
            cur_buttons[1] = 1;
            cur_buttons[0] = 0;
        } else if (inMatrix(dpad_buttons[1]) == false && cur_buttons[0] == -1) {
            cur_buttons[0] = 1;
            cur_buttons[1] = 0;
        }

        if (inMatrix(dpad_buttons[2]) == true && cur_buttons[2] == 0) {
            cur_buttons[2] = 1;
            cur_buttons[3] = -1;
        } else if (inMatrix(dpad_buttons[3]) == true && cur_buttons[3] == 0) {
            cur_buttons[3] = 1;
            cur_buttons[2] = -1;
        } else if (inMatrix(dpad_buttons[2]) == false && cur_buttons[3] == -1) {
            cur_buttons[3] = 1;
            cur_buttons[2] = 0;
        } else if (inMatrix(dpad_buttons[3]) == false && cur_buttons[2] == -1) {
            cur_buttons[2] = 1;
            cur_buttons[3] = 0;
        }

        for (int i = 0; i < 4; i++) {
            if (inMatrix(dpad_buttons[i]) == false) cur_buttons[i] = 0;
            Serial.print(cur_buttons[i]);
            Serial.print(" ");
        }
        Serial.print("\n");

        if (cur_buttons[0] == 1 && cur_buttons[1] != 1) {
            /* up */
            if (cur_buttons[2] == 1 && cur_buttons[3] != 1)      ble_gamepad.setHat1(DPAD_UP_LEFT);  /* up left */
            else if (cur_buttons[3] == 1 && cur_buttons[2] != 1) ble_gamepad.setHat1(DPAD_UP_RIGHT); /* up right */
            else                                                 ble_gamepad.setHat1(DPAD_UP);       /* up */
        } else if (cur_buttons[1] == 1 && cur_buttons[0] != 1) {
            /* down */
            if (cur_buttons[2] == 1 && cur_buttons[3] != 1)      ble_gamepad.setHat1(DPAD_DOWN_LEFT);  /* down left */
            else if (cur_buttons[3] == 1 && cur_buttons[2] != 1) ble_gamepad.setHat1(DPAD_DOWN_RIGHT); /* down right */
            else                                                 ble_gamepad.setHat1(DPAD_DOWN);       /* down */
        }
        else if (cur_buttons[2] == 1 && cur_buttons[3] != 1) ble_gamepad.setHat1(DPAD_LEFT);
        else if (cur_buttons[3] == 1 && cur_buttons[2] != 1) ble_gamepad.setHat1(DPAD_RIGHT);
        else                                                 ble_gamepad.setHat1(DPAD_CENTERED);

        break;
    default:
        if (inMatrix(dpad_buttons[0]) == true && inMatrix(dpad_buttons[1]) == false) {
            /* up */
            if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false)      ble_gamepad.setHat1(DPAD_UP_LEFT);  /* up left */
            else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_UP_RIGHT); /* up right */
            else                                                                              ble_gamepad.setHat1(DPAD_UP);       /* up */
        } else if (inMatrix(dpad_buttons[1]) == true && inMatrix(dpad_buttons[0]) == false) {
            /* down */
            if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false)      ble_gamepad.setHat1(DPAD_DOWN_LEFT);  /* down left */
            else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_DOWN_RIGHT); /* down right */
            else                                                                              ble_gamepad.setHat1(DPAD_DOWN);       /* down */
        }
        else if (inMatrix(dpad_buttons[2]) == true && inMatrix(dpad_buttons[3]) == false) ble_gamepad.setHat1(DPAD_LEFT);
        else if (inMatrix(dpad_buttons[3]) == true && inMatrix(dpad_buttons[2]) == false) ble_gamepad.setHat1(DPAD_RIGHT);
        else                                                                              ble_gamepad.setHat1(DPAD_CENTERED);

        break;
    }

}





/* DO NOT EDIT */
bool inMatrix(const int *matrix_coord) {
    for (int i = 0; i < active_keys_len; i++) {
        if (active_keys_arr[i][0] == matrix_coord[0] && active_keys_arr[i][1] == matrix_coord[1]) {
            return true;
        }
    }
    return false;
}
/* DO NOT EDIT */

#endif // CONFIG_H
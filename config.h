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





/* DO NOT EDIT */
int active_keys_arr[ROWS * COLS][2];
int active_keys_len = 0;
bool inMatrix(const int *matrix_coord);
/* DO NOT EDIT */



BleGamepad ble_gamepad("stickb0xx", "jsong1b", 100);



const int* hybrid_stick_layout_coords[12] = {right_index_mid, right_index_bot, right_middle_mid, right_middle_bot, right_ring_mid, right_ring_bot, right_pinky_mid, right_pinky_bot, left_pinky_top, right_ring_top, right_index_top, right_middle_top};
const int hybrid_stick_layout_buttons[12] = {BUTTON_4,        BUTTON_1,        BUTTON_5,         BUTTON_2,         BUTTON_8,       BUTTON_10,      BUTTON_7,        BUTTON_9,        BUTTON_12,      BUTTON_11,      BUTTON_14,       BUTTON_15};
void hybridStickLayout() {
    for (int i = 0; i < 12; i++) {
        if (inMatrix(hybrid_stick_layout_coords[i]) == true) ble_gamepad.press(hybrid_stick_layout_buttons[i]);
        else ble_gamepad.release(hybrid_stick_layout_buttons[i]);

        /* ================  UP     DOWN   LEFT   RIGHT  ===== */
        int dpad_state[4] = {false, false, false, false};

        if (inMatrix(lever_up) == true || inMatrix(left_middle_top) == true || inMatrix(thumb_middle) == true) dpad_state[0] = true;
        if (inMatrix(lever_down) == true || inMatrix(left_middle_mid) == true)                                 dpad_state[1] = true;
        if (inMatrix(lever_left) == true || inMatrix(left_ring_mid) == true)                                   dpad_state[2] = true;
        if (inMatrix(lever_right) == true || inMatrix(left_index_mid) == true)                                 dpad_state[3] = true;

        /* LEFT + RIGHT => NEUTRAL, UP + DOWN => UP */
        if (dpad_state[0] == true) {
            if (dpad_state[2] == true && dpad_state[3] == false)      ble_gamepad.setHat1(DPAD_UP_LEFT);
            else if (dpad_state[3] == true && dpad_state[2] == false) ble_gamepad.setHat1(DPAD_UP_RIGHT);
            else                                                      ble_gamepad.setHat1(DPAD_UP);
        } else if (dpad_state[1] == true) {
            if (dpad_state[2] == true && dpad_state[3] == false)      ble_gamepad.setHat1(DPAD_DOWN_LEFT);
            else if (dpad_state[3] == true && dpad_state[2] == false) ble_gamepad.setHat1(DPAD_DOWN_RIGHT);
            else                                                      ble_gamepad.setHat1(DPAD_DOWN);
        }
        else if (dpad_state[2] == true && dpad_state[3] == false) ble_gamepad.setHat1(DPAD_LEFT);
        else if (dpad_state[3] == true && dpad_state[2] == false) ble_gamepad.setHat1(DPAD_RIGHT);
        else                                                      ble_gamepad.setHat1(DPAD_CENTERED);
    }
    const int* test = hybrid_stick_layout_coords[0];
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
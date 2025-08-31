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

#define SOCD_CLEANERS_LEN 5
typedef enum SocdCleaner {
    NONE                     = 0,
    NEUTRAL                  = 1,
    LRN_UDU                  = 2, /* left + right = neutral, up + down = up */
    LIP                      = 3, /* last input priority */
    B0XX_NEUTRAL_TRAVEL_TIME = 4  /* for things like melee ruleset */
} SocdCleaner;
const int* socd_cleaner_binds[SOCD_CLEANERS_LEN]  = {left_index_mid,     left_middle_mid, left_ring_mid,                           left_pinky_mid,             left_middle_top};
std::string socd_cleaner_names[SOCD_CLEANERS_LEN] = {"no socd cleaning", "neutral socd",  "left + right = neural, up + down = up", "last input priority socd", "b0xx - neutral socd w/ travel time"};





/* DO NOT EDIT */
int active_keys_arr[ROWS * COLS][2];
int active_keys_len = 0;
bool inMatrix(const int *matrix_coord);

void leverLayout(SocdCleaner socd_cleaner);
void hitboxLayout(SocdCleaner socd_cleaner);
void wasdHitboxLayout(SocdCleaner socd_cleaner);
void b0xxLayout(SocdCleaner socd_cleaner);
/* DO NOT EDIT */



std::string ble_gamepad_name = "stickb0xx";
BleGamepad ble_gamepad(ble_gamepad_name);



#define LAYOUTS_LEN 4
const int* layouts_binds[LAYOUTS_LEN]              = {right_index_mid, right_middle_mid, right_ring_mid,        right_pinky_mid};
void (*layout_functions[LAYOUTS_LEN])(SocdCleaner) = {&leverLayout,    &hitboxLayout,    &wasdHitboxLayout,     &b0xxLayout};
std::string layouts_names[LAYOUTS_LEN]             = {"lever layout",  "hitbox layout",  "wasd hitbox layout", "b0xx layout"};



void leverLayout(SocdCleaner socd_cleaner) {
    Serial.println("leverLayout");
    return;
}

void hitboxLayout(SocdCleaner socd_cleaner) {
    Serial.println("hitboxLayout");
    return;
}

void wasdHitboxLayout(SocdCleaner socd_cleaner) {
    Serial.println("wasdHitboxLayout");
    return;
}

void b0xxLayout(SocdCleaner socd_cleaner) {
    Serial.println("b0xxLayout");
    return;
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
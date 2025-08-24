#ifndef CONFIG_H
#define CONFIG_H

const bool print_matrix = true;

#define ROWS 4
#define COLS 9
const int row_pins[ROWS] = {18, 20, 19, 17};
const int col_pins[COLS] = {16, 23, 22, 21, 2, 1, 0, 5, 7};

#define LAYOUT_SWITCH_LEN 5
const int layer_switch_combo[LAYOUT_SWITCH_LEN][2] = {{0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}};

#endif // CONFIG_H
/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2020 Ploopy Corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_BTN1, KC_BTN3, KC_BTN3,
          KC_BTN2, KC_BTN4
    ),
    /* 1    Right lower
     * 2    Right upper
     * 3    Right middle
     * 4    Left 
     */
};

//#undef PRINTF_SUPPORT_DECIMAL_SPECIFIERS
//#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS 1
//#include "print.h"

float x_rem = 0.0;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    const float cos_theta = 0.866025;
    const float sin_theta = 0.500000;
    
    float x_new = mouse_report.x * cos_theta - mouse_report.y * sin_theta + x_rem;

    mouse_report.x = x_new;
    x_rem = x_new - mouse_report.x;

    return mouse_report;
}

//void keyboard_post_init_user(void) {
//  // Customise these values to desired behaviour
//  debug_enable=true;
//  debug_matrix=true;
//  //debug_keyboard=true;
//  debug_mouse=true;
//}


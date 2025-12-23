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
    // Layout indexes correspond to physical buttons (left handed mouse).
    // Values assigned to these indexes indicate button functions.
    //
    // BTN1 = primary click
    // BTN2 = "right"/secondary click
    // BTN3 = middle click
    // BTN4 = extra (previous page)
    // BTN5 = extra (next page)
    [0] = LAYOUT(
        KC_BTN1, // Physical right-side lower (primary click)
        KC_BTN3, // Physical right-side upper (middle click)
        KC_BTN3, // Physical right-side middle scroll wheel (middle click)
        KC_BTN2, // Physical left-side upper ("right"/secondary click)
        KC_BTN4  // Physical left-side lower (extra)
    ),
};

float x_rem = 0.0;
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    /* Correction to vertical (up and down) mouse movements which
     * skew counterclockwise while horizontal (left and right) movements
     * remain level. This is a typical "rotate a point about the origin"
     * problem with the following corresponding formulas.
     *
     *     x1 = x0 * cos(theta) - y0 * sin(theta)
     *     y1 = x0 * sin(theta) + y0 * cos(theta)
     *
     *  Since the adjustment is only needed for vertical movements, only
     *  the x value is modified to compensate for being off axis. This
     *  essentially makes the vertical and horizontal axis
     *  non-perpendicular
     */

    // 30 degrees clockwise
    const float cos_theta = 0.866025;  // cos(30)
    const float sin_theta = 0.500000;  // sin(30)

    // New X value after adjusting 30 degrees clockwise (with remaining value
    // from previous report to compensate for int return type)
    float x_new = mouse_report.x * cos_theta - mouse_report.y * sin_theta + x_rem;

    mouse_report.x = x_new;
    // mouse_report.x is an integer but the new X value is a float
    // so record the difference to apply for next time. This smoothes
    // out horizontal (y=0) movements preventing "sticking" from partial
    // values being disregarded.
    x_rem = x_new - mouse_report.x;

    return mouse_report;
}

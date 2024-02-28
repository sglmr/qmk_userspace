/* Copyright 2020 gtips
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

enum custom_keycodes {
  CMD_SH_4 = SAFE_RANGE, 
  SAVE,
  SEL_ALL,
  UNDO,
  CUT,
  COPY,
  PASTE,
  // other custom keycodes can follow
};

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _MACRO,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define MACRO  MO(_MACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  RSFT_T(KC_ENT),
                                            KC_LALT,   LOWER,    KC_SPC,   RAISE,    KC_RGUI
  ),
  
  [_LOWER] = LAYOUT(
    KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
    _______,  KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,   KC_MINS,            XXXXXXX,  KC_LEFT,  KC_UP,    KC_RGHT,  XXXXXXX,  KC_BSLS,
    KC_LSFT,  UNDO,     CUT,      COPY,     PASTE,     XXXXXXX,            KC_HOME,  KC_END,   KC_DOWN,  KC_DOT,   XXXXXXX,  RSFT_T(KC_ENT),
                                            _______,   _______,  KC_ENT,   _______,  _______
  ),
  
  [_RAISE] = LAYOUT(
    KC_ESC,   KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,    KC_PERC,            KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
    _______,  KC_TILD,  KC_PLUS,  KC_LCBR,  KC_RCBR,   KC_UNDS,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PIPE,
    KC_CAPS,  UNDO,     CUT,      COPY,     PASTE,     XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),

  [_MACRO] = LAYOUT(
    XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX,  CMD_SH_4,  XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_PAUSE, XXXXXXX,
    XXXXXXX,  SEL_ALL,  SAVE,    XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
  
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _MACRO);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Cmd+Shift+4 for a screenshot shortcut
    case CMD_SH_4:
      if (record->event.pressed) {
        // when keycode CMD_SHIFT_4 is pressed
        SEND_STRING(SS_LGUI(SS_LSFT("4"))); // This sends CMD+Shift+4
      } 
      return false; // Skip all further processing of this key
    // Cmd+s for a save shortcut
    case SAVE:
      if (record->event.pressed) {
        // when keycode CMD_S is pressed
        SEND_STRING(SS_LGUI("s")); // This sends CMD+s
      }
      return false; // Skip all further processing of this key
    // Cmd+a for select all
    case SEL_ALL:
      if (record->event.pressed) {
        // when keycode SEL_ALL is pressed
        SEND_STRING(SS_LGUI("a")); // This sends CMD+a
      }
      return false; // Skip all further processing of this key
    // Cmd+z for undo
    case UNDO:
      if (record->event.pressed) {
        // when keycode UNDO is pressed
        SEND_STRING(SS_LGUI("z")); // This sends CMD+z
      }
      return false; // Skip all further processing of this key
    // Cmd+x for Cut
    case CUT:
      if (record->event.pressed) {
        // when keycode CUT is pressed
        SEND_STRING(SS_LGUI("x")); // This sends CMD+x
      }
      return false; // Skip all further processing of this key
    // Cmd+c for Copy
    case COPY:
      if (record->event.pressed) {
        // when keycode COPY is pressed
        SEND_STRING(SS_LGUI("c")); // This sends CMD+c
      }
      return false; // Skip all further processing of this key
    // CMD+v for Paste
    case PASTE:
      if (record->event.pressed) {
        // when keycode COPY is pressed
        SEND_STRING(SS_LGUI("v")); // This sends CMD+v
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}


#pragma once
#ifndef InputMappings_HPP
#define InputMappings_HPP

namespace SM
{
#define NUM_KEY_STATES   380
#define NUM_MOUSE_STATES 8

#define MOUSE_1      0
#define MOUSE_2      1
#define MOUSE_3      2
#define MOUSE_4      3
#define MOUSE_5      4
#define MOUSE_6      5
#define MOUSE_7      6
#define MOUSE_8      7
#define MOUSE_LAST   MOUSE_8
#define MOUSE_LEFT   MOUSE_1
#define MOUSE_RIGHT  MOUSE_2
#define MOUSE_MIDDLE MOUSE_3

#define JOYSTICK_1    0
#define JOYSTICK_2    1
#define JOYSTICK_3    2
#define JOYSTICK_4    3
#define JOYSTICK_5    4
#define JOYSTICK_6    5
#define JOYSTICK_7    6
#define JOYSTICK_8    7
#define JOYSTICK_9    8
#define JOYSTICK_10   9
#define JOYSTICK_11   10
#define JOYSTICK_12   11
#define JOYSTICK_13   12
#define JOYSTICK_14   13
#define JOYSTICK_15   14
#define JOYSTICK_16   15
#define JOYSTICK_LAST JOYSTICK_16

#define GAMEPAD_A            0
#define GAMEPAD_B            1
#define GAMEPAD_X            2
#define GAMEPAD_Y            3
#define GAMEPAD_LEFT_BUMPER  4
#define GAMEPAD_RIGHT_BUMPER 5
#define GAMEPAD_BACK         6
#define GAMEPAD_START        7
#define GAMEPAD_GUIDE        8
#define GAMEPAD_LEFT_THUMB   9
#define GAMEPAD_RIGHT_THUMB  10
#define GAMEPAD_DPAD_UP      11
#define GAMEPAD_DPAD_RIGHT   12
#define GAMEPAD_DPAD_DOWN    13
#define GAMEPAD_DPAD_LEFT    14
#define GAMEPAD_DPAD_LAST    GLFW_GAMEPAD_DPAD_LEFT

#define GAMEPAD_CROSS    GAMEPAD_A
#define GAMEPAD_CIRCLE   GAMEPAD_B
#define GAMEPAD_SQUARE   GAMEPAD_X
#define GAMEPAD_TRIANGLE GAMEPAD_Y

#define GAMEPAD_LEFT_X        0
#define GAMEPAD_LEFT_Y        1
#define GAMEPAD_RIGHT_X       2
#define GAMEPAD_RIGHT_Y       3
#define GAMEPAD_LEFT_TRIGGER  4
#define GAMEPAD_RIGHT_TRIGGER 5
#define GAMEPAD_LAST          GAMEPAD_RIGHT_TRIGGER

#define KEY_UNKNOWN -1
#define KEY_A       65
#define KEY_B       66
#define KEY_C       67
#define KEY_D       68
#define KEY_E       69
#define KEY_F       70
#define KEY_G       71
#define KEY_H       72
#define KEY_I       73
#define KEY_J       74
#define KEY_K       75
#define KEY_L       76
#define KEY_M       77
#define KEY_N       78
#define KEY_O       79
#define KEY_P       80
#define KEY_Q       81
#define KEY_R       82
#define KEY_S       83
#define KEY_T       84
#define KEY_U       85
#define KEY_V       86
#define KEY_W       87
#define KEY_X       88
#define KEY_Y       89
#define KEY_Z       90

#define KEY_0 48
#define KEY_1 49
#define KEY_2 50
#define KEY_3 51
#define KEY_4 52
#define KEY_5 53
#define KEY_6 54
#define KEY_7 55
#define KEY_8 56
#define KEY_9 57

#define KEY_RETURN    257
#define KEY_ESCAPE    256
#define KEY_BACKSPACE 259
#define KEY_TAB       258
#define KEY_SPACE     32

#define KEY_MINUS        45
#define KEY_EQUALS       61
#define KEY_LEFTBRACKET  91
#define KEY_RIGHTBRACKET 93
#define KEY_BACKSLASH    92

#define KEY_SEMICOLON  59
#define KEY_APOSTROPHE 39
#define KEY_GRAVE      96

#define KEY_COMMA    44
#define KEY_PERIOD   46
#define KEY_SLASH    47
#define KEY_CAPSLOCK 280

#define KEY_F1  290
#define KEY_F2  291
#define KEY_F3  292
#define KEY_F4  293
#define KEY_F5  294
#define KEY_F6  295
#define KEY_F7  296
#define KEY_F8  297
#define KEY_F9  298
#define KEY_F10 299
#define KEY_F11 300
#define KEY_F12 301

#define KEY_PRINTSCREEN KEY_UNKNOWN
#define KEY_SCROLLLOCK  281
#define KEY_PAUSE       284
#define KEY_INSERT      260

#define KEY_HOME         268
#define KEY_PAGEUP       266
#define KEY_DELETE       261
#define KEY_END          269
#define KEY_PAGEDOWN     267
#define KEY_RIGHT        262
#define KEY_LEFT         263
#define KEY_DOWN         264
#define KEY_UP           265
#define KEY_NUMLOCKCLEAR 282

#define KEY_KP_DECIMAL  330
#define KEY_KP_DIVIDE   331
#define KEY_KP_MULTIPLY 332
#define KEY_KP_MINUS    333
#define KEY_KP_PLUS     334
#define KEY_KP_ENTER    335
#define KEY_KP_1        321
#define KEY_KP_2        322
#define KEY_KP_3        323
#define KEY_KP_4        324
#define KEY_KP_5        325
#define KEY_KP_6        326
#define KEY_KP_7        327
#define KEY_KP_8        328
#define KEY_KP_9        329
#define KEY_KP_0        320

#define KEY_F13 302
#define KEY_F14 303
#define KEY_F15 304
#define KEY_F16 305
#define KEY_F17 306
#define KEY_F18 307
#define KEY_F19 308
#define KEY_F20 309
#define KEY_F21 310
#define KEY_F22 311
#define KEY_F23 312
#define KEY_F24 313

#define KEY_LCTRL  341
#define KEY_LSHIFT 340
#define KEY_LALT   342
#define KEY_LGUI   343
#define KEY_RCTRL  345
#define KEY_RSHIFT 344
#define KEY_RALT   346
#define KEY_RGUI   347

} // namespace SM

#endif

#define BUTT_PIN 13                                 //пин для считывания кнопок
#define DOT_PIN 5                                   //пин для считывания кнопок

#define DEBOUNCE 200                                // таймаут антидребезга, миллисекунды
// ---------- ЯРКОСТЬ ---------- //
#define NIGHT_LIGHT 1                               // менять яркость от времени суток (1 вкл, 0 выкл)
#define NIGHT_START 23                              // час перехода на ночную подсветку (BRIGHT_N)
#define NIGHT_END 7                                 // час перехода на дневную подсветку (BRIGHT)

int8_t FLIP_EFFECT = 0;
#define FLIP_SPEED_1 18                             // скорость эффекта 1, мс
#define FLIP_SPEED_2 50                             // скорость эффекта 2, мс
//#define FLIP_SPEED_3 167                          // скорость эффекта 2, мс

#define INDI_BRIGHT 24                              // яркость цифр дневная (0 - 24) !на 24 могут быть фантомные цифры!
#define INDI_BRIGHT_N 6                             // яркость ночная (0 - 24)

#define BACKLIGHT_BRIGHT 1.0                        // яркость подсветки  дневная (0 - 1.0)
#define BACKLIGHT_BRIGHT_N 0.4                      // яркость ночная (0 - 1.0)

// --------- ДРУГОЕ -------- //
#define BURN_TIME 45                                // период обхода в режиме очистки, мс

#include <GyverTimer.h>                             // библиотека для задержек
#include <RTClib.h>                                 // библиотека для RTC модуля
#include <Wire.h>                                   // i2s library

RTC_DS3231 rtc;

GTimer_ms burnTimer(BURN_TIME);
GTimer_ms returnBlinkTimer(2000);
GTimer_ms dotTimer(500);                            // полсекундный таймер для часов
GTimer_ms flipTimer(FLIP_SPEED_1);
GTimer_ms blinkTimer(400);
GTimer_ms debounceTimer(DEBOUNCE);

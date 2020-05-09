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

const int8_t VT_pin[] = {12, 8, 7, 6, 2, 4};                // выводы для транзисторных ключей
const byte def_pin[] = {A0, A2, A1, A3};                    //выводы для дешифратора defPin[out1,out2,out4,out8];
const int8_t mass_led[] = {9, 10, 11};                      //массив с пинами светодиодов
int8_t led_color[] = {0, 0, 0};                             //массив с цветами светодиодов
const int8_t digitMask[] = {9, 8, 0, 5, 6, 3, 2, 7, 4, 1};  //подключение индикатора
boolean anodeStates[] = {1, 1, 1, 1, 1, 1};

volatile byte mass_but[] = {0, 0, 0, 0};             //массив для состояние кнопок
volatile int8_t time_date[6];                        // массив где хранится временя или дата
volatile byte curIndi = 0;                           // текущий индикатор (0-5)
volatile byte indiCounter[6];                        // счётчик каждого индикатора (0-24)
volatile byte indiDimm[6];                           // яркость каждого индикатора
uint8_t newTime[6];                                  //for effects
boolean flipIndics[6];

boolean dotFlag;                                     // полсекундный флаг для часов
byte hrs, mins, secs, days, months;
int16_t years;
int16_t changedTime[3];                              //[Hour_Day, Minutes_Month, Seconds_Year]
byte indiMaxBright = INDI_BRIGHT;
float bright_lvl = BACKLIGHT_BRIGHT;
boolean newTimeFlag;
byte curMode = 0;                                               // 0 - time, 1 - set time
boolean flipInit;
boolean changeDate = false;                                             // change to date or time
boolean indiBrightDirection;
boolean changeEffects;                                          // for change effects
int8_t indiBrightCounter;
boolean lampState = false;                                      //for blimming lamp

//переменные для светодиодов
unsigned long last_step = 0;
short ihue = 0;
int8_t c = 0;
byte fl_color = 0;                                           // on/off подсветки

//only for buttons func
byte currentDigit = 0;
bool dontblink = false;

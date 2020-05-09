
const int8_t VT_pin[] = {12, 8, 7, 6, 2, 4};                // выводы для транзисторных ключей
const byte def_pin[] = {A0, A2, A1, A3};                    //выводы для дешифратора defPin[out1,out2,out4,out8];
const int8_t mass_led[] = {9, 10, 11};                      //массив с пинами светодиодов
short led_color[] = {0, 0};                             //массив с цветами светодиодов
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
bool smth_do = false;

//only for buttons func
byte currentDigit = 0;
bool dontblink = false;

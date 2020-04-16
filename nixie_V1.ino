
void setup() {
 //Serial.begin(9600);
  s_timer();
  analogWrite(3, 80);                                           // если запитывать от блока питания 9в
  s_pins();
  s_RTC();
  sendTime(hrs, mins, secs);
  changeBright();
  changeEffects = true;
}

void loop() {
  if (dotTimer.isReady()) calculateTime();                      // каждые 500 мс пересчёт и отправка времени
  if (newTimeFlag && curMode == 0) flipTick();                  // ефекты перелистивания цыфр
  button();                                                     // check the buttons
  set_color(fl_color);                                          // подсветка
}

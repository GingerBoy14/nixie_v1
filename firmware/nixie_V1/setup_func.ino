void s_timer() {
  cli();                               //запрещаем прерывания для натройки таймеров
  TCCR1B = (TCCR1B & B11111000) | 2;
  TCCR1B |= (1 << WGM12);              // CTC
  TIMSK1 |= (1 << OCIE1A);             // Output Compare Match A Interrupt Enable
  TCCR2B = TCCR2B & 0b11111000 | 0x01; // задаем частоту ШИМ на 3 выводе 30кГц
  sei();
}

void s_pins() {
  //задаем режим работы выходов микроконтроллера
  for (byte i = 0; i < 4; i++) {
    pinMode(def_pin[i], OUTPUT);
  }
  for (byte i = 0; i < 6; i++) {
    pinMode(VT_pin[i], OUTPUT);
  }
  pinMode(BUTT_PIN, INPUT);
  pinMode(DOT_PIN, OUTPUT);

}

void s_RTC(){
  Wire.begin();
  rtc.begin();
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
//rtc.adjust(DateTime(19,9,18,0,14,0));
  DateTime now = rtc.now();
  secs = now.second();
  mins = now.minute();
  hrs = now.hour();
  years = now.year();
  months = now.month();
  days = now.day();
}

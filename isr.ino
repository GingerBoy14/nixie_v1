ISR(TIMER1_COMPA_vect) {
  if (curIndi < 4) mass_but[curIndi] = readPin(BUTT_PIN); //проверка кнопок
  indiCounter[curIndi]++;                         // счётчик индикатора
  if (indiCounter[curIndi] >= indiDimm[curIndi])  // если достигли порога диммирования
    setPin(VT_pin[curIndi], LOW);               // выключить текущий индикатор

  if (indiCounter[curIndi] > 25) {                // достигли порога в 25 единиц
    indiCounter[curIndi] = 0;                     // сброс счетчика индикатора
    if (++curIndi >= 6)  curIndi = 0;

    // отправить цифру из массива time_date согласно типу лампы
       if (indiDimm[curIndi] > 0) {
      for (int8_t i = 0; i < 4; i++) {
        setPin(def_pin[i], bitRead(digitMask[time_date[curIndi]], i));
      }
      setPin(VT_pin[curIndi], anodeStates[curIndi]);            // включить анод на текущую лампу
     }
  }
}

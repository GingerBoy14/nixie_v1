void changeBright() {
#if (NIGHT_LIGHT == 1)                    // установка яркости всех светилок от времени суток
  if ( (hrs >= NIGHT_START && hrs <= 23)
       || (hrs >= 0 && hrs < NIGHT_END) ) {
    indiMaxBright = INDI_BRIGHT_N;
    bright_lvl = BACKLIGHT_BRIGHT_N;
  } else {
    indiMaxBright = INDI_BRIGHT;
    bright_lvl = BACKLIGHT_BRIGHT;
  }
  for (byte i = 0; i < 6; i++) {
    indiDimm[i] = indiMaxBright;
  }
  indiBrightCounter = indiMaxBright;
#endif
}

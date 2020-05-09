void flipTick() {
  if (FLIP_EFFECT == 0) {
    sendTime(hrs, mins, secs);
    newTimeFlag = false;
  }
  else if (FLIP_EFFECT == 1) {
    if (!flipInit) {
      flipInit = !flipInit;
      // запоминаем, какие цифры поменялись и будем менять их яркость
      for (byte i = 0; i < 6; i++) {
        if (time_date[i] != newTime[i]) flipIndics[i] = true;
        else flipIndics[i] = false;
      }
    }
    if (flipTimer.isReady()) {
      if (!indiBrightDirection) {
        indiBrightCounter--;                              // уменьшаем яркость
        if (indiBrightCounter <= 0) {                      // если яроксть меньше нуля
          indiBrightDirection = true;     // меняем направление изменения
          indiBrightCounter = 0;                          // обнуляем яркость
          sendTime(hrs, mins, secs);                      // меняем цифры
        }
      } else {
        indiBrightCounter++;                                     // увеличиваем яркость
        if (indiBrightCounter >= indiMaxBright) {                 // достигли предела
          indiBrightDirection = false;            // меняем направление
          indiBrightCounter = indiMaxBright;                     // устанавливаем максимум
          // выходим из цикла изменения
          flipInit = false;
          newTimeFlag = false;
        }
      }
    }
    for (byte i = 0; i < 6; i++)
     if (flipIndics[i])  indiDimm[i] = indiBrightCounter;   // применяем яркость
  }
  else if (FLIP_EFFECT == 2) {
    if (!flipInit) {
      flipInit = true;
      // запоминаем, какие цифры поменялись и будем менять их
      for (byte i = 0; i < 6; i++) {
        if (time_date[i] != newTime[i]) flipIndics[i] = true;
        else flipIndics[i] = false;
      }
    }

    if (flipTimer.isReady()) {
      byte flipCounter = 0;
      for (byte i = 0; i < 6; i++) {
        if (flipIndics[i]) {
          time_date[i]--;
          if (time_date[i] < 0) time_date[i] = 9;
          if (time_date[i] == newTime[i]) flipIndics[i] = false;
        } else {
          flipCounter++;        // счётчик цифр, которые не надо менять
        }
      }
      if (flipCounter == 6) {   // если ни одну из 6 цифр менять не нужно
        // выходим из цикла изменения
        flipInit = !flipInit;
        newTimeFlag = false;
      }
    }
  }
  // else if (FLIP_EFFECT == 3) {    /*******************dotEffect balance wheel**********************/
  //   if(!setting_flag && !f){//если "время" - бегать
  //      if (dotScroll.isReady() && !change) {
  //    roll++;//right
  //    if(roll==5){ change = !change; }//turning
  //  }else if(dotScroll.isReady() && change){
  //        roll--;//left
  //        if(roll==0){ change = !change; }//turning
  //  }
  //  if(i == roll && flag){//"оставатся" на одном индикаторе 1/6 секунды
  //     digitalWrite(A0, HIGH);
  //  }
  //  else{//не светить на остальных
  //     digitalWrite(A0, LOW);
  //  }
  //
  // }else if(!flag && f){//если "дата" - просто светить
  //     digitalWrite(A0, HIGH);
  //  }
  //  if(open_scroll) {//если прокрутка - не светить
  //     digitalWrite(A0, LOW);
  //  }
  //  }
  //else if (FLIP_EFFECT == 4) {    /*******************dotEffect snake**********************/
  // if(!setting_flag && !f){//если "время" - бегать
  //      if (millis() - last_blink >= 167 && !change) {
  //         if(m == 6){
  //          g[n] = 0;
  //            n++;
  //             if(n == 6){change = !change; m--;n--;}
  //            }else{
  //               g[m] = 1;
  //               m++;
  //    //turning
  //    }last_blink = millis();
  //  }else if(millis() - last_blink >= 167 && change){
  //  if(m < 0){
  //          g[n] = 0;
  //            n--;
  //             if(n < 0){change = !change; m++;n++;}
  //            }else{
  //        g[m] = 1;
  //            m--;
  //       //turning
  //     } last_blink = millis();
  //  }
  //
  //  if(g[i]==1 && flag){//"оставатся" на одном индикаторе 1/6 секунды
  //     digitalWrite(A0, HIGH);
  //  }else if(g[i] == 0){
  //         digitalWrite(A0, LOW);
  //  }
  //
  //
  //}else if(!flag && f){//если "дата" - просто светить
  //     digitalWrite(A0, HIGH);
  //  }
  //  if(open_scroll) {//если прокрутка - не светить
  //     digitalWrite(A0, LOW);
  //  }
  //  }
  //else if (FLIP_EFFECT == 5) {    /*******************dotEffect blink**********************/
  //  if (dotFlag && flag) {
  //if(state == LOW){
  //  state = HIGH;
  //}else{
  //  state = LOW;
  //}
  //    digitalWrite(A0, state);//подаем сигнал на keysPin[i] индикатор
  //last_blink = millis();
  //  }else if(!flag){
  //        digitalWrite(A0, HIGH);//подаем сигнал на keysPin[i] индикатор
  //  }
  //  }
}


void burnIndicators() {

    for (byte d = 0; d < 10;){
        if (burnTimer.isReady())d++;
      for (byte i = 0; i < 6; i++) {
        anodeStates[i] = 1;
        time_date[i] = d;
    }
  }
}

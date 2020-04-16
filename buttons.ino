

void button() {
  settingBlink();
  if ( (mass_but[0] || mass_but[1] || mass_but[2] || mass_but[3])
  && debounceTimer.isReady()) {
    if (curMode == 0) { //time and some function
      Funcrions();
    }else if(curMode == 1){ //settings
      settingsFunctions();
    }
  }  else if (!(mass_but[1] && mass_but[2])
  && dontblink && returnBlinkTimer.isReady()) {
    dontblink = false;
  }
}

void settingBlink(){
  if(curMode == 1 && blinkTimer.isReady() && !dontblink){
    lampState = !lampState;
    switch (currentDigit) {                               //мигаем выбранным разрядом
      case 0:{
        anodeStates[4] = 0;
        anodeStates[5] = 0;
        break;
      }
      case 1:{
        anodeStates[3] = 0;
        anodeStates[2] = 0;
        break;
      }
      case 2:{
        anodeStates[1] = 0;
        anodeStates[0] = 0;
        break;
      }
    }
  }else if (lampState || curMode == 0 || dontblink) {
    for (byte i = 0; i < 6; i++) {
      anodeStates[i] = 1;
    }
  }
}

bool smth_do = false;
void settingsFunctions(){

  if (mass_but[0]) {
    if(currentDigit == 2) {
      currentDigit = 0;
    }else{
      currentDigit++;
    }
  }else
  if (mass_but[3]) {
      curMode = 0;
      currentDigit = 0;
  }else
  if (mass_but[1]) {
    confPlus();
    dontblink = true;
    smth_do = true;
  }else
  if (mass_but[2]) {
    confMinus();
    dontblink = true;
    smth_do = true;
  }
  if (smth_do){
       acceptNewTime(changedTime[0], changedTime[1], changedTime[2]);
  }
}

void Funcrions(){
  if (mass_but[0]) {
    flipTick();
    changeDate = !changeDate;
    DateTime now = rtc.now();
    if (changeDate) {
      years = now.year();
      months = now.month();
      days = now.day();
      sendDate(days, months, years);
    } else {
      secs = now.second();
      mins = now.minute();
      hrs = now.hour();
      sendTime(hrs, mins, secs);
    }

  }
  if (mass_but[1]){
    for (byte i = 0; i < 6; i++) indiDimm[i] = indiMaxBright;   // применяем яркость
    if (FLIP_EFFECT == 0 || FLIP_EFFECT == 2) {
      changeEffects = !changeEffects;
    }
    if(!changeEffects){
      FLIP_EFFECT++;
    }else{
      FLIP_EFFECT = 0;
    }

    switch (FLIP_EFFECT) {
      case 0:  break;
      case 1:  flipTimer.setInterval(FLIP_SPEED_1);break;
      case 2:  flipTimer.setInterval(FLIP_SPEED_2);break;
    }
  }

  if (mass_but[2]){
     if(fl_color == 2) {
      fl_color = 0;
    }else{
      fl_color++;
    }
    set_color(fl_color);
  }
  if (mass_but[3]) {
    if (changeDate) {                                   // will be change the date
      changedTime[2] = years;
      changedTime[1] = months;
      changedTime[0] = days;
    } else {                                            // will be change the time
      changedTime[2] = secs;
      changedTime[1] = mins;
      changedTime[0] = hrs;
    }
    curMode = 1;
  }
}



void confPlus(){
  if (changeDate) {                                // will be change the date
    switch (currentDigit) {
      case 0:{
        changedTime[2]++;
        if (changedTime[2] > 2099) {
          changedTime[2] = 2000;
        }
        break;
      }
      case 1:{
        changedTime[1]++;
        if (changedTime[1] > 12) {
          changedTime[1] = 1;
          changedTime[2]++;
        }
        break;
      }
      case 2:{
        byte daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        changedTime[0]++;
        if(changedTime[0] > daysInMonth[changedTime[1]-1]){
          changedTime[0] = 1;
          changedTime[1]++;
        }
        break;
      }
    }

  } else {                                            // will be change the time
    switch (currentDigit) {
      case 0:{
         changedTime[2]++;
        if ( changedTime[2] > 59) {
           changedTime[2] = 0;
          changedTime[1]++;
          if (changedTime[1] > 59) changedTime[1] = 0;
        }
        break;
      }
      case 1:{
        changedTime[1]++;
        if (changedTime[1] > 59) {
          changedTime[1] = 0;
           changedTime[0]++;
          if ( changedTime[0] > 23) changedTime[0] = 0;
        }
        break;
      }
      case 2:{
        changedTime[0]++;
        if (changedTime[0] > 23) changedTime[0] = 0;
        break;
      }
    }
  }
}



void confMinus(){
  if (changeDate) {                                    // will be change the date
    switch (currentDigit) {
      case 0:{
        changedTime[2]--;
        if (changedTime[2] < 2000) {
          changedTime[2] = 2099;
        }
        break;
      }
      case 1:{
        changedTime[1]--;
        if (changedTime[1] < 1) {
          changedTime[1] = 12;
          changedTime[2]--;
        }
        break;
      }
      case 2:{
        byte daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        changedTime[0]--;
        if(changedTime[0] == 0){  changedTime[1]--;
          changedTime[0] = daysInMonth[changedTime[1]-1];
        }
        break;
      }
    }

  } else {                                            // will be change the time
    switch (currentDigit) {
      case 0:{
        changedTime[2]--;
        if (changedTime[2] < 0) {
          changedTime[2] = 59;
          changedTime[1]--;
          if (changedTime[1] < 0) changedTime[1] = 59;
        }
        break;
      }
      case 1:{
        changedTime[1]--;
        if (changedTime[1] < 0) {
          changedTime[1] = 59;
          changedTime[0]--;
          if (changedTime[0] < 0) changedTime[0] = 23;
        }
        break;
      }
      case 2:{
        changedTime[0]--;
        if (changedTime[0] < 0) changedTime[0] = 23;
        break;
      }
    }
  }
}

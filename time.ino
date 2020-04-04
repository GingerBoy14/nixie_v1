void sendTime(byte hours, byte minutes, byte seconds) {
    time_date[0] = (byte)hours / 10;
    time_date[1] = (byte)hours % 10;

    time_date[2] = (byte)minutes / 10;
    time_date[3] = (byte)minutes % 10;

    time_date[4] = (byte)seconds / 10;
    time_date[5] = (byte)seconds % 10;
}

void sendDate(byte day, byte month, short year) {
    time_date[0] = (byte)day / 10;
    time_date[1] = (byte)day % 10;

    time_date[2] = (byte)month / 10;
    time_date[3] = (byte)month % 10;

    short buf = year / 10 % 10;
    time_date[4] = (byte)buf;
    buf = year % 10;
    time_date[5] = (byte)buf;
}


// для эффектов
void setNewTime() {
    newTime[0] = (byte)hrs / 10;
    newTime[1] = (byte)hrs % 10;

    newTime[2] = (byte)mins / 10;
    newTime[3] = (byte)mins % 10;

    newTime[4] = (byte)secs / 10;
    newTime[5] = (byte)secs % 10;
}

void acceptNewTime(short d_h, short m_m, short y_s){
    if (changeDate) {         // will be change the date
        years = y_s;
        months = m_m;
        days = d_h;
        sendDate(days, months, years);

    } else {        // will be change the time
        secs = y_s;
        mins = m_m;
        hrs = d_h;
        sendTime(hrs, mins, secs);
    }
    if(curMode == 0) rtc.adjust(DateTime(years,months,days,hrs,mins,secs));             //только после выхода из настроек
}

void calculateTime() {
    dotFlag = !dotFlag;
    if (dotFlag) {
        if(!changeDate)    newTimeFlag = true;    // флаг что нужно поменять время, если не просматриваем дату
        secs++;
        if (secs > 59) {
            secs = 0;
            mins++;

        if ((hrs == 12 && mins == 1 && secs == 0)       // чистим чистим!
        || (hrs == 0 && mins == 1 && secs == 0)) {
            byte repeat = 0;                             // for burnIndi
            while (repeat < 5) {
                burnIndicators();
                repeat++;
            }
        }

        if ((mins == 1 && secs == 15) || mins == 30) {    // каждые полчаса
            DateTime now = rtc.now();       // синхронизация с RTC
            secs = now.second();
            mins = now.minute();
            hrs = now.hour();
        }

    }
        if (mins > 59) {
            mins = 0;
            hrs++;
            if (hrs > 23) hrs = 0;
            changeBright();
        }
        if (newTimeFlag) setNewTime();         // обновляем массив времени
    }
}

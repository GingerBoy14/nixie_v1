//обновление цвета светодиодов
void set_color(byte flag) {
  switch(flag){
    case 0:{
      rainbow_fade(220); 
      break;
    }
    case 1:{
    if (c <= 1) {
      analogWrite( mass_led[c], led_color[0]);
      analogWrite( mass_led[c + 1], led_color[1]);
    } else {
      analogWrite( mass_led[c], led_color[0]);
      analogWrite( mass_led[0], led_color[1]);
    }
          break;
    }
    case 2:{
          analogWrite(mass_led[0], 255);
          analogWrite(mass_led[1], 255);
          analogWrite(mass_led[2], 255);
          break;
    }
    default:{
          analogWrite(mass_led[0], LOW);
          analogWrite(mass_led[1], LOW);
          analogWrite(mass_led[2], LOW);
          break;
    }
  }
}

// плавная смена цветов всей ленты
void rainbow_fade(uint8_t pause) {
  if (millis() - last_step > pause) {
    ihue++;
    led_color[0] = short((255 - ihue)*bright_lvl);
    led_color[1] = short(ihue * bright_lvl);
    if (ihue > 255) ihue = 0;
    if (c > 2) c = 0;
    if (c <= 1) {
      analogWrite( mass_led[c], led_color[0]);
      analogWrite( mass_led[c + 1], led_color[1]);
    } else {
      analogWrite( mass_led[c], led_color[0]);
      analogWrite( mass_led[0], led_color[1]);
    }
    if (ihue == 255)c++;
    last_step = millis();
  }
}

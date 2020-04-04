//обновление цвета светодиодов
void set_color(bool flag) {
  if (flag) {
    rainbow_fade(200);
  }else {
   analogWrite(mass_led[0], LOW);
    analogWrite(mass_led[1], LOW);
    analogWrite(mass_led[2], LOW);
  }
}
// плавная смена цветов всей ленты
void rainbow_fade(uint8_t pause) {
  if (millis() - last_step > pause) {
    ihue++;
    if (ihue > 255)ihue = 0;
    if (c > 2) c = 0;
    if (c <= 1) {
      analogWrite( mass_led[c], short((255 - ihue)*bright_lvl));
      analogWrite( mass_led[c + 1],  short(ihue * bright_lvl));
    } else {
      analogWrite( mass_led[c], short((255 - ihue)*bright_lvl));
      analogWrite( mass_led[0], short(ihue * bright_lvl));
    }
    if (ihue == 255)c++;
    last_step = millis();
  }
}

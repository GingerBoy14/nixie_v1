// ***************************** fast digitalwrite *****************************
void setPin(uint8_t pin, uint8_t x) {
  if (pin < 8) bitWrite(PORTD, pin, x);
  else if (pin < 14) bitWrite(PORTB, (pin - 8), x);
  else if (pin < 20) bitWrite(PORTC, (pin - 14), x);
  if (pin > 19) return 0;
}
// ***************************** fast digitalread *****************************
boolean readPin(uint8_t pin) {  
  if (pin < 8) return bitRead(PIND, pin);
  else if (pin < 14) return bitRead(PINB, pin - 8);
  else if (pin < 20) return bitRead(PINC, pin - 14);  
  else return false;
}

void process_inputs() {
   //Watch for trigger

  #if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
    if (digitalRead(BTN_TRIGGER) == HIGH && gameData_status == 1 && playerData_alive == 1) {
      shoot();
    }
  #else
    if (analogRead(BTN_TRIGGER) > 500 && gameData_status == 1 && playerData_alive == 1) {
      shoot();
    }
  #endif
  
}

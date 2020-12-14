void process_inputs() {
   //Watch for trigger
  if (analogRead(BTN_TRIGGER) > 500 && gameData_status == 1 && playerData_alive == 1) {
    shoot();
  }
}

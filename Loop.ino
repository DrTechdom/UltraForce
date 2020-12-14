void loop() {
  //Check timers
  timers();

  //Check Radio for packets
  RF_RX();

  //LED Requests
  process_led();

  // Check for user input changes
  process_inputs();

  // Check IR for packets
  process_IR();  
}

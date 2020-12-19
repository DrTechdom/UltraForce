void process_IR() {
  if (irrecv.decode(&results)) {
    int id = 88;
    String s_id = "";
    s_id = char(results.value);
    
    #if defined(DEBBUGER)
      Serial.print("<IR:CLIENT <-  "); Serial.print(s_id); Serial.println(">");
    #endif
    
    if (playerData_alive == 1 && checkPlayer(s_id.toInt()) == true && gameData_status == 1) {
      // Set respawn time
      playerData_respawn = millis();
      playerData_alive = 0;
   
      gameData_roster[id][0] = gameData_roster[s_id.toInt()][0] + 1;
      
      #if defined(DEBUGGER)
        Serial.print("<IR:CLIENT <- "); Serial.print(s_id); Serial.print("> Shot by: "); Serial.print(gameData_roster[id][1]); Serial.print(" "); Serial.print(gameData_roster[id][0]); Serial.println(" times");
      #endif
      
      FastLED.setBrightness(  BRIGHTNESS_DEAD );
      FastLED.show();
   
      //Make a waa waa sound
      #if defined(AUTOTYPE_SOUNDFX)
        // SoundFX
      #else
        TimerFreeTone(SPEAKER, 262, 50);
        delay(300);
        TimerFreeTone(SPEAKER, 196, 50);
        delay(500);
      #endif

      //Make a waa waa sound
      #if defined(DISPLAYTYPE_TWO_CHAR)
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("     Shot By");
        lcd.setCursor(0, 1);
        lcd.print(gameData_roster[s_id.toInt()][1]);
      #else
        // 1603
      #endif
    //  screens(7);

      // Record the shot
      gameData_shots++;
    }
    irrecv.resume(); // Receive the next value    
  }
}

void shoot() {
  String id = "";
  id = gameData_playerID;
  
  // Delay time for next shot
  if ((millis() - lastShot) > 200) {

    //Make a pew pew sound
    #if defined(AUTOTYPE_SOUNDFX)
      // SoundFX
    #else
      TimerFreeTone(SPEAKER, 3729, 20);
      digitalWrite(LED_SHOOT,HIGH);
      delay(20);
      TimerFreeTone(SPEAKER, 2489, 20);
      delay(20);
      digitalWrite(LED_SHOOT,LOW);
    #endif
 
    #if DEBBUGER2
      Serial.print("<CLIENT -> IR> "); Serial.println(id);
    #endif
        
    //send the characters over the IR line
    for (int i = 0; i < id.length(); i++){  
      irsend.sendRC5(id.charAt(i), 12);
      delay(30);
   
    }
    //irrecv.resume(); // Receive the next value
    irrecv.enableIRIn(); // Start the receiver
 
    // Set time for next shot
    lastShot = millis();
 
 
  }
}

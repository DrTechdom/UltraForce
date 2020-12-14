void timers() {
 
  // Player respawn
  if ((millis() - playerData_respawn) > (gameData_respawn_time * 1000) && playerData_alive == 0) {
    playerData_alive = 1;
    setTeamColor();

    //Make a ooweep sound
    #if AUTOTYPE_SOUNDFX
      // SoundFX
    #else
      TimerFreeTone(SPEAKER, 200, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 250, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 300, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 350, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 400, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 450, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 500, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 600, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 700, 50);
      delay(50);
      TimerFreeTone(SPEAKER, 800, 50);
      delay(50);
    #endif
    
    FastLED.setBrightness(  BRIGHTNESS_ALIVE );
    FastLED.show();

    //Print Player name and stats
    #if defined(DISPLAYTYPE_TWO_CHAR)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(gameData_roster[gameData_playerID][1]);
      lcd.setCursor(0, 1);
      lcd.print("Shots left: 000");
    #else
      //1603
    #endif
  }
 
  // Game start time count down
  if (gameData_status == 2) {
    // Turn on beep every other second
    if (((millis() - gameData_wait_time_mills) / 1000) % 2) {

    #if defined(AUTOTYPE_SOUNDFX)
      // SoundFX
    #else
      TimerFreeTone(SPEAKER, 50, 100);
    #endif

    #if defined(DISPLAYTYPE_TWO_CHAR)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Starting!");
      lcd.setCursor(0, 1);
      lcd.print("Get to hidding!!");
    #else
      //1603
    #endif
    }
  }

 
  // Game start time
  if ((millis() - gameData_wait_time_mills) > (gameData_wait_time * 1000) && gameData_status == 2) {
    #if defined(AUTOTYPE_SOUNDFX)
      // SoundFX
    #else
      TimerFreeTone(SPEAKER, 200, 100);
      delay(300);
      TimerFreeTone(SPEAKER, 200, 100);
      delay(300);
      TimerFreeTone(SPEAKER, 200, 100);
      delay(300);
      TimerFreeTone(SPEAKER, 200, 100);
      delay(300);
      TimerFreeTone(SPEAKER, 1000, 20);
   #endif
   
    playerData_alive = 1;
    gameData_status = 1;
    gameData_wait_time_mills = millis();
    FastLED.setBrightness(  BRIGHTNESS_ALIVE );
    FastLED.show();

    //Print Player name and stats
    #if defined(DISPLAYTYPE_TWO_CHAR)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(gameData_roster[gameData_playerID][1]);
      lcd.setCursor(0, 1);
      lcd.print("Shots left: 000");
    #else
      //1603
    #endif
  }
 
  // In-Game end time
  if ((millis() - gameData_wait_time_mills) > (gameData_game_time * 1000L) && gameData_status == 1) {
    #if defined(DEBUGGER2)
      Serial.println("<CLIENT> Game has ended");
    #endif

    #if defined(DISPLAYTYPE_TWO_CHAR)
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Game Ended!");
      lcd.setCursor(0, 1);
      lcd.print("Get to base!");
    #else
      //1603
    #endif
    
    playerData_alive = 1;
    gameData_status = 0;
    gameData_game_time = 0;
    gameData_wait_time = 0;
    gameData_respawn_time = 0;
    
    FastLED.setBrightness(  BRIGHTNESS_DEAD );
    FastLED.show();

    #if AUTOTYPE_SOUNDFX
      // SoundFX
    #else
      TimerFreeTone(SPEAKER, 50, 200);
      delay(600);
      TimerFreeTone(SPEAKER, 50, 200);
      delay(600);
      TimerFreeTone(SPEAKER, 50, 200);
      delay(600);
      TimerFreeTone(SPEAKER, 50, 200);
   #endif
   
    FastLED.setBrightness(  BRIGHTNESS_ALIVE );
    FastLED.show();

    #if defined(DISPLAYTYPE_TWO_CHAR)
      lcd.clear();
      lcd.setCursor(0, 0);
      sprintf(Buffdata,"Player %u", gameData_playerID);
      lcd.print(Buffdata);
      lcd.setCursor(0, 1);
      lcd.print("Ready");
    #else
      //1603
    #endif
    
    radioLastPing = millis() + 30000;
    SendMSG("hits","1");
  }

#if defined(DISPLAYTYPE_TWO_CHAR)
if (millis() > timer_flipflop && playerData_alive == 1) {
    timer_flipflop = millis() + 1500; // Every 2 seconds
    lcd.clear();

    //Top Screen
    lcd.setCursor(0, 0);

    switch (flipflop) {
      case 0:
       if (gameData_status == 0) {
        sprintf(Buffdata,"Player %u", gameData_playerID);
        lcd.print(Buffdata);
       }
       break;
      case 1:
        if (gameData_status == 0) {
          lcd.print("Ultra Force");
        }
        break;
      case 2:
       if (gameData_status == 0) {
        sprintf(Buffdata,"Player %u", gameData_playerID);
        lcd.print(Buffdata);
       }
       break;
    }

    if (gameData_status == 1) { lcd.print(gameData_roster[gameData_playerID][1]); }
    if (gameData_status == -1) {   sprintf(Buffdata,"Player %u", gameData_playerID);
                                   lcd.print(Buffdata); }
                                

    //Bottom Screen
    lcd.setCursor(0, 1);
    
    switch (flipflop) {
      case 0:
        if (gameData_status == 1) { lcd.print("Shots left: 000"); }
        if (gameData_status == -1) { lcd.print("Connecting.."); }
        break;
      case 1:
       if (gameData_status == -1) { lcd.print("Connecting. ."); }
       if (gameData_status == 1) { 
        sprintf(Buffdata,"Hits: %u", gameData_shots);
        lcd.print(Buffdata);}
       break;
      case 2:
       if (gameData_status == -1) { lcd.print("Connecting .."); }
       if (gameData_status == 1) {
        int time, seconds, mins = 0;
        time = gameData_game_time - (millis() - gameData_wait_time_mills) / 1000;
        //mins = time / 60;
        sprintf(Buffdata,"Time: %u:%u", mins, time);
        lcd.print(Buffdata); }
       break;
    }

    if (gameData_status == 0) { lcd.print("Ready"); }

    //Perform flip flop
    if (flipflop == 2) {
      flipflop = 0;
    }else{
      flipflop++;
    }
}
#endif

  //Ping Pong Timer
/*
  if (millis() > radioLastPing && gameData_status != -1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Ultra Force");
    lcd.setCursor(0, 1);
    lcd.scrollDisplayLeft();
    lcd.print("Lost Connection!");
    leds[0] = CRGB::Blue;
    FastLED.show();
    gameData_status = -1;
   }
*/
}

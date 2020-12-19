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
    screens(4); /* In game and alive */
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

    //screens(5);
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
    screens(4);
  }
 
  // In-Game end time
  if ((millis() - gameData_wait_time_mills) > (gameData_game_time * 1000L) && gameData_status == 1) {
    #if defined(DEBUGGER2)
      Serial.println("<CLIENT> Game has ended");
    #endif

    screens(6); /* Game ending screen */
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

    screens(3); /* Idle screen */
    
    RF_endgame();
  }

#if defined(DISPLAYTYPE_TWO_CHAR)
  screens_flipflop();
#endif

  //Ping Pong Timer

  if (millis() > radioLastPing && gameData_status != -1) {
    screens(8);
    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(3000);
    gameData_status = -1;
    screens(1);
   }

}

#ifdef DISPLAYTYPE_TWO_CHAR
  void screens(byte s) {
    screen = s; /* Update the global variable for refreshing */
    lcd.clear();
    
    switch (s) {
      case 0: /* Startup screen */
        lcd.setCursor(0, 0);
        lcd.print("UltraForce");
        lcd.setCursor(0, 1);
        lcd.print("Ver "+sw_version);
        break;
     case 1:  /* Waiting for connection */
        lcd.setCursor(0, 0);
        sprintf(Buffdata,"Player %u", gameData_playerID);
        lcd.print(Buffdata);
        lcd.setCursor(0, 1);
        lcd.print("Connecting..");
        break;
     case 2: /* Found host */
        lcd.setCursor(0, 1);
        lcd.print("Host found!    ");
        delay(1500);
     case 3: /* Idle screen */
        lcd.setCursor(0, 1);
        lcd.print("Ready           ");
        break;
     case 4: /* In game - Alive */
        lcd.setCursor(0, 0);
        lcd.print(gameData_roster[gameData_playerID][1]);
        lcd.setCursor(0, 1);
        lcd.print("Shots left: 000");
        break;
      case 5: /* Going into game - get ready screen */
        lcd.setCursor(0, 0);
        lcd.print("Game Starting!");
        lcd.setCursor(0, 1);
        lcd.print("Get to hiding!!");
        break;
      case 6: /* In Game - Game ending */
        lcd.setCursor(0, 0);
        lcd.print("Game Ended!");
        lcd.setCursor(0, 1);
        lcd.print("Get to base!");
        break;
      case 7: /* Shot */
//        lcd.setCursor(0, 0);
//        lcd.print("     Shot By");
//        lcd.setCursor(0, 1);
//        lcd.print(gameData_roster[s_id.toInt()][1]);
        break;
      case 8:
        lcd.setCursor(0, 0);
        lcd.print("Ultra Force     ");
        lcd.setCursor(0, 1);
        lcd.scrollDisplayLeft();
        lcd.print("Lost Connection!");
        break;
        
    }
  }

  /* Flip Flop of changing screen displays to fit more on an event */
  void screens_flipflop() {
    if (millis() > timer_flipflop && playerData_alive == 1 && gameData_status != 2) {
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
  }
#endif

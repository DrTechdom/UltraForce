#ifdef DISPLAYTYPE_1603
  void screens(byte s) {
    screen = s; /* Update the global variable for refreshing */
    display.clearDisplay();
    
    switch (s) {
      case 0: /* Start-up screen */        
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println(F("UltraForce"));
        display.setCursor(3, 25);
        display.setTextSize(1);
        display.println("Version: "+sw_version);
        break;
      case 1: /* Connection screen */
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_playerID);
        display.setCursor(6, 25);
        display.setTextSize(1);
        display.println("Waiting for host..");
        break;
      case 2: /* Host found */
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_playerID);
        display.setCursor(6, 25);
        display.setTextSize(1);
        display.println("Host Found!");
        display.display();
        delay( 1500 );
      case 3: /* Idle */
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_playerID);
        display.setCursor(6, 25);
        display.setTextSize(3);
        display.println("Ready");
        break;
      case 4: /* In game - alive */
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_roster[gameData_playerID][1]);
        display.setCursor(6, 25);
        display.setTextSize(3);
        display.println("Shots left: 000");
        break;
      case 5: /* Going into game - gets ready */
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_roster[gameData_playerID][1]);
        display.setCursor(6, 25);
        display.setTextSize(3);
        display.println("Game starting! Get to hiding!");
        break;
      case 6: /* In Game - Game Ending */
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_roster[gameData_playerID][1]);
        display.setCursor(6, 25);
        display.setTextSize(3);
        display.println("Get to base!");
        break;
      case 7: /* Shot */
        break;
      case 8:
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(3, 0);
        display.print("Player ID: "); display.println(gameData_playerID);
        display.setCursor(6, 25);
        display.setTextSize(1);
        display.println("Connection Lost!");
        break;
    }
    display.display(); /* Refresh the display */
  }
#endif

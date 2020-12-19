void SendMSG(String command , String data){
   // Stop listening, so we can send!
  radio.stopListening();
  delay(80); // Wait for console to come back
  
  String msg = "00";
  msg += gameData_playerID;
  msg += "x";
  msg += command;

  if (data != "") {
    msg += "x";
    msg += data;
  } 
  char text[20] = "";
  msg.toCharArray(text,msg.length()+1);
  
  if (!radio.write(text, msg.length()+1)) {
    #ifdef DEBUGGER
      Serial.println("<RF:CLIENT> Radio transmission failed");
    #endif
  }

  #if defined(DEBUGGER)
    Serial.print("<RF:CLIENT -> HOST> "); Serial.println(msg);
  #endif
  
  delay(10);
  radio.startListening();
}

void RF_RX() {
  if (radio.available()) {
    delay(50);
    char text[32] = {0};
    String text_str = "";
    
    radio.read(&text, sizeof(text));
    text_str = text; // Convert char to string to deal with

    //Debugging
    #if defined(DEBUGGER2)
      Serial.print("<RF:HOST (RAW) ("); Serial.print(sizeof(text)); Serial.print(")> "); Serial.println(text_str);
    #endif
    
    #if defined(DEBUGGER)
      Serial.print("<RF:HOST -> "); Serial.print(text_str.substring(0,3)); Serial.print(" > "); Serial.println(text_str.substring(4));
    #endif

    #if defined(DEBUGGER2)
      Serial.print("<RF:HOST (4-8)>"); Serial.println(text_str.substring(4,8));
      Serial.print("<RF:HOST (8-9)>"); Serial.println(text_str.substring(8,9));
      Serial.print("<RF:HOST (9)>"); Serial.println(text_str.substring(9));
    #endif
    


    // Message to everyone
    if (text_str.substring(0,3) == "000") {
      //Registration
      if (text_str.substring(4,8) == "REG" and gameData_status == -1) {
        SendMSG("CREG","");
      }

      //PING - PONG
      else if (text_str.substring(4,8) == "PING" && gameData_status == 0) {
        SendMSG("PONG",text_str.substring(9));
        radioLastPing = millis() + 30000;

        //screens(3); /* Show ready screen */
      }

      //Game Start
      else if (text_str.substring(4,8) == "SART") { // && gameData_status == 0
        Serial.println("Game starting . . .");
        //Start game
        gameData_status = 2;
        screens(5);
        gameData_reset();
        setTeamColor();
        gameData_wait_time_mills = millis();
      }

      //Game Stop
      else if (text_str.substring(4,8) == "STOP" && gameData_status != 0) {
        //Stop!!
        gameData_status = 0;
      }
        
      //Changing settings
      if (text_str.substring(4,7) == "set") {
        //Player Name
        if (text_str.substring(8,9) == "N"){ // && isnan(text_str.substring(9,10).toInt()) == 0
          gameData_roster[text_str.substring(9,10).toInt()][1] = text_str.substring(10);
        }
        //Team ID
        if (text_str.substring(8,9) == "T"){ // && isnan(text_str.substring(9,10).toInt()) == 0
          gameData_roster[text_str.substring(9,10).toInt()][2] = text_str.substring(10,11);
        }
        //Game Time
        else if (text_str.substring(8,9) == "G"){
          gameData_game_time = text_str.substring(9).toInt();
        }
        //Game Wait Time
        else if (text_str.substring(8,9) == "W"){
          gameData_wait_time = text_str.substring(9).toInt();
        }
        //Game Friendly fire rule
        else if (text_str.substring(8,9) == "F"){
          gameData_friendly_fire = text_str.substring(9).toInt();
        }
        //Game respawn time
        else if (text_str.substring(8,9) == "R"){
          gameData_respawn_time = text_str.substring(9).toInt();
        }
      }
    }

    // Message to this client
    if (text_str.substring(0,3).toInt() == gameData_playerID) {

     // Client Software Version
     if (text_str.substring(4,8) == "VERS") {
      SendMSG("VERS",sw_version);
     }
     
     // Client Registation
     if (text_str.substring(4,8) == "REGG") {
        // Registation was successful
        if (text_str.substring(9) == "OK"){
          #if defined(DEBUGGER)
            Serial.println("<CLIENT> Registation Successful");
          #endif
          screens(2); /* Host Found */
          
          radioLastPing = millis() + 30000;
          gameData_status = 0;
        }
        //Registation Error - Server has no record of client
        else if (text_str.substring(9) == "NONE"){
          #if defined(DEBUGGER)
            Serial.println("<CLIENT> Clearing data due to an registation error..");
          #endif
          gameData_status = -1;

        #if defined(DEBUGGER)
          Serial.println("<RF:CLIENT -> CONSOLE> Re-registering..");
        #endif
        SendMSG("CREG","");
        }
     }

     /* Ping Pong Results */
     if (text_str.substring(4,8) == "PSTA") {
        #if defined(DEBUGGER)
          Serial.print("<RF:CLIENT -> CONSOLE> Ping-Pong Results: "); Serial.println(text_str.substring(9));
        #endif     
     }
    }
  }
}

void RF_endgame() {
  radioLastPing = millis() + 30000;
  SendMSG("hits","1");
}

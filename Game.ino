bool checkPlayer (int playerID) {
  int result = false; // Finding result
 
 if (playerID < 21 && playerID > 0) {
 
  //Check if player is enabled in roster by type
  if (gameData_roster[playerID][1].length() > 1) {
 
    // Check if its friendly fire and FF is disabled
    if (gameData_friendly_fire == 0 && gameData_roster[playerID][1] == gameData_roster[gameData_playerID][1]) {
      result = false;
    }else{
      result = true;
    }
  }
 }
 return result;
}

void gameData_reset() {
  gameData_shots = 0;
}

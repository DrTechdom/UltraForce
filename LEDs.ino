void setTeamColor() {
  switch(gameData_roster[gameData_playerID][2].toInt()) {
    case 1: // Red
      leds[0] = CRGB::Red;
      FastLED.show();
      break;
    case 2: // Green
      leds[0] = CRGB::Green;
      FastLED.show();
      break;
    case 3: // Blue
      leds[0] = CRGB::Blue;
      FastLED.show();
      break;
    case 4: // Pink
      leds[0] = CRGB::Pink;
      FastLED.show();
      break;
    default: // Black/Off
      leds[0] = CRGB::Black;
      FastLED.show();
      break;
  }
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
 
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, BRIGHTNESS_ALIVE, currentBlending);
        colorIndex += 1;
    }
}

void process_led() {
  //Idle motion - only shows when not in game and client is registered to server
 if (gameData_status == 0) {
  //Rainbow - maybe use for idle
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */
 
  FillLEDsFromPaletteColors( startIndex);
 
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
 }  
}

void setup() {
  pinMode(LED_SHOOT,OUTPUT);
  digitalWrite(LED_SHOOT,HIGH);
  delay( 1500 ); // power-up safety delay
  digitalWrite(LED_SHOOT,LOW);

  // Setup the display

  #if defined(DISPLAYTYPE_TWO_CHAR)
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("UltraForce");
    lcd.setCursor(0, 1);
    lcd.print("Ver "+sw_version);
  #else
   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
      Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
    }
    display.display(); // Splash screen
    display.clearDisplay();
    delay(2);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("UltraForce"));
    display.setCursor(3, 25);
    display.setTextSize(1);
    display.println("Version: "+sw_version);
    display.display();
  #endif
  
  delay(1500);

  #if defined(DEBUGGER) or defined(DEBUGGER2)
   // Start the serial
   Serial.begin(9600);
   while(!Serial);
   Serial.println("<CLIENT> Guncode Client Starting...");
  #endif

  /*
   * I2C Scanner for debugging
   */
   
  #if DEBUGGER3
    byte error, address;
    int nDevices;
  
    Serial.println("<I2C SCANNER> Scanning...");
  
    nDevices = 0;
    for(address = 1; address < 127; address++ ) 
    {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();
  
      if (error == 0) {
        Serial.print("<I2C SCANNER> Device found at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.print(address,HEX);
        Serial.println("  !");
  
        nDevices++;
      }
      else if (error==4) {
        Serial.print("<I2C SCANNER> Unknown error at address 0x");
        if (address<16) {
          Serial.print("0");
        }
        Serial.println(address,HEX);
      }    
    }
    if (nDevices == 0) {
      Serial.println("<I2C SCANNER> No I2C devices found");
    } else {
      Serial.println("<I2C SCANNER> Done");
    }
    #endif
  
  // Start the radio
  #if defined(DEBUGRF)
    printf_begin(); // Debugging
  #endif
  
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);   // RF24_PA_MIN ,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  if (!radio.setDataRate( RF24_2MBPS )) { Serial.println("<CONSOLE> Set data rate failed!"); } // RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  radio.setChannel(22);
  //radio.setRetries(15, 4);
  //radio.enableAckPayload();
  radio.setCRCLength(RF24_CRC_8);
  //radio.setPayloadSize(20);
  radio.setAutoAck(0);

  // Get into standby mode
  radio.startListening();
  radio.stopListening();

  #if defined(DEBUGRF)
    radio.printDetails();
  #endif  
    
  // Set the reading pipe and start listening
  radio.openReadingPipe(1, pipeNum[0]);
  radio.openWritingPipe(pipeNum[gameData_playerID]);
  radio.startListening();
  //radio.printDetails();

  irrecv.blink13(false); // Flash pin 13 when IR is recived
  irrecv.enableIRIn(); // Start the receiver
  FastLED.addLeds<WS2811, RGB_LED, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS_ALIVE );
 
  currentPalette = RainbowStripeColors_p;
  currentBlending = LINEARBLEND;
  
  gameData_wait_time_mills = millis();
  
  delay(1000);

  #if defined(DISPLAYTYPE_TWO_CHAR)
    lcd.clear();
    lcd.setCursor(0, 0);
    sprintf(Buffdata,"Player %u", gameData_playerID);
    lcd.print(Buffdata);
    lcd.setCursor(0, 1);
    lcd.print("Connecting..");
  #else
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(3, 0);
    display.print("Player ID: "); display.println(gameData_playerID);
    display.setCursor(6, 25);
    display.setTextSize(1);
    display.println("Waiting for host..");
    display.display();
  #endif
}

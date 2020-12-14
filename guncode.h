#ifndef _GUNCODE_H
#define _GUNCODE_H

// Load up the libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#if defined(DEBUGRF)
  #include <printf.h> // Debugging for radio
#endif

#include <Wire.h>
#include <FastLED.h>
#include <IRremote.h>

#if defined(DISPLAYTYPE_TWO_CHAR)
  // Two char display
  #include <LiquidCrystal_I2C.h>
#else
  //1603
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
#endif


#if AUTOTYPE_SOUNDFX
  // SoundFX
#else
  #include <TimerFreeTone.h>
#endif

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
  //Digital I/O
  #define LED_SHOOT      2  // LED on IR blaster
  #define IR_TX          9  // Front IR LED
  #define IR_BLAST_EN    11 // Enable blaster IR LEDs
  #define IR_RECV        10 // Reciver LED
  #define SPEAKER        6  // Speaker
  #define RGB_LED        5  // RGB LED
  #define RADIO_CS       49  // Radio hardware
  #define RADIO_CE       48  // Radio hardware
  #define LED_HEARTBEAT  0 // Heart beat LED
   
  // Analog inputs
  #define BTN_TRIGGER    0  // Trigger/enter button
  #define BTN_UP         0  // Up button
  #define BTN_DOWN       0  // Down button
#else
  //Digital I/O
  #define LED_SHOOT      2  // LED on IR blaster
  #define IR_TX          3  // Front IR LED
  #define IR_BLAST_EN    4  // Enable blaster IR LEDs
  #define IR_RECV        5  // Reciver LED
  #define SPEAKER        6  // Speaker
  #define RGB_LED        7  // RGB LED
  #define RADIO_CS       8  // Radio hardware
  #define RADIO_CE       9  // Radio hardware
  #define open_10        10 // Open Pin
  #define LED_HEARTBEAT  13 // Heart beat LED
   
  // Analog inputs
  #define BTN_TRIGGER    0  // Trigger/enter button
  #define BTN_UP         1  // Up button
  #define BTN_DOWN       2  // Down button
  // A3-7 open
#endif

// Create a Radio
RF24 radio(RADIO_CE, RADIO_CS); 

// The tx/rx address
const uint64_t pipeNum[6] = { 0xF0F0F0F066 , 0xF0F0F0F0AA , 0xF0F0F0F0AB ,0xF0F0F0F0AC , 0xF0F0F0F0AD , 0xF0F0F0F0AE };

//Variables
int gameData_status = -1; // -1 = unregistered, 0 = stop , 1 = started , 2 = waiting
int gameData_game_time, gameData_team, gameData_wait_time, gameData_friendly_fire, gameData_respawn_time, gameData_shots;
long gameData_wait_time_mills = 0;
String gameData_roster[8][3]; // 0- shots 1- name 2- team 3- Reserved 4- special
int playerData_alive = 1;
long playerData_respawn = 0;
String console_input = "";
String msg_combine = "";
long radioLastPing = 30000;
unsigned long lastShot = 0;
long int timer_registation = 2000;

char Buffdata[10];

#if defined(DISPLAYTYPE_TWO_CHAR)
  long int timer_flipflop = 1500; // 2 second flip flop
  int flipflop = 0;
#endif

// IR
IRrecv irrecv(IR_RECV);
IRsend irsend;
decode_results results;
long ir_building_time = 0;
String ir_buffer;
 
//RGB LED
#define BRIGHTNESS_ALIVE  200
#define BRIGHTNESS_DEAD 5
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;
#define UPDATES_PER_SECOND 70


#if defined(DISPLAYTYPE_TWO_CHAR)
  /* LCD
   * set the LCD address to 0x27 for a 16 chars and 2 line display
   *
   *                     Address
   *                     |   Charactors
   *                     |   |  Lines
   *                    vvv  vv v       */
  LiquidCrystal_I2C lcd(0x27,16,2);
#else
  //1603 display
  #define SCREEN_WIDTH 128 // OLED display width, in pixels
  #define SCREEN_HEIGHT 64 // OLED display height, in pixels

  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  #define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  
#endif

#endif

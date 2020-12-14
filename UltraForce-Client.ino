/**************************************************
 *                  Ultra Force                   *
 *        Created by. Ryan and Alex Vesely        *  
 *                                                *
 *             Update on  08/21/2019              */
String         sw_version = "1.3.286"; 
 /**************************************************/


/******* Setup per gun ************
 *                                *
 *  These are the only settings   *
 *        to set per gun          *
 **********************************/
int gameData_playerID = 1;


/********* RGB LEDs ***************
 *  How many LEDs are on a gun?   *
 **********************************/
#define NUM_LEDS    1


/******* Display type ************
 *  1 - 2 char LCD               *
 *  2 - 603 OLED                 *
 *********************************/
// #define DISPLAYTYPE_TWO_CHAR
#define DISPLAYTYPE_1603


/********* Audio ****************/
#define AUTOTYPE_PIZZO
 // #define AUTOTYPE_SOUNDFX


/****** SoundFX - Gun Theme *****/
#define GUNTHEME_OLDSKOOL
// #define GUNTHEME_FORTNITE
// #define GUNTHEME_CAT
// #define GUNTHEME_WOLF
// #define GUNTHEME_UNICORN


/************************************
 *       DEBUG CONFIGURATION        *
 ************************************/
 #define DEBUGGER     // Low level printout debugging
 //#define DEBUGGER2  // Verbose level printout debugging
 //#DEBUGRF           // Radio debugging






/******** END OF CONFIG ******************/


/**** DEPENDENCIES TO INSTALL *****  
 *  IREMOTE
 *   - NOTE: boarddef.h timer 
 *           must be set to timer 2
 *
 *  LiquidCrystal_I2C           - 2 Char LCD
 *  TimerFreeTone               - Arduino 128
 *  Adafruit SSD1306            - Char LCD
 *  
 *  FastLED                     - All
 *  RF24                        - All
 **********************************/
 

/********** TODO LIST **************
 *  
 *  Create IR blaster
 *  Display shots
 *  Display hits
 *  Bonus shots
 *  Still issues with ping timer when game is running
 *  Center player name when shot
 *  Game modes
 *  Convert time correctly on in game timer in flip flop
 *  
 ***********************************/








//Compatibity errors
#if !defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)
  #if defined(DISPLAYTYPE_1603)
    #error Only Arduino mega can not run this display
    /*******************************
     * The smaller Arduinos are not compatable with this display
     * as the size of the processor is too small
     */
  #endif

  #if defined(AUTOTYPE_SOUNDFX)
    #error Only Arduino mega can not run SoundFX
     /*******************************
     * The smaller Arduinos are is not compatable with running SoundFX
     * as the size of the processor is too small
     */
  #endif
#endif

#include "guncode.h"

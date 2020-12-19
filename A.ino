/******************************************************
 *                Configuration                       *
 ******************************************************/

/******* Setup per gun ************
 *                                *
 *  These are the only settings   *
 *        to set per gun          *
 **********************************/
int gameData_playerID = 2;


/********* RGB LEDs ***************
 *  How many LEDs are on a gun?   *
 **********************************/
#define NUM_LEDS    1


/******* Display type ************
 *  1 - 2 char LCD               *
 *  2 - 1603 OLED                *
 *********************************/
//#define DISPLAYTYPE_TWO_CHAR
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
//#define DEBUGGER     // Low level printout debugging
//#define DEBUGGER2  // Verbose level printout debugging
//#define DEBUGRF           // Radio debugging






/******** END OF CONFIG ******************/



//Compatibity errors
#if defined(DISPLAYTYPE_1603)
  #if !defined(__AVR_ATmega2560__) //|| !defined(__AVR_ATmega1280__)
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

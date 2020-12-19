/**************************************************
 *                  Ultra Force                   *
 *        Created by. Ryan and Alex Vesely        *  
 *                                                *
 *             Update on  12/19/2020              */
String         sw_version = "1.3.298"; 
 /**************************************************/



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
 *  timerfreetone               - ALL https://bitbucket.org/teckel12/arduino-timer-free-tone/downloads/
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


/******** Change Log *****************
 *  
 *  02/11/2018 - Ryan Vesely - Version 1.1.0
 *    Start of project - Moved from guncode 1.0
 *  
 *  02/13/2018 - Ryan Vesely - Version 1.1.4
 *    Start of IR RX and TX - Working
 *    
 *  02/14/2018 - Ryan Vesely - Version 1.1.8
 *    Added library to interact with RGB LED
 *    Kept sample code
 *    Added debounce for trigger
 *    
 *  02/17/2018 - Ryan Vesely - Version 1.1.14
 *    Added tones
 *      - Shooting
 *      - Dead
 *      - Respawn
 *
 *    Added basic team data
 *    Added shot verification
 *    Added function to RGB LED
 *      - Set team color
 *      - Dead
 *      
 *  02/18/2018 - Ryan Vesely - Version 1.1.19
 *    Added game start timer
 *    Added in game timer
 *
 *    Moved around RGB led code to make timers work
 *    and to dim/brighten LED for enabled disabled status
 *
 *  02/18/2018 - Ryan Vesely - Version 1.1.22
 *    Added idle mode to run a rainbow effect on the RGB LEDs when not in game
 *    
 *  02/25/2018 - Ryan Vesely - Version 1.1.44
 *    Added the ability for the base to program the gun
 *    with all nessecary game parameters and then start the game.
 *    
 *  --------- Missing Data ----------
 *  ?/?/2018 - Ryan Vesely - 1.2.0
 *    Moved from proto board to Arduino nano to add to final products using a two line serial LCD
 *    
 *  ?/?/2019 - Ryan Vesely - 1.3.0
 *    Migrated from Arduino nano to Arduiono Mega using the Adafruit 1306 SSD as the buffer overflows for the 1306
 *    using a nano. Going to keep the two line LCD as an optional gun.
 *    
 *  12/16/2020 - Ryan Vesely - 1.3.290
 *    Moved all screens to seperate screens() function depending on the type of screen
 *    
 *  12/17/2020 - Ryan Vesely - 1.3.294
 *    Fixed multi client RF issues and collisions
 *    Added connetion lost screen and function when ping timer succeeds
 *    
 *  12/18/2020 - Ryan Vesely - 1.3.298
 *    Repaired client ping timer
 *    Added ping statisics of client <-> server and caculations to add to clients signal strength meter
 *    
 *  12/18/2020 - Ryan Vesely - 1.3.298
 *    Migrated git changelog here. Moving from local git to github
 *    
 */

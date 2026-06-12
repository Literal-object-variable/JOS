#ifndef JOS_CONFIG
#define JOS_CONFIG
#include <Arduino.h>
// THE JOS REWRITTEN CONFIGURATION FILE //
/* Section A: Pin Mapping */
#define UP_BUTTON        2
#define DOWN_BUTTON      3
#define SELECT_BUTTON    4
#define BACK_BUTTON      5
#define BUZZER           6
#define DHTPIN           7
/* Section B: System settings */
#define SPLASHSCREEN     true   // Display the Splash screen.
#define LENGTH_OF_SPLASH 2      // Length of the Splash screen. Time in seconds
#define SCREEN_WIDTH     128    // Width of OLED display
#define SCREEN_HEIGHT    64     // Height of OLED display
#define SCREEN_ADDRESS   0x3C   // Address of OLED display
#define RTC_ADDRESS      0x68   // Address of RTC module
#define DHTTYPE          DHT11  // Type of DHT module
#define USE_RTC          true   // Use the RTC module (turn off if you don't have one)
// PRANKS WERE REMOVED.
/* Section C: Useful stuff */
#define GAME             true  // Show the game in the menu.
#define DEVICE_NAME      "Mainstream" // Name of the device, shows up at the top of the screen.
/* Section D: Application-defined */
const unsigned long      BALL_RATE =     16;
const uint8_t            PADDLE_HEIGHT = 12;
const uint8_t            SCORE_LIMIT =   9;
#endif

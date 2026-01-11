#include <SPI.h>
#include <Wire.h>
#include <DHT.h>
#include <EEPROM.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <uRTCLib.h>
#include "JOS_bitmaps.h"
#include "JOS_config.h"
const unsigned long PADDLE_RATE = 64;
const uint8_t PLAYER_X = 115;
const uint8_t MCU_X = 12;
uint32_t delayMS = 1000;
bool game_over, win;
bool isfs = false;
bool dhtl = false;
bool isCluck = false;
uint8_t player_score, mcu_score;
uint8_t ball_x = 53, ball_y = 26;
uint8_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;
unsigned long paddle_update;
uint8_t mcu_y = 16;
uint8_t player_y = 16;
int selected = 0;
int entered = -1;
int fsEnter = -1;
int fsSelect = 0;
int eeAddress = 0;
short hours    = 0;
short minutes  = 0;
short seconds  = 0;
char tempA[3];
char tempB[3];
char tempC[3];
short date     = 0;
short month    = 0;
int year       = 0;
struct EStructure {
  char fileA[128];
  char fileB[128];
  char fileC[128];
  char fileD[128];
  char fileE[128];
  char fileF[128];
  char nameA[16];
  char nameB[16];
  char nameC[16];
  char nameD[16];
  char nameE[16];
  char nameF[16];
};
const char *options[6] = {
    " Clock               ",
    " Temp / Humidity     ",
    " SuperMario Song     ",
    " The Pong Game       ",
    " EEPROM FS           ",
    " About Me            ",
};
unsigned long len = LENGTH_OF_SPLASH*1000;
void splash();
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
uRTCLib rtc(RTC_ADDRESS);
DHT_Unified dht(DHTPIN, DHTTYPE);
void setup() {
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {for (;;);}
  if (DISAGREE && !AGREE){for (;;);}
  if (SWITCHOFF){for (;;);}
  if (SHOWERROR){while(true){display.clearDisplay(); display.setCursor(10,10); display.print("Error 1: Cannot start JOS, system files missing."); display.display(); delay(2000);}}
  if (FAKEUPDATE){while(true){display.clearDisplay(); display.setCursor(10,10); display.print("Updating JOS... This will take forever."); display.display(); delay(2000);}}
  if (SPLASHSTUCK){len = 4294967295UL;}
  display.clearDisplay();
  if(SPLASHSCREEN){splash();}
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  
}
void loop() {displaymenu();}
void splash(){
  display.clearDisplay();
  display.drawBitmap(0, 0, TitlePage, 128, 64, 1);
  display.display();
  display.setFont(NULL);
  delay(len);
  display.clearDisplay();
  display.display();
}
void staticHeader(){
    display.clearDisplay();
    display.fillRect(0, 0, 128, 8, 1);
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(1, 0);
    display.print(DEVICE_NAME);
    display.setCursor(98, 0);
    updateRTC();
    sprintf(tempA, "%02d", hours);
    sprintf(tempB, "%02d", minutes);
    display.print(tempA);
    display.print(":");
    display.print(tempB);
    display.setTextColor(WHITE);
}
void displaymenu(void) {
  int down = digitalRead(DOWN_BUTTON);
  int up = digitalRead(UP_BUTTON);
  int enter = digitalRead(SELECT_BUTTON);
  int back = digitalRead(BACK_BUTTON);

  if (up == LOW && down == LOW) {};
  if (up == LOW && entered == -1) {
    selected = selected + 1;
    delay(200);
  };
  if (down == LOW && entered == -1) {
    selected = selected - 1;
    delay(200);
  };
  if (enter == LOW && entered == -1) {
    entered = selected;
  };
  if (back == LOW && entered != -1) {
    entered = -1;
    dhtl = false;
  };
  if (entered == -1) {
    staticHeader();
    display.setCursor(52, 9);
    display.println("Menu");
    if(!GAME){options[3] = " File not found.     ";}
    if(MATHPI){options[0] = " Math.Pi             ";}
    for (int i = 0; i < 6; i++) {
      if (i == selected) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.println(options[i]);
      } else if (i != selected) {
        display.setTextColor(SSD1306_WHITE);
        display.println(options[i]);
      }
    }
  } else if (entered == 0 && !MATHPI) {
    isCluck = true;
    while (isCluck){
      cluck(); // Chickens can tell the time, so the clock application is called cluck.
      if (digitalRead(BACK_BUTTON) == LOW) {
        isCluck = false;
        return;
      } 
    }
  } else if (entered == 0 && MATHPI) {
    display.clearDisplay();
    display.fillRect(0, 0, 128, 8, 1);
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(1, 0);
    display.println("COMPATIBLITY MODE.");
    display.setTextColor(WHITE);
    display.setCursor(20, 9);
    display.println("Legacy Math.Pi");
    display.setTextWrap(1);
    display.println("3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986");
    display.display();
  } else if (entered == 1) {
    staticHeader();
    dhtl = true;
    while (dhtl) {
      dl();
      if (digitalRead(BACK_BUTTON) == LOW) {
        dhtl = false;
        return;
      }
    }
  }
  else if (entered == 2) {
    display.clearDisplay();
    display.drawBitmap(0, 0, New_Project, 128, 64, 1);
    display.display();
    musicdisc();
  } else if (entered == 3 && GAME) {
    mcu_y = 16;
    player_y = 16;
    player_score = 0;
    mcu_score = 0;
    ball_x = 53;
    ball_y = 26;
    ball_dir_x = 1;
    ball_dir_y = 1;
    //The Setup:
    unsigned long start = millis();
    display.clearDisplay();
    drawCourt();
    display.display();
    ball_update = millis();
    paddle_update = ball_update;
    gameloop();
  } else if (entered == 4) {
    isfs = true;
    fsEnter = -1;
    fsSelect = 0;
    delay(200);
    fs();
  } else if (entered == 5) {
    staticHeader();
    display.setCursor(25, 9);
    display.println("About Me");
    display.println("John Antony Alapatt");
    display.print("JOS REWRITTEN ");
    display.println(JOS_VERSION);
    display.print("NAME:");
    display.println(DEVICE_NAME);
    display.print("CEPROM ");
    display.println(EEPROM_FS_VERSION);
  }
  if (selected > 5) {
    selected = 5;
  } if (selected < 0) {
    selected = 0;
  }
  display.display();
}

void Chaplication(){
  while(isChap){
  EStructure mainDirectory;
  EEPROM.get(eeAddress, mainDirectory);
  int down = digitalRead(DOWN_BUTTON);
  int up = digitalRead(UP_BUTTON);
  int enter = digitalRead(SELECT_BUTTON);
  int back = digitalRead(BACK_BUTTON);          
  if (up == LOW && down == LOW) {}
  if (up == LOW && cEnter == -1) {
    cSelect = cSelect - 1;
    delay(200);
  };
  if (down == LOW && cEnter == -1) {
    cSelect = cSelect + 1;
    delay(200);
  };
  if (enter == LOW && cEnter == -1) {
    cEnter = cSelect;
  };
  if (back == LOW && cEnter == -1){
    entered = -1;
    isChap = false;                
    return;
  };
  if (back == LOW && cEnter != -1) {
    cEnter = -1;
    delay(200);
  };
  char *cOption[6];
  if (cEnter == -1) {
    int down = digitalRead(DOWN_BUTTON);
  int up = digitalRead(UP_BUTTON);
  int enter = digitalRead(SELECT_BUTTON);
  int back = digitalRead(BACK_BUTTON);
    showCHeader();
    display.setCursor(28, 9);
    display.println("Chaplication");
    display.fillRect(0,16,128,1,0);
    cOption[0] = mainDirectory.chatNameA;
    cOption[1] = mainDirectory.chatNameB;
    cOption[2] = mainDirectory.chatNameC;
    cOption[3] = mainDirectory.chatNameD;
    cOption[4] = mainDirectory.chatNameE;
    cOption[5] = mainDirectory.chatNameF;
    for (int i = 0; i < 6; i++) {
      if (i == cSelect) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.print(" ");
        display.print(cOption[i]);
        if(strlen(cOption[i]) < 20){for (int ni = strlen(cOption[i]); ni < 20; ni++){display.print(" ");}}display.println();
      } else if (i != cSelect) {
        display.setTextColor(SSD1306_WHITE);
        display.print(" ");
        display.print(cOption[i]);
        if(strlen(cOption[i]) < 20){for (int ni = strlen(cOption[i]); ni < 20; ni++){display.print(" ");}}display.println();
      }
    }
  } else if (cEnter == 0) {showChat(mainDirectory.chatMsgA1,mainDirectory.chatMsgA2 ,mainDirectory.chatNameA);
  } else if (cEnter == 1) {showChat(mainDirectory.chatMsgB1,mainDirectory.chatMsgB2 ,mainDirectory.chatNameB);
  } else if (cEnter == 2) {showChat(mainDirectory.chatMsgC1,mainDirectory.chatMsgC2 ,mainDirectory.chatNameC);
  } else if (cEnter == 3) {showChat(mainDirectory.chatMsgD1,mainDirectory.chatMsgD2 ,mainDirectory.chatNameD);
  } else if (cEnter == 4) {showChat(mainDirectory.chatMsgE1,mainDirectory.chatMsgE2 ,mainDirectory.chatNameE);
  } else if (cEnter == 5) {showChat(mainDirectory.chatMsgF1,mainDirectory.chatMsgF2 ,mainDirectory.chatNameF);
  } if (cSelect > 5) {cSelect = 5;
  } if (cSelect < 0) {cSelect = 0;
  } display.display();
  }
}void showCHeader(){
  display.clearDisplay();
  display.fillRect(0, 0, 128, 8, 1);
  display.setTextColor(WHITE);
}
void showChat(char cMsgA[32],char cMsgB[32], char name[16]){
  showCHeader();
  display.setTextWrap(1);
  display.setCursor(0, 9);
  display.print(" ");
  display.println(name);
  display.println(cMsgA);
  display.println(cMsgB);
  display.setCursor(1, 48);
  display.fillRect(0, 47, 128, 17, 1);
  display.setTextColor(BLACK, WHITE);
  display.println("> Type your message here");
}

void Chaplication(){
  while(isChap){
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
  } else if (cEnter == 0) {display.clearDisplay(); showChat(mainDirectory.chatMsgA1,mainDirectory.chatMsgA2 ,mainDirectory.chatNameA);
  } else if (cEnter == 1) {display.clearDisplay(); showChat(mainDirectory.chatMsgB1,mainDirectory.chatMsgB2 ,mainDirectory.chatNameB);
  } else if (cEnter == 2) {display.clearDisplay(); showChat(mainDirectory.chatMsgC1,mainDirectory.chatMsgC2 ,mainDirectory.chatNameC);
  } else if (cEnter == 3) {display.clearDisplay(); showChat(mainDirectory.chatMsgD1,mainDirectory.chatMsgD2 ,mainDirectory.chatNameD);
  } else if (cEnter == 4) {display.clearDisplay(); showChat(mainDirectory.chatMsgE1,mainDirectory.chatMsgE2 ,mainDirectory.chatNameE);
  } else if (cEnter == 5) {display.clearDisplay(); showChat(mainDirectory.chatMsgF1,mainDirectory.chatMsgF2 ,mainDirectory.chatNameF);
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
  display.fillRect(0, 0, 128, 8, 1);
  display.setTextColor(WHITE);
  display.setTextWrap(1);
  display.setCursor(0, 9);
  display.print(" ");
  display.println(name);
  display.println(cMsgA);
  display.println(cMsgB);
  display.setCursor(1, 48);
  chapUpdateText();
  _keypad();
  chapUpdateText();
  if(areUDoneYet == true){
         if (cEnter == 0) {strcpy(mainDirectory.chatMsgA1, mainDirectory.chatMsgA2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgA2, ctempA); 
  } else if (cEnter == 1) {strcpy(mainDirectory.chatMsgB1, mainDirectory.chatMsgB2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgB2, ctempA);
  } else if (cEnter == 2) {strcpy(mainDirectory.chatMsgC1, mainDirectory.chatMsgC2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgC2, ctempA);
  } else if (cEnter == 3) {strcpy(mainDirectory.chatMsgD1, mainDirectory.chatMsgD2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgD2, ctempA);
  } else if (cEnter == 4) {strcpy(mainDirectory.chatMsgE1, mainDirectory.chatMsgE2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgE2, ctempA);
  } else if (cEnter == 5) {strcpy(mainDirectory.chatMsgF1, mainDirectory.chatMsgF2); finalmsg.toCharArray(ctempA, 32); strcpy(mainDirectory.chatMsgF2, ctempA);
  }
  eeprom.eeprom_write(0, (byte*)&mainDirectory, sizeof(EStructure));
  eeprom.eeprom_read(eeAddress, (byte*)&mainDirectory, sizeof(EStructure));
  areUDoneYet = false;
  }
}
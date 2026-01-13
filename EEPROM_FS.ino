/* EEPROM FS / FILE MANAGER // DO NOT EDIT ANY LINE APART FROM LINE 44 */
void fs(){
  while(isfs){
  EStructure mainDirectory;
  EEPROM.get(eeAddress, mainDirectory);
  int down = digitalRead(DOWN_BUTTON);
  int up = digitalRead(UP_BUTTON);
  int enter = digitalRead(SELECT_BUTTON);
  int back = digitalRead(BACK_BUTTON);

  if (up == LOW && down == LOW) {}
  if (up == LOW && fsEnter == -1) {
    fsSelect = fsSelect - 1;
    delay(200);
  };
  if (down == LOW && fsEnter == -1) {
    fsSelect = fsSelect + 1;
    delay(200);
  };
  if (enter == LOW && fsEnter == -1) {
    fsEnter = fsSelect;
  };
  if (back == LOW && fsEnter == -1){
    entered = -1;
    isfs = false;
    return;
  };
  if (back == LOW && fsEnter != -1) {
    fsEnter = -1;
    delay(200);
  };
  char *fsOption[6];
  if (fsEnter == -1) {
    int down = digitalRead(DOWN_BUTTON);
  int up = digitalRead(UP_BUTTON);
  int enter = digitalRead(SELECT_BUTTON);
  int back = digitalRead(BACK_BUTTON);
    showHeader();
    display.setCursor(28, 9);
    display.println("File Manager");
    display.fillRect(0,16,128,1,0); // Hide bottom part of g in File Manager. Remove this line if using white only or blue only display.
    fsOption[0] = mainDirectory.nameA;
    fsOption[1] = mainDirectory.nameB;
    fsOption[2] = mainDirectory.nameC;
    fsOption[3] = mainDirectory.nameD;
    fsOption[4] = mainDirectory.nameE;
    fsOption[5] = mainDirectory.nameF;
    for (int i = 0; i < 6; i++) {
      if (i == fsSelect) {
        display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
        display.print(" ");
        display.print(fsOption[i]);
        display.print(".txt");
        if(strlen(fsOption[i]) < 16){for (int ni = strlen(fsOption[i]); ni < 16; ni++){display.print(" ");}}display.println();
      } else if (i != fsSelect) {
        display.setTextColor(SSD1306_WHITE);
        display.print(" ");
        display.print(fsOption[i]);
        display.print(".txt");
        if(strlen(fsOption[i]) < 16){for (int ni = strlen(fsOption[i]); ni < 16; ni++){display.print(" ");}}display.println();
      }
    }
  } else if (fsEnter == 0) {showFile(mainDirectory.fileA, mainDirectory.nameA);
  } else if (fsEnter == 1) {showFile(mainDirectory.fileB, mainDirectory.nameB);
  } else if (fsEnter == 2) {showFile(mainDirectory.fileC, mainDirectory.nameC);
  } else if (fsEnter == 3) {showFile(mainDirectory.fileD, mainDirectory.nameD);
  } else if (fsEnter == 4) {showFile(mainDirectory.fileE, mainDirectory.nameE);
  } else if (fsEnter == 5) {showFile(mainDirectory.fileF, mainDirectory.nameF);
  } if (fsSelect > 5) {fsSelect = 5;
  } if (fsSelect < 0) {fsSelect = 0;
  } display.display();
  }
}void showFile(char file[128], char nameA[16]){
  showHeader();
  display.setCursor(0, 9);
  display.print(" ");
  display.print(nameA);
  display.println(".txt");
  display.println(file);
}void showHeader(){
  display.clearDisplay();
  display.fillRect(0, 0, 128, 8, 1);
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(1);
  display.setFont(NULL);
  display.setCursor(1, 0);
  display.print("JOS CEPROM ");
  display.print(EEPROM_FS_VERSION);
  display.setTextColor(WHITE);
}


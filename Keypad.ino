void _keypad() {
    char key = keypad.getKey();
  if (key && (millis() - lastKeyTime > DEBOUNCE)) {
    if (key == '#') {
      finalmsg = message;
      message = "";
      charIndex = 0;
      lastKey = -1;
      areUDoneYet = true;
      } else if (key == '*') {
      if (message.length() > 0) {
        message.remove(message.length() - 1);
        charIndex = 0;
        lastKey = -1;
        chapUpdateText();
      }
    } else if (key >= '0' && key <= '9') {
      if (message.length() >= 32) {
        chapUpdateText();
      } else {
        int num = key - '0';
        if (num == lastKey) {
          charIndex = (charIndex + 1) % strlen(letters[num]);
          message.setCharAt(message.length() - 1, letters[num][charIndex]);
        } else {
          message += letters[num][0];
          charIndex = 0;
        }
        lastKey = num;
        chapUpdateText();
      }
    }
    lastKeyTime = millis();
  }

  if (lastKey != -1 && millis() - lastKeyTime > TIMEOUT) {
    lastKey = -1;
    charIndex = 0;
  }
}
void chapUpdateText(){
  display.setCursor(1, 48);
  display.fillRect(0, 47, 128, 17, 1);
  display.setTextColor(BLACK, WHITE);
  display.println("Light> " + message);
  
}
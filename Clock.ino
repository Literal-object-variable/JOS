void cluck(){
    updateRTC();
    display.clearDisplay();
    display.fillRect(0, 0, 128, 8, 1);
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    display.setFont(NULL);
    display.setCursor(1, 0);
    display.print("JOS ");
    display.print(JOS_VERSION);
    display.setTextColor(WHITE);
    sprintf(tempA, "%02d", hours);
    sprintf(tempB, "%02d", minutes);
    sprintf(tempC, "%02d", seconds);
    display.setTextSize(2);
    display.setCursor(16, 20);
    display.print(tempA);
    display.print(":");
    display.print(tempB);
    display.print(":");
    display.print(tempC);
    display.setCursor(34, 40);
    display.setTextSize(1);
    display.print(date);
    display.print("/");
    display.print(month);
    display.print("/20");
    display.print(year);
    display.display();
}
void updateRTC(){
  if(USE_RTC){
    rtc.refresh();
    delay(20);
    date = rtc.day();
    month = rtc.month();
    year = rtc.year();
    hours = rtc.hour();
    minutes = rtc.minute();
    seconds   = rtc.second();
  }
}

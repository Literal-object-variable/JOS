/* DHT ELEVEN TEMPERATURE AND HUMIDITY // DO NOT EDIT ANY LINE APART FROM LINE 7 */
void dl(){
  display.fillRect(0, 9, 128, 55, 0);
  display.setTextColor(WHITE);
  display.setCursor(25, 9);
  display.println("Temp/Humiditu"); // change to Temp/Humidity if using full white or full blue display.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    display.println(F("Error"));
  }
  else {
    display.print(F("Temperature: "));
    display.print(event.temperature);
    display.println(F(" C"));
  }
  dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
    display.println(F("Error"));
  }
  else {
    display.print(F("Humidity:    "));
    display.print(event.relative_humidity);
    display.println(F("%"));
  }
  display.display();
  delay(500);
}

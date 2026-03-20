/* DHT ELEVEN TEMPERATURE AND HUMIDITY // DO NOT EDIT ANY LINE APART FROM LINE 7 */
void dl(){
  display.fillRect(0, 9, 128, 55, 0);
  display.setTextColor(WHITE);
  display.setCursor(25, 9);
  display.println("Temp/Humiditu"); // change to Temp/Humidity if using full white or full blue display.
  display.print(F("Temperature: "));
  display.print(dht.readTemperature());
  display.println(F(" C"));
  display.print(F("Humidity:    "));
  display.print(dht.readHumidity());
  display.println(F("%"));
  display.display();
  delay(500);
}

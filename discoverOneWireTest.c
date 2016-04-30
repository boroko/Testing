//*** Discover OneWire Device *****************************************
// trying to find a way to capture one address at a time and assign it to a parameter
void discoverOneWireDevices(void) {
  byte i;   // for selecting the address
  byte para;   // for selecting the parameter
  byte present = 0;
  byte data[12];
  byte addr[8];
  Serial.println("Looking for 1-Wire devices...");
  while (oneWire.search(addr)) {
    for ( i = 0; i < 8; i++) {
      if (addr[i] < 16) {
        Serial.println('0');
      }
      Serial.println(addr[i], HEX);
      if (i < 7) {
        Serial.println(", ");
      }
    }
    Serial.println("");
    Serial.print("ROM =");
    for ( i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }
    if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.print("CRC is not valid!");
      return;
    }
   do{
      TS_Point p = ts.getPoint();  //X & Y points range from 0-4095, Z = 0-255
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.height());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.width());
      delay(100);  
    // UP button
    if (p.y > 0 && p.y < 60 && p.x > 55 && p.x < 100) {
      para = (para + 1);
      if (para > 6) para = 0;
		Serial.println(ParaName[para]);
    }
    // Down button
    if (p.y > 0 && p.y < 60 && p.x > 0 && p.x < 45) { //Decrement ParaName
      para = (para + 1);
      if (para > 6) para = 0;
      Serial.println(ParaName[para]);
    }
    // ADD button     // assign captured number to selected parameter
   if ((p.y > 145 && p.y < 205 && p.x > 0 && p.x < 50)) { //wait for operator 
      //  xxx();    // call "Assign" Hex address of OneWire to ParaName
	Serial.println("ADD Button"); 
      delay(200);
	  return
    }
  }
  }
  oneWire.reset_search();
  return;

}
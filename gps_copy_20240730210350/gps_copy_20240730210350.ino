void setup() {
  Serial.begin(9600); // Initialize serial communication
  randomSeed(analogRead(0)); // Seed the random number generator with a value from an unconnected analog pin
  Serial.println("GPS Simulator Initialized");
}

void loop() {
  // Generate random latitude and longitude values
  float latitude = random(-90, 90) + random(0, 1000000) / 1000000.0;
  float longitude = random(-180, 180) + random(0, 1000000) / 1000000.0;
  
  // NMEA sentence format: $GPGGA,hhmmss.ss,latitude,lat_dir,longitude,lon_dir,fix_quality,num_satellites,hdop,altitude,units,geoidal_separation,units,dgps_age,dgps_station_id*checksum
  String gpsData = "$GPGGA,123519,";

  // Format latitude
  if (latitude < 0) {
    gpsData += String(-latitude, 6) + ",S,";
  } else {
    gpsData += String(latitude, 6) + ",N,";
  }

  // Format longitude
  if (longitude < 0) {
    gpsData += String(-longitude, 6) + ",W,";
  } else {
    gpsData += String(longitude, 6) + ",E,";
  }

  // Append fixed values for other fields in the NMEA sentence

  
  Serial.println(gpsData); // Send GPS data
  delay(1000); // Send data every second
}

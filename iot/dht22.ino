void dht22(){
  delay(1000);
  h = dht.readHumidity();
  t = dht.readTemperature();
  if (isnan(h) || isnan(t) ) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C \t");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");
}

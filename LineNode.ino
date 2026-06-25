void setup() {
  Serial.begin(9600);
}

void loop() {
  int c = analogRead(A0);
  int v = analogRead(A1);

  float I = (c - 512) * (5.0 / 1023.0) / 0.066;
  float V = v * (230.0 / 1023.0);
  float P = V * I;

  Serial.println(P);

  delay(1000);
}
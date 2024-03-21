#include <WiFiNINA.h>

char ssid[] = "Coldspotttt";
char pass[] = "password1234";
char val;
WiFiServer server(80); // Port 80

void setup() {
  pinMode(13, OUTPUT);

  // Serial.begin(9600);
  // while (!Serial);
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  
  // Serial.println("Connected to WiFi");
  // Serial.print("IP Address: ");
  // Serial.println(WiFi.localIP()); // ARDUINO IP 192.168.204.78
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    // Serial.println("New client connected");
    client.println("Hello from Arduino!");

    if (client.available()) {
      val = client.read();
      // Serial.println(val);
      if (val == 'F') {
        // Serial.println("Setting to high");
        digitalWrite(13, HIGH);
      } else {
        // Serial.println("Setting to low");
        digitalWrite(13, LOW);
      }
    }

    client.stop();
    // Serial.println("Client disconnected");
  }

  
}
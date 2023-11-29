#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 51, 182);

const int ledPin = 2;

EthernetServer server(80);

void setup() {
  pinMode(ledPin, OUTPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
}

void loop() {
  EthernetClient client = server.available();
  
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        
        if (request.indexOf("GET /?LED=ON") != -1) {
          digitalWrite(ledPin, HIGH);
          Serial.println("Led on");
        } else if (request.indexOf("GET /?LED=OFF") != -1) {
          digitalWrite(ledPin, LOW);
          Serial.println("Led off");
        }

        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("");
        client.println("<html><body>");
        client.println("<h1>Controle do LED</h1>");
        client.println("<p><a href=\"/?LED=ON\">Ligar LED</a></p>");
        client.println("<p><a href=\"/?LED=OFF\">Desligar LED</a></p>");
        client.println("</body></html>");
        break;
      }
    }

    delay(1); // Aguarda que o cliente envie os dados
    client.stop();
  }
}

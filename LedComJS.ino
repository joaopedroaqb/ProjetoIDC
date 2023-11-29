#include <SPI.h>
#include <Ethernet.h>
// Defina o endereço MAC e IP conforme necessário para a sua rede
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 51, 182);

// Pino do LED
const int ledPin = 2;

// Inicializa o servidor na porta 80
EthernetServer server(80);

void setup() {
  // Inicializa o pino do LED como saída
  pinMode(ledPin, OUTPUT);

  // Inicializa a comunicação Ethernet
  Ethernet.begin(mac, ip);

  // Inicia o servidor
  server.begin();

  Serial.begin(9600);
}

void loop() {
  // Aguarda a conexão de um cliente
  EthernetClient client = server.available();
  
  if (client) {
    // Aguarda até que o cliente envie dados
    while (client.connected()) {
      if (client.available()) {
        
        // Lê a primeira linha da solicitação HTTP
        String request = client.readStringUntil('\r');
        
        // Verifica se a solicitação contém "GET /?LED=ON"
        if (request.indexOf("GET /?LED=sentilante") != -1) {
          digitalWrite(ledPin, HIGH); // Liga o LED
          Serial.println("Led on");
        } else if (request.indexOf("GET /?LED=OFF") != -1) {
          digitalWrite(ledPin, LOW); // Desliga o LED
          Serial.println("Led off");
        }

        // Retorna a resposta HTTP com a página de controle
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

    // Fecha a conexão
    client.stop();
  }
}

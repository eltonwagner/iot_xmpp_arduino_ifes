//Codigo Incial : Projeto original que faz a comunicação entre o arduíno e o servidor Python
//Elton Machado, Filipe Vaz

#include <SPI.h>
#include <UDP.h>
#include <Ethernet.h>
#include <Stream.h>
#include <Print.h>
#include <EthernetUdp.h>


// Exemplo 3 - Entradas e saídas digitais - push-button + led
// Apostila Eletrogate - KIT START
#define PinButton 8 // define pino digital D8
#define ledPin 7 // define pino digital D7
#define AGUARDE 5

byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
// Meu IP do Ethernet Shield
IPAddress ip(192, 168, 25, 12);
//unsigned int localPort = 8880;
unsigned int localPort = 5222;

unsigned int UDPport = 5222;
IPAddress UDPServer(192,168,25,3); 

const int UDP_PACKET_SIZE = 48;

char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;


void setup()
{
// Meu MAC Address do Ethernet Shield
Ethernet.begin(mac, ip);
Serial.begin(9600);
while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start UDP
Serial.println(Ethernet.localIP());  
Udp.begin(localPort);

pinMode(PinButton, INPUT); // configura D8 como entrada digital
pinMode(ledPin, OUTPUT); // configura D7 como saída digital
//Serial.begin(9600); // monitor serial - velocidade 9600 Bps
//delay(10); // atraso de 100 milisegundos
}

void loop()
{
if ( digitalRead(PinButton) == HIGH) // se chave = nivel alto
{
digitalWrite(ledPin, HIGH); // liga LED com 5V
Serial.print("Acendendo Led"); // imprime no monitor serial

digitalWrite(ledPin, LOW); // desliga LED com 0V 
Serial.print("Desligando led"); // imprime no monitor serial 

int success;
/// enviar informação para o server
//Inicia a montagem do pacote para enviar ao host especificado
// No caso 192.168.0.90 é o IP do meu servidor(destino) e 5005 é a porta UDP

success = Udp.beginPacket(UDPServer, UDPport);
Serial.print("Init Packet: ");
Serial.println(success);

success = Udp.print("Led Vermelho Ativado"); //success recebe o numero de bytes enviados
Serial.print("bytes enviado: ");
Serial.println(success);
 
// Finaliza o pacote enviado, retorna 1 para sucesso e 0 para erro
success = Udp.endPacket();
Serial.print("End Packet: ");
Serial.println(success);
 
// Informa o IP Remoto
Serial.print("IP Remoto: ");
Serial.println(UDPServer);
 
// Informa a Porta Remota
Serial.print("Porta Remota: ");
Serial.println(UDPport);

 
// Encerra este socket
//Udp.stop();
 
delay(2000); //Aguarda 5s, altere AGUARDE pelo tempo em segundos
  
}

else // senão chave = nivel baixo 

{ 
digitalWrite(ledPin, LOW); // desliga LED com 0V 
//Serial.print("Desligando led"); // imprime no monitor serial 
} 
 


}
}

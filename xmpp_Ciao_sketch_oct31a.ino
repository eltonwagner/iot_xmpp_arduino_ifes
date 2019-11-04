/*
  Arduino Ciao example

  This sketch uses ciao xmpp connector. It sends back “hello world” message to the xmpp client when receives “ciao” from it.

  Be sure to set the xmpp client in the "USER" field used to receive the response by MCU.

  Possible commands to send from the xmpp client:
   "ciao" -> random answers in 5 different languages
*/

#include <Ciao.h>

#define LED 7
String USER = "user@domain";;

void setup() {
  pinMode(LED, OUTPUT);
  Ciao.begin();
}

void loop() {

  CiaoData data = Ciao.read("xmpp");

  if (!data.isEmpty() && !data.isError()) {

    String id = data.get(0);
    String sender = data.get(1);
    String message = data.get(2);

    message.toLowerCase();

    if (message == "ciao" )
      Ciao.write("xmpp", USER, "Hello, i'm Arduino :-) ");
    else if ( message == "led on") {
      digitalWrite(LED, HIGH);
      Ciao.writeResponse("xmpp", id, "LED ON");
    }
    else if ( message == "led off") {
      digitalWrite(LED, LOW);
      Ciao.writeResponse("xmpp", id, "LED OFF");
    }
    else
      Ciao.write("xmpp", USER, "Sorry i don't understand :-( ");
  }
}

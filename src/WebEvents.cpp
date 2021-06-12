#include <ESPAsyncWebServer.h>
#include <WebEvents.h>
#include <Motors.h>
#include <Switch.h>

AsyncEventSource events("/events");

void initEvents(AsyncWebServer *server) {
  events.onConnect([](AsyncEventSourceClient *client) {
    if (client->lastId()) {
      Serial.printf("Last msg id: %u\n", client->lastId());
    }
    client->send("hello", NULL, millis(), 1000);
  });
  server->addHandler(&events);
}

void notifyClient() {
  Serial.println("Notifying client...");
  String json = "{";
  json += "\"running\":";
  json += isMotorRunning();
  json += ", \"speed\":";
  json += getMotorSpeed();
  json += ", \"direction\":";
  json += getMotorDirection() == MOTOR_FORWARD ? "\"forward\"" : "\"backward\"";
  json += ", \"clicks\":";
  json += getClicks();
  json += ", \"rpm\":";
  json += getRpm();
  json += "}";
  events.send(json.c_str(), "change", millis());
}

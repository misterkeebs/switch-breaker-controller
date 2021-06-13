#include <ESPAsyncWebServer.h>
#include <WebEvents.h>
#include <Motors.h>
#include <Switch.h>
#include <Program.h>

AsyncEventSource events("/api/events");

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
  json += isMotorRunning() ? "true" : "false";
  json += ", \"speed\":";
  json += getMotorSpeed();
  json += ", \"direction\":";
  json += getMotorDirection() == MOTOR_FORWARD ? "\"forward\"" : "\"backward\"";
  json += ", \"clicks\":";
  json += getClicks();
  json += ", \"rpm\":";
  json += getRpm();
  json += ", \"program\":";
  json += isProgrammed() ? "true" : "false";
  json += ", \"programLength\":";
  json += getCyclePresses();
  json += ", \"programDuration\":";
  json += getCycleDuration();
  json += ", \"programDurationFormatted\":";
  json += "\"" + getFormattedCycleDuration() + "\"";
  json += "}";
  events.send(json.c_str(), "change", millis());
}

#include <ESPAsyncWebServer.h>
#include <WebEvents.h>

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
  events.send("refresh", "change", millis());
}

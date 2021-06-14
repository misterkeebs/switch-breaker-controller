#include <Arduino.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Input.h>
#include <Motors.h>
#include <Program.h>

#include "AsyncJson.h"
#include "ArduinoJson.h"

AsyncWebServer server(80);
AsyncEventSource events("/api/events");

JsonObject& getStatusAsJson() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject &obj = jsonBuffer.createObject();
  obj["running"] = isMotorRunning() ? true : false;
  obj["speed"] = getMotorSpeed();
  obj["direction"] = getMotorDirection() == MOTOR_FORWARD ? "forward" : "backward";
  obj["clicks"] = getClicks();
  obj["rpm"] = getRpm();
  obj["program"] = isProgrammed() ? true : false;
  obj["programLength"] = getCyclePresses();
  obj["programDuration"] = getCycleDuration();
  obj["programDurationFormatted"] = getFormattedCycleDuration();
  obj["programMessage"] = getMessage();
  return obj;
}

void sendStatus(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  getStatusAsJson().printTo(*response);
  // setMessage("");

  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void notifyClient() {
  Serial.println("Notifying client...");
  char output[1024];
  getStatusAsJson().printTo(output);
  setMessage("");
  events.send(output, "change", millis());
}

void sendError(AsyncWebServerRequest *request, int httpCode, String error) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject &obj = jsonBuffer.createObject();
  obj["error"] = error;
  response->setCode(httpCode);
  request->send(response);
}

void initEvents(AsyncWebServer *server) {
  events.onConnect([](AsyncEventSourceClient *client) {
    if (client->lastId()) {
      Serial.printf("Last msg id: %u\n", client->lastId());
    }
    client->send("hello", NULL, millis(), 1000);
  });
  server->addHandler(&events);
}

void initWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Sending index.html...");
    request->send(SPIFFS, "/index.html");
  });

  server.on("/api/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendStatus(request);
  });

  server.on("/api/reset", HTTP_POST, [](AsyncWebServerRequest *request) {
    stopProgram();
    sendStatus(request);
  });

  AsyncCallbackJsonWebHandler* progHandler = new AsyncCallbackJsonWebHandler("/api/program", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject& obj = json.as<JsonObject>();

    if (!obj.containsKey("length")) {
      sendError(request, 422, "missing length attribute");
      return;
    }

    int length = obj.get<int>("length");
    startProgram(length);

    sendStatus(request);
  });

  AsyncCallbackJsonWebHandler* setHandler = new AsyncCallbackJsonWebHandler("/api/set", [](AsyncWebServerRequest *request, JsonVariant &json) {
    JsonObject& obj = json.as<JsonObject>();

    if (obj.containsKey("motor")) {
      bool run = obj.get<bool>("motor");
      Serial.print("SET motor ");
      Serial.println(run);
      if (run) {
        startMotor();
      } else {
        stopMotor();
      }
    }

    if (obj.containsKey("speed")) {
      int speed = obj.get<int>("speed");
      Serial.print("SET speed ");
      Serial.println(speed);
      setMotorSpeed(speed);
    }

    if (obj.containsKey("direction")) {
      bool forward = obj.get<bool>("direction");
      Serial.print("SET direction ");
      Serial.println(forward);
      setMotorDirection(forward);
    }

    sendStatus(request);
  });

  server.addHandler(setHandler);
  server.addHandler(progHandler);
  initEvents(&server);

  server.begin();
}

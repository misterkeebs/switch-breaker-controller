#include <Arduino.h>
// #include <ESP8266WebServer.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Input.h>
#include <Motors.h>
#include <WebEvents.h>

#include "AsyncJson.h"
#include "ArduinoJson.h"

// ESP8266WebServer server(80);
AsyncWebServer server(80);

void handleServer() {
  // server.handleClient();
}

// void sendError(String msg) {
//   server.send(422, "text/plain", msg);
// }

void sendStatus(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject &obj = jsonBuffer.createObject();
  obj["running"] = isMotorRunning() ? true : false;
  obj["speed"] = getMotorSpeed();
  obj["direction"] = getMotorDirection() == MOTOR_FORWARD ? "forward" : "backward";
  obj["clicks"] = getClicks();
  obj["rpm"] = getRpm();
  obj.printTo(*response);
  response->addHeader("Access-Control-Allow-Origin", "*");
  request->send(response);
}

void initWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    Serial.println("Sending index.html...");
    request->send(SPIFFS, "/index.html");
  });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request) {
    sendStatus(request);
  });

  AsyncCallbackJsonWebHandler* setHandler = new AsyncCallbackJsonWebHandler("/set", [](AsyncWebServerRequest *request, JsonVariant &json) {
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
  initEvents(&server);

  server.begin();
}

// void handleStatus() {
//   if (server.method() == HTTP_POST) {
//     for (uint8_t i = 0; i < server.args(); i++) {
//       String name = server.argName(i);
//       String value = server.arg(i);

//       if (name == "speed") {
//         int speed = value.toInt();
//         if (speed < 0 || speed > 10) {
//           return sendError("Invalid speed");
//         }
//         setMotorSpeed(speed);
//       }

//       if (name == "motor") {
//         Serial.print("Set motor to ");
//         Serial.print(value);
//         Serial.print(value == "on");
//         Serial.print(value == "off");
//         Serial.println("");
//         if (value == "on") {
//           startMotor();
//         } else if (value == "off") {
//           stopMotor();
//         } else {
//           return sendError("Invalid motor status. Use on or off.");
//         }
//       }

//       if (name == "direction" || name == "dir") {
//         toggleMotorDirection();
//       }
//     }
//   }

//   String message = "{";
//   message += "\"running\":";
//   message += isMotorRunning() ? "true" : "false";
//   message += ",";
//   message += "\"speed\":";
//   message += getMotorSpeed();
//   message += ",";
//   message += "\"direction\":\"";
//   message += getMotorDirection() == MOTOR_FORWARD ? "forward" : "backwards";
//   message += "\"";
//   message += ",";
//   message += "\"clicks\":";
//   message += getClicks();
//   message += ",";
//   message += "\"rpm\":";
//   message += getRpm();
//   message += "}";
//   server.send(200, "application/json", message);
// }

// void handleIndex() {
//   String s = MAIN_page;
//   server.send(200, "text/html", s);
// }

// void handleOldIndex() {
//   if (server.args() > 0) {
//     String cmd = server.arg("cmd");
//     Serial.print("Command: ");
//     Serial.println(cmd);
//     if (cmd == "start") {
//       startMotor();
//     }
//     if (cmd == "stop") {
//       stopMotor();
//     }
//     if (cmd == "faster") {
//       setMotorSpeed(getMotorSpeed() + 1);
//     }
//     if (cmd == "slower") {
//       setMotorSpeed(getMotorSpeed() - 1);
//     }
//     if (cmd == "direction") {
//       toggleMotorDirection();
//     }
//     if (cmd == "reset") {
//       stopMotor();
//       resetClicks();
//     }
//     server.sendHeader("Location", String("/"), true);
//     server.send(302, "text/plain", "");
//     return;
//   }

//   String message = "";
//   if (isMotorRunning()) {
//     message += "<a href=\"/?cmd=stop\">Stop</a> | ";
//   } else {
//     message += "<a href=\"/?cmd=start\">Start</a> | ";
//   }
//   message += "<a href=\"/?cmd=reset\">Reset</a> | ";
//   message += "<a href=\"/?cmd=direction\">Direction</a> | ";
//   message += "<a href=\"/?cmd=faster\">Faster</a> | ";
//   message += "<a href=\"/?cmd=slower\">Slower</a> | ";
//   message += "<a href=\"/status\">Status</a>";
//   message += "<p>Motor running: ";
//   message += isMotorRunning() ? "Yes" : "No";
//   message += "<br/>Motor speed: ";
//   message += getMotorSpeed();
//   message += "<br/>Direction: ";
//   message += getMotorDirection() == MOTOR_BACKWARD ? "backward" : "forward";
//   message += "<br/>Presses: ";
//   message += getClicks();
//   message += "<br/>RPM: ";
//   message += getRpm();
//   message += "</p>";
//   server.send(200, "text/html", message);
// }

// void handleNotFound()
// {
//   String message = "File Not Found\n\n";
//   message += "URI: ";
//   message += server.uri();
//   message += "\nMethod: ";
//   message += (server.method() == HTTP_GET) ? "GET" : "POST";
//   message += "\nArguments: ";
//   message += server.args();
//   message += "\n";
//   for (uint8_t i = 0; i < server.args(); i++)
//   {
//     message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
//   }
//   server.send(404, "text/plain", message);
// }

// void initWebServer() {
//   server.on("/", handleIndex);
//   server.on("/status", handleStatus);
//   server.onNotFound(handleNotFound);
//   server.begin();
// }

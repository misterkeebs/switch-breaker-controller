#include <ESPAsyncWebServer.h>

void initWebServer();
void initEvents(AsyncWebServer *server);
void handleIndex();
void handleNotFound();
void notifyClient();

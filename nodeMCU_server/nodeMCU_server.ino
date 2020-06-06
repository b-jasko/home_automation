#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "Most DWR-921E_CBC043";  // Enter SSID here
const char* password = "12345678";  //Enter Password here


ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.swap();
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  server.on("/body", handleBody); //Associate the handler function to the path
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", "Connected to /"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

void handleBody() { //Handler for the body path
      server.send(200, "text/plain", server.arg("plain"));
      Serial.println(server.arg("plain"));
}

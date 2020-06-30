#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

/* Put your SSID & Password */
const char* ssid = "Most DWR-921E_CBC043";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.swap();
  inputString.reserve(200);
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

  HTTPClient http;

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  
  if (stringComplete)
  {
    http.begin("http://192.168.43.228:5000/writedata");      //Specify request destination
    http.addHeader("Content-Type", "text/plain");  //Specify content-type header
 
    int httpCode = http.POST(inputString);   //Send the request
  
    http.end();  //Close connection
   
    inputString = "";  // clear the string:
    stringComplete = false;
  }
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

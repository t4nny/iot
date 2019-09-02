#include <ESP8266WiFi.h>
 
const char* ssid = "Realme 2";
const char* password = "0000000000";
 

int finger = 14;

WiFiServer server(80);
 
void setup() {
  
  Serial.begin(115200);
  delay(10);
 
  pinMode(finger, OUTPUT);
  digitalWrite(finger, LOW);
 
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  
   int fingervalue=LOW;
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
 
  if (request.indexOf("/Finger=TRUE") != -1)  {
    digitalWrite(finger, HIGH);
    fingervalue = HIGH;
  }

   if (request.indexOf("/Finger=FALSE") != -1)  {
    digitalWrite(finger, LOW);
    fingervalue = LOW;
  }

 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
 
  if(fingervalue == LOW) {
      client.print("<script type='text/javascript'> alert('Access Denied'); </script>");
  } else {
   client.print("<script type='text/javascript'> alert('Access Granted'); </script>");
  
  }

    client.println("<br><br>");
    client.println("<br><br>");



  client.println("<a href=\"/Finger=TRUE\"\"><button>Granted</button></a>&nbsp; &nbsp; &nbsp; ");
 
 client.println("<a href=\"/Finger=FALSE\"\"><button>Denied</button></a>&nbsp; &nbsp; &nbsp; ");  
  client.println("</html>");
 
  delay(1);
  
  Serial.println("Client disonnected");
  Serial.println("");
 
}

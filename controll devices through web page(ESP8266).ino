#include <ESP8266WiFi.h>
 
const char* ssid = "automation";
const char* password = "roboticworld";
 
int fan = 13; //D7 PIN
int light = 12; //D6 PIN

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(light, OUTPUT);
  digitalWrite(light, LOW);
  pinMode(fan, OUTPUT);
  digitalWrite(fan, LOW);
 
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
   int fanvalue = LOW;
   int lightvalue= LOW;
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
 
 
  if (request.indexOf("/Light=ON") != -1)  {
    digitalWrite(light, HIGH);
    lightvalue = HIGH;
  }

   if (request.indexOf("/Light=OFF") != -1)  {
    digitalWrite(light, LOW);
    lightvalue = LOW;
  }

 if (request.indexOf("/Fan=ON") != -1)  {
    digitalWrite(fan, HIGH);
    fanvalue = HIGH;
  }
  
 if (request.indexOf("/Fan=OFF") != -1)  {
    digitalWrite(fan, LOW);
    fanvalue = LOW;
  }
 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Led pin is now: ");
 
  if(fanvalue == HIGH) {
    client.print("Fan On  ");
  } else {
    client.print("Fan Off  ");
  }

  if(lightvalue == HIGH) {
    client.print("Light On  ");
  } else {
    client.print("Light Off  ");
  }
    client.println("<br><br>");
    client.println("<br><br>");
 
  client.println("FAN");
  client.println("<a href=\"/Fan=ON\"\"><button>Turn On Fan </button></a>&nbsp; &nbsp; &nbsp; ");
  client.println("<a href=\"/Fan=OFF\"\"><button>Turn Off Fan </button></a>&nbsp; &nbsp; &nbsp; ");  
  delay(1);
    client.println("<br><br>");
    client.println("<br><br>");


  client.println("Light");
  client.println("<a href=\"/Light=ON\"\"><button>Turn On Light </button></a>&nbsp; &nbsp; &nbsp; ");
 
  client.println("<a href=\"/Light=OFF\"\"><button>Turn Off Light </button></a>&nbsp; &nbsp; &nbsp; ");  
  client.println("</html>");
 
  delay(1);
  
  Serial.println("Client disonnected");
  Serial.println("");
 
}

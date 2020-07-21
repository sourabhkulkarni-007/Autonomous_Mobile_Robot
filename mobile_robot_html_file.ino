  #include <ESP8266WiFi.h>
const char ssid[20] = "HomeSer";
const char password[20] = "mynameisthere";
int xvalue=0;

WiFiServer server(80);
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void setup() {

    Serial.begin(115200);
    delay(10);
    
     pinMode(D5, OUTPUT);
    pinMode(D1, OUTPUT);
    Serial.println("");
    Serial.println("Server-------------------------------");
    Serial.print("Configuring access point");
    WiFi.mode(WIFI_AP);           
    WiFi.softAP(ssid, password);
    //WiFi.begin(ssid, password);

    Serial.println("");
    Serial.print("Hotspot Created : ");
    Serial.println(WiFi.softAPIP());

  // Start the server
    server.begin();
    Serial.println("Server started");
    Serial.println("-------------------------------------");
    Serial.println("");
}
void loop() {
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
   
    Serial.print("Request: ");
    Serial.println(request);

//This function can be used to seperate a string into pieces based on what the separating character is.
String xval1 = getValue(request, '_', 1);
String xval2 = getValue(request, '_', 2);

if(xval1== "L" || xval1== "Z"){
xvalue = xval2.toInt();
}
    client.flush();
// Match the request
    int value = LOW;

    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); // do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<br><br>");
    client.println("<a href=\"/_L_130_\"\"><button>RED </button></a><br />");
    client.println("<a href=\"/_Z_120_\"\"><button>GREEN </button></a><br />");
    client.println("<a href=\"/B\"\"><button>BLUE</button></a><br />");
    client.println("<a href=\"/W\"\"><button>WHITE </button></a><br />");
    client.println("<a href=\"/O\"\"><button>Off </button></a><br />");
    client.println("</html>");
    Serial.println("Client disonnected");
    Serial.println("");


    Serial.println(request.indexOf("/_L"));
    Serial.println(request.indexOf("/_Z"));
    if(request.indexOf("/_L")!=-1) {
    analogWrite(D5,1023-xvalue);
    }
    if(request.indexOf("/_Z")!=-1){
    analogWrite(D1,xvalue);
    }
    

    
}

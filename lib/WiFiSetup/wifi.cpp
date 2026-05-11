#include "wifi.hpp"

Preferences preferences;

const char* AP_SSID = "ESP32-AP";
const char* AP_PASSWORD = "12345678";

const uint8_t DNS_PORT = 53;
DNSServer dnsServer;


void connectWiFi(){
  Serial.println();
  Serial.println("Starting WiFi setup");

  preferences.begin("wifi-config", false);

  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");

  if (ssid != "" && password != ""){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());

    Serial.print("Connecting");
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
      delay(500);
      Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nConnected!");
      preferences.end();
      return;
    } else {
      Serial.println("\nFailed to connect. Starting AP...");
    }
  }
  preferences.end();
  startAP();
}

void startAP() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(192,168,4,1), IPAddress(192,168,4,1), IPAddress(255,255,255,0));
  WiFi.softAP(AP_SSID, AP_PASSWORD);

  dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
  dnsServer.start(53, "*", IPAddress(192,168,4,1));

  webServer.on("/", HTTP_GET, handleRoot);
  webServer.on("/save", HTTP_POST, handleSave);

  webServer.on("/generate_204", handleRoot);
  webServer.on("/favicon.ico", []() { webServer.send(204); });

  webServer.onNotFound([]() {
    webServer.sendHeader("Location", "http://192.168.4.1/", true);
    webServer.send(302, "text/plain", "");
  });

  Serial.println("Captive Portal is up and redirection set!");
}

void handleRoot() {
  String page = R"=====( 
    <!DOCTYPE html>
    <html lang="uk">
    <head>
      <meta charset="UTF-8" />
      <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
      <title>Wi-Fi Setup</title>
      <style>
        body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }
        input { padding: 8px; margin: 8px 0; width: 80%; max-width: 300px; }
        button { padding: 10px 20px; font-size: 16px; }
      </style>
    </head>
    <body>
      <h2>Wi-Fi Setup</h2>
      <form action="/save" method="POST">
        <input type="text" name="ssid" placeholder="SSID" required /><br>
        <input type="password" name="password" placeholder="Password" required /><br>
        <button type="submit">Save & restart</button>
      </form>
    </body>
    </html>
  )=====";

  webServer.send(200, "text/html; charset=utf-8", page);
}

void handleSave() {
  if (webServer.hasArg("ssid") && webServer.hasArg("password")) {
    String ssid = webServer.arg("ssid");
    String pass = webServer.arg("password");

    Serial.printf("Отримані дані: SSID=%s, PASS=%s", ssid.c_str(), pass.c_str());

    preferences.begin("wifi-config", false);
    preferences.putString("ssid", ssid);
    preferences.putString("password", pass);
    preferences.end();

    String resp = R"=====( 
      <!DOCTYPE html>
      <html lang="uk">
      <head><meta charset="UTF-8"/><meta name="viewport" content="width=device-width, initial-scale=1.0"/><title>Success</title></head>
      <body style="text-align:center; font-family:Arial,sans-serif; padding:20px;">
        <h2>Succesfully saved!</h2>
        <p>The board will restarts soon...</p>
      </body>
      </html>
    )=====";

    webServer.send(200, "text/html; charset=utf-8", resp);
    delay(3000);
    ESP.restart();
  } else {
    webServer.send(400, "text/plain", "Error: Missing SSID or Password");
  }
}
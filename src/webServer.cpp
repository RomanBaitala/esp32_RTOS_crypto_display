#include "webServer.hpp"

WebServer webServer(80);

void initWebRoutes() {
    webServer.on("/settings", HTTP_GET, handleSettingsPage);
    webServer.on("/update_crypto", HTTP_POST, handleUpdateCrypto);
    webServer.onNotFound(handleNotFound);
    webServer.begin();
}

void handleSettingsPage() {
    String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
    html += "<title>Налаштування</title>";
    html += "<style>";
    html += "body { font-family: sans-serif; background: #121212; color: white; text-align: center; }";
    html += ".card { background: #1e1e1e; padding: 20px; border-radius: 12px; display: inline-block; margin-top: 50px; border: 1px solid #333; }";
    html += "select, button { width: 100%; padding: 12px; margin: 10px 0; border-radius: 8px; border: none; font-size: 16px; }";
    html += "button { background: #f3ba2f; color: black; font-weight: bold; cursor: pointer; }";
    html += "</style></head><body>";
    
    html += "<div class='card'>";
    html += "<h2>Crypto Display Settings</h2>";
    html += "<form action='/update_crypto' method='POST'>";
    html += "<select name='pair_idx'>";
    
    for (int i = 0; i < totalPairs; i++) {
        String selected = (i == currnetPairIndex) ? "selected" : "";
        html += "<option value='" + String(i) + "' " + selected + ">" + String(cryptoPairs[i]) + "</option>";
    }
    
    html += "</select><br>";
    html += "<button type='submit'>ЗБЕРЕГТИ</button>";
    html += "</form></div></body></html>";

    webServer.send(200, "text/html", html);
}

void handleUpdateCrypto() {
    if (webServer.hasArg("pair_idx")) {
        int newIdx = webServer.arg("pair_idx").toInt();
        saveSettings(newIdx);
        
        webServer.send(200, "text/plain", "OK. Settings Saved!");
    } else {
        webServer.send(400, "text/plain", "Bad Request");
    }
}

void handleNotFound() {
    webServer.send(404, "text/plain", "404: Not Found");
}

Preferences prefs;
bool forceUpdate = false;

void loadSettings() {
    prefs.begin("crypto-app", true);
    currnetPairIndex = prefs.getUChar("pair_idx", 0); 
    prefs.end();
}

void saveSettings(uint8_t index) {
    prefs.begin("crypto-app", false);
    prefs.putUChar("pair_idx", index);
    prefs.end();
    currnetPairIndex = index;
    forceUpdate = true; 
}
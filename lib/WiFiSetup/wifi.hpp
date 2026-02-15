#ifndef WFIF_OPERATIONS_H
#define WFIF_OPERATIONS_H

#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <Preferences.h>

extern DNSServer dnsServer;
extern WebServer webServer;

void connectWiFi();
void handleSave();
void handleRoot();
void startAP();
#endif 
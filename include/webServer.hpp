#ifndef WEB_SERVER_LOGIC_HPP
#define WEB_SERVER_LOGIC_HPP

#include <WebServer.h>
#include <Preferences.h>
#include "config.hpp"
#include "controller.hpp"

extern WebServer webServer;
extern bool forceUpdate;

void initWebRoutes();

void handleSettingsPage();
void handleUpdateCrypto();
void handleNotFound();

void loadSettings();
void saveSettings(uint8_t index);

#endif
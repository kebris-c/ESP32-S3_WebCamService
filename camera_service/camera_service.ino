/**********************************************************************
  Filename    : Camera Service
  Description : Web-based camera service for ESP32-S3. Connects
                to WiFi, initializes camera, and serves video stream.
  Auther      : kebris-c
  Modification: 2025/12/18
**********************************************************************/

#include "include/App.hpp"
#include "include/Log.hpp"
#include <Arduino.h>

static App	app;

void	setup(void)
{
	app.init();
}

void	loop(void)
{
	app.update();
}
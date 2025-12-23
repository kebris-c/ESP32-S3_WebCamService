#include "include/App.hpp"

/*
 *	Constructor
 */
App::App(void)
	: _wifi("ghostintheshell", "gh0st1nth3sh3ll"), \
	_cam(), \
	_sd(), \
	_web(_cam, _sd)
{
}

/*
 *	Init board, prepare the field. Called by setup() on .ino file.
 *	Spawn some messages. Try to connect to WiFi.
 */
void	App::init(void)
{
	Log::init(115200);
	Log::info("App initialized");
	_wifi.init();
	_sd.init();
	_cam.init();
	_web.init();
}

/*
 *	Main loop. Called by loop() on .ino file.
 */
void	App::update(void)
{
	_wifi.update();
	delay(1);
}
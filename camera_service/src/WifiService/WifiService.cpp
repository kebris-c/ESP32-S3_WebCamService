#include "include/WifiService.hpp"

/*
 *	Constructor
 */
WifiService::WifiService(const char *ssid, const char *password)
	: _ssid(ssid), _password(password)
{
}

/*
 *	Init WiFi connect. Try once for 10 seconds, then, if it is not connected,
 *	send a message of error.
 */
void	WifiService::init(void)
{
	unsigned long	start;

	Log::info("Connecting to WiFi...");
	WiFi.begin(_ssid, _password);

	start = millis();
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
		if (millis() - start > 10000)
		{
			Serial.println("");
			Log::error("Failed to connect to WiFi");
			return ;
		}
	}
	Serial.println("");
	Log::info("WiFi connected!");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
}


/*
 *	If the connection is fallen, try to connect it again and send
 *	a warning message to the user.
 */
void	WifiService::update(void)
{
	if (WiFi.status() != WL_CONNECTED)
	{
		delay(10000);
		Log::warn("WiFi disconnected, trying to reconnect...");
		WiFi.begin(_ssid, _password);
	}
}
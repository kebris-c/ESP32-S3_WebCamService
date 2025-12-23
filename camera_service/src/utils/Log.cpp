#include "include/Log.hpp"

/*
 *	Init board, by order of the main class App, called by setup on .ino file.
 *  Send the baudrate to Serial internally, needed to init it.
 */
void Log::init(unsigned long baudrate)
{
    Serial.begin(baudrate);
    while (!Serial)
    {
        ;
    }
}

/*
 *	Spawn some messages to the user.
 */
void Log::info(const char *msg)
{
    Serial.print("[INFO] ");
    Serial.println(msg);
}

void Log::warn(const char *msg)
{
    Serial.print("[WARN] ");
    Serial.println(msg);
}

void Log::error(const char *msg)
{
    Serial.print("[ERROR] ");
    Serial.println(msg);
}
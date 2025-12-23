#ifndef LOG_HPP
# define LOG_HPP

# include <Arduino.h>

/*
 *	Class with some features as init, info, warn or error.
 *	Contains functions to print something on the terminal.
 */
class	Log
{
public:
	static void init(unsigned long baudrate);

	static void info(const char *msg);
	static void warn(const char *msg);
	static void error(const char *msg);
};

#endif
#ifndef APP_HPP
# define APP_HPP

# include "include/Log.hpp"
# include "include/WifiService.hpp"
# include "include/CameraService.hpp"
# include "include/WebServerService.hpp"

/*
 *	Main class. Flow control, initializer.
 *	Use other classes as WifiService or Log.
 */
class App
{
private:
	WifiService			_wifi;
	CameraService		_cam;
	SDService			_sd;
	WebServerService	_web;
public:
	App(void);

	void	init(void);
	void	update(void);
};

#endif
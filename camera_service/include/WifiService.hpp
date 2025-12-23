#ifndef WIFISERVICE_HPP
# define WIFISERVICE_HPP

# include <WiFi.h>
# include "include/Log.hpp"

class WifiService
{
private:
	const char	*_ssid;
	const char	*_password;
public:
	WifiService(const char *ssid, const char *password);

	void	init(void);
	void	update(void);
};

#endif
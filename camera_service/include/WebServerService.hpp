#ifndef WEBSERVERSERVICE_HPP
# define WEBSERVERSERVICE_HPP

# include <esp_http_server.h>
# include "include/CameraService.hpp"
# include "include/Log.hpp"
# include "include/SDService.hpp"
# include "include/WifiService.hpp"

/*
 *	Simple HTTP server for ESP32 to stream camera.
 */
class	WebServerService
{
private:
	CameraService		&_cam;
	SDService			&_sd;

	httpd_handle_t		_server;

	static const char	*_STREAM_BOUNDARY;
	static const char	*_STREAM_PART;
	static const char	*_STREAM_CONTENT_TYPE;

	static esp_err_t	_index_handler(httpd_req_t *req);
	static esp_err_t	_capture_handler(httpd_req_t *req);
	static esp_err_t	_stream_handler(httpd_req_t *req);
public:
	WebServerService(CameraService &cam, SDService &sd);

	void	init(void);
};

#endif
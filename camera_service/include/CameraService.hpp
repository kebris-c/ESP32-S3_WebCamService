#ifndef CAMERASERVICE_HPP
# define CAMERASERVICE_HPP

# include "include/Log.hpp"
# include "include/CameraPins.hpp"
# include "include/SDService.hpp"
# include <esp_camera.h>
# include <Arduino.h>

class CameraService
{
private:
	camera_config_t	_config;
public:
	CameraService(void);

	bool 		captureToSD(const char *path, SDService &sd);
	void		init(void);
	void		returnFrame(camera_fb_t *fb);
	camera_fb_t	*captureFrame(void);
};

#endif
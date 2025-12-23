#include "include/CameraService.hpp"

CameraService::CameraService(void)
{
}

/*
 *	Camera config.
 *	If PSRAM IC present, init with UXGA resolution and
 *	higher JPEG quality for larger pre-allocated frame buffer.
 */
void	CameraService::init(void)
{
	esp_err_t	err;
	sensor_t	*s;

	Log::info("Initializing camera...");

	_config.ledc_channel	= LEDC_CHANNEL_0;
	_config.ledc_timer		= LEDC_TIMER_0;
	_config.pin_d0			= Y2_GPIO_NUM;
	_config.pin_d1			= Y3_GPIO_NUM;
	_config.pin_d2			= Y4_GPIO_NUM;
	_config.pin_d3			= Y5_GPIO_NUM;
	_config.pin_d4			= Y6_GPIO_NUM;
	_config.pin_d5			= Y7_GPIO_NUM;
	_config.pin_d6			= Y8_GPIO_NUM;
	_config.pin_d7			= Y9_GPIO_NUM;
	_config.pin_xclk		= XCLK_GPIO_NUM;
	_config.pin_pclk		= PCLK_GPIO_NUM;
	_config.pin_vsync		= VSYNC_GPIO_NUM;
	_config.pin_href		= HREF_GPIO_NUM;
	_config.pin_sccb_sda	= SIOD_GPIO_NUM;
	_config.pin_sccb_scl	= SIOC_GPIO_NUM;
	_config.pin_pwdn		= PWDN_GPIO_NUM;
	_config.pin_reset		= RESET_GPIO_NUM;
	_config.xclk_freq_hz	= 10000000;
	_config.frame_size		= FRAMESIZE_UXGA;
	_config.pixel_format	= PIXFORMAT_JPEG;
	_config.grab_mode		= CAMERA_GRAB_WHEN_EMPTY;
	_config.fb_location		= CAMERA_FB_IN_PSRAM;
	_config.jpeg_quality	= 12;
	_config.fb_count		= 1;
	if(psramFound())
	{
		_config.jpeg_quality	= 10;
		_config.fb_count		= 2;
		_config.grab_mode		= CAMERA_GRAB_LATEST;
	}
	else
	{
		_config.frame_size		= FRAMESIZE_SVGA;
		_config.fb_location		= CAMERA_FB_IN_DRAM;
	}
	err = esp_camera_init(&_config);
	if (err != ESP_OK)
	{
		Serial.printf("Camera init failed with error 0x%x", err);
		return ;
	}
	s = esp_camera_sensor_get();
	s->set_vflip(s, 1);
	s->set_brightness(s, 1);
	s->set_saturation(s, 0);
	Serial.println("Camera configuration complete!");
}

camera_fb_t	*CameraService::captureFrame(void)
{
	camera_fb_t	*fb;

	fb = esp_camera_fb_get();
	if (!fb)
	{
		Log::error("Camera capture failed");
		return (NULL);
	}
	return (fb);
}

void	CameraService::returnFrame(camera_fb_t *fb)
{
	esp_camera_fb_return(fb);
}

bool	CameraService::captureToSD(const char *path, SDService &sd)
{
	camera_fb_t	*fb;
	bool		ok;

	fb = esp_camera_fb_get();
	if (!fb)
	{
		Log::error("Camera capture failed");
		return (false);
	}
	if (fb->format != PIXFORMAT_JPEG)
	{
		Log::error("Frame is not JPEG");
		esp_camera_fb_return(fb);
		return (false);
	}
	ok = sd.writeFile(path, fb->buf, fb->len);
	esp_camera_fb_return(fb);
	return (ok);
}
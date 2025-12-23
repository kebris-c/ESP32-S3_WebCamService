#include "include/WebServerService.hpp"

const char	*WebServerService::_STREAM_BOUNDARY = "\r\n--frame\r\n";
const char	*WebServerService::_STREAM_PART = "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n";
const char	*WebServerService::_STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=frame";

WebServerService::WebServerService(CameraService &cam, SDService &sd)
	: _cam(cam), _sd(sd), _server(nullptr)
{
}

/*
 *	--- Camera HTTP Server ---
 *				&
 *	--- Stream HTTP Server ---
*/
void	WebServerService::init(void)
{
    httpd_config_t	config;
	httpd_uri_t		index_uri = {};
	httpd_uri_t		capture_uri = {};
	httpd_uri_t		stream_uri = {};

	config = HTTPD_DEFAULT_CONFIG();
	config.server_port = 80;

	index_uri.uri = "/";
	index_uri.method = HTTP_GET;
	index_uri.handler = _index_handler;
	index_uri.user_ctx = this;

    capture_uri.uri = "/capture";
	capture_uri.method = HTTP_GET;
	capture_uri.handler = _capture_handler;
	capture_uri.user_ctx = this;

	stream_uri.uri = "/stream";
	stream_uri.method = HTTP_GET;
	stream_uri.handler = _stream_handler;
	stream_uri.user_ctx = this;
	if (httpd_start(&_server, &config) == ESP_OK)
	{
		httpd_register_uri_handler(_server, &index_uri);
		httpd_register_uri_handler(_server, &capture_uri);
		httpd_register_uri_handler(_server, &stream_uri);
		Log::info("HTTP server started on port 80");
	}
	else
		Log::error("Failed to start HTTP server");
}

/*
 *	--- Handlers ---
 */
esp_err_t	WebServerService::_index_handler(httpd_req_t *req)
{
	String				ipStr;
	String				html;

	ipStr = WiFi.localIP().toString();
	html  = "<!DOCTYPE html><html><head><meta charset='utf-8'><title>ESP32-Camera</title></head><body>";
	html += "<h1>ESP32 Camera Stream</h1>";
	html += "<img id='stream' width='640' height='480'/><br/>";
	html += "<button onclick='capture()'>Capture</button>";
	html += "<pre id='out'></pre>";
	html += "<script>"
			"function capture(){fetch('/capture').then(r=>r.text()).then(t=>document.getElementById('out').innerText=t);}"
			"document.addEventListener('DOMContentLoaded', function(){"
			"var img=document.getElementById('stream');"
			"img.src='http://" + ipStr + ":80/stream';"
			"});"
			"</script></body></html>";
	httpd_resp_set_type(req, "text/html");
	httpd_resp_send(req, html.c_str(), html.length());
	return (ESP_OK);
}

esp_err_t	WebServerService::_capture_handler(httpd_req_t *req)
{
	WebServerService	*self;
	camera_fb_t			*fb;
	String				fname;
	bool				ok;

	self = (WebServerService *)req->user_ctx;
	fb = self->_cam.captureFrame();
	if (!fb)
	{
		httpd_resp_send_500(req);
		return (ESP_FAIL);
	}
	fname = "/photo_" + String(millis()) + ".jpg";
	ok = self->_sd.writeFile(fname.c_str(), fb->buf, fb->len);
	self->_cam.returnFrame(fb);
	if (!ok)
	{
		httpd_resp_send_500(req);
		return (ESP_FAIL);
	}
	httpd_resp_send(req, ("Saved: " + fname).c_str(), -1);
	return (ESP_OK);
}

esp_err_t	WebServerService::_stream_handler(httpd_req_t *req)
{
	WebServerService	*self;
    camera_fb_t			*fb;
    esp_err_t			res;
	char				part_buf[128];
	size_t				hlen;
	
	self = (WebServerService *)req->user_ctx;
	res = ESP_OK;
	httpd_resp_set_type(req, _STREAM_CONTENT_TYPE);
	httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
	while (true)
	{
		fb = self->_cam.captureFrame();
		if (!fb)
			break ;
		hlen = snprintf(part_buf, 128, _STREAM_PART, fb->len);
		res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, strlen(_STREAM_BOUNDARY));
		if (res != ESP_OK)
			break ;
		res = httpd_resp_send_chunk(req, part_buf, hlen);
		if (res != ESP_OK)
			break ;
		res = httpd_resp_send_chunk(req, (const char*)fb->buf, fb->len);
		if (res != ESP_OK)
			break ;
		self->_cam.returnFrame(fb);
	}
	if (fb)
		self->_cam.returnFrame(fb);
	httpd_resp_send_chunk(req, NULL, 0);
	return (res);
}
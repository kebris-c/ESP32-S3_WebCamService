# ESP32 Camera Web Server

A lightweight web-based camera streaming and capture system built for the ESP32 platform.

This project runs an HTTP server on an ESP32 with camera support, allowing:
- Live MJPEG video streaming from a browser
- On-demand photo capture
- Saving captured images to an SD card
- Simple web interface accessible from any device on the local network

Developed as a personal embedded systems project.

## Features

- 📷 Live MJPEG stream over HTTP (`/stream`)
- 📸 Capture single images via HTTP endpoint (`/capture`)
- 💾 Save captured images to SD card
- 🌐 Minimal web interface served directly by the ESP32
- ⚙️ Modular C++ design (Camera, WiFi, SD, WebServer services)

## Tech Stack

- ESP32 / ESP32-S3
- ESP-IDF HTTP Server (`esp_http_server`)
- C++
- MJPEG streaming (`multipart/x-mixed-replace`)
- SD card filesystem
- Arduino-style networking (`WiFi`)

## Project Structure
'''
.
├── camera_service/
|      ├── include/
|      |     ├── App.hpp
|      |     ├── CameraPins.hpp
|      |     ├── CameraService.hpp
|      |     ├── Log.hpp
|      |     ├── SDService.hpp
|      |     ├── WebServerService.hpp
|      |     └── WifiService.hpp
|      ├── src/
|      |     ├── App/
|      |     |    └── App.cpp
|      |     ├── CameraService/
|      |     |    └── CameraService.cpp # Camera initialization and frame handling
|      |     ├── SDService/
|      |     |    └── SDService.cpp # SD card read/write abstraction
|      |     ├── utils/
|      |     |    └── Log.cpp # Simple logging utility
|      |     ├── WebServerService/
|      |     |    └── WebServerservice.cpp # HTTP server and request handlers
|      |     └── WifiService/
|      |          └── WifiService.cpp # WiFi connection management
|      └── camera_service.ino
└── README.md

'''

Each service is designed to be independent and reusable.

## Endpoints

| Endpoint   | Description                          |
|------------|--------------------------------------|
| `/`        | Web UI with live stream and controls |
| `/stream`  | MJPEG live video stream              |
| `/capture` | Capture image and save to SD card    |

## Usage

1. Flash the firmware to the ESP32
2. Connect the device to WiFi
3. Open a browser and navigate to the ESP32 IP address
4. View the live stream or capture images directly from the web interface

## Notes

- The streaming loop runs continuously while the client is connected.
- No artificial FPS limit is enforced by default.
- Designed for educational and experimental use.

## License

This project is currently **not licensed**.

The code was written as a personal learning project while studying at **42**.
If you plan to reuse or modify it, please contact me or wait for a license to be added.

## Author

**kebris-c**  
42 student  
GitHub: https://github.com/kebris-c

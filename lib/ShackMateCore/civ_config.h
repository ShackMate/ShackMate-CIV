// List of allowed CI-V FROM addresses for filtering (edit as needed)
#include <array>
constexpr size_t NUM_VALID_FROM_ADDRS = 3;
static constexpr std::array<uint8_t, NUM_VALID_FROM_ADDRS> VALID_FROM_ADDRS = {0x94, 0xA2, 0xC0};
#pragma once

// -------------------------------------------------------------------------
// CI-V Controller Configuration (overrides ShackMateCore defaults)
// -------------------------------------------------------------------------
#define NAME "ShackMate - CI-V Controller"
#define VERSION "2.2.0"
#define AUTHOR "Half Baked Circuits"
#define MDNS_NAME "ShackMate-CI-V"

// Network Configuration
#define UDP_PORT 4210
#define WEBSOCKET_PORT 4000
#define HTTP_PORT 80

// CI-V Specific Configuration
#define CIV_ADDRESS 0xC0 // CI-V controller address
#define DEFAULT_CIV_BAUD 19200
#define MAX_CIV_FRAME 64

// Hardware Pin Definitions for different M5 devices
#if defined(M5ATOM_S3) || defined(ARDUINO_M5Stack_ATOMS3)
// AtomS3 pin assignments
#define MY_RX1 5
#define MY_TX1 7
#define MY_RX2 39
#define MY_TX2 38
#define LED_PIN 35            // AtomS3 LED is GPIO35 (G35)
#define WIFI_RESET_BTN_PIN 41 // AtomS3 button is GPIO41 (G41)
#else
// M5Atom pin assignments
#define MY_RX1 22
#define MY_TX1 23
#define MY_RX2 21
#define MY_TX2 25
#define LED_PIN 27            // M5Atom LED is GPIO27 (G27)
#define WIFI_RESET_BTN_PIN 39 // M5Atom button is GPIO39
#endif

// CI-V Specific Timing Constants
static constexpr unsigned long CACHE_WINDOW_MS = 500; // system checks if it has already seen that message in the last 500 ms.
static constexpr int CACHE_MAX_SIZE = 30;             // system will remember up to 64 recent messages for duplicate detection.

// WebSocket Constants for CI-V Controller
static constexpr unsigned long WS_PING_INTERVAL_MS = 30000;  // Interval for sending ping messages to keep connection alive
static constexpr unsigned long WS_PING_TIMEOUT_MS = 5000;    // Timeout for waiting for a pong response after sending a ping
static constexpr unsigned long WS_RECONNECT_DELAY_MS = 2000; // Delay between reconnection attempts if the WebSocket connection is lost
static constexpr int WS_MESSAGE_RATE_LIMIT = 25;             // Increased from 10 to 30 messages/second for high CI-V traffic
static constexpr int WS_MAX_RECONNECT_ATTEMPTS = 0;          // 0 = unlimited reconnection attempts

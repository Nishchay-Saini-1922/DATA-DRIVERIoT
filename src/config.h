/*
 * Configuration File - Pin Definitions and Constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// ==================== LCD Display ====================
#define LCD_ADDR 0x27            // I2C address for 16x2 LCD
#define LCD_SDA_PIN 21           // SDA pin on ESP32
#define LCD_SCL_PIN 22           // SCL pin on ESP32
#define LCD_COLS 16
#define LCD_ROWS 2

// ==================== RFID Reader ====================
#define RFID_SS_PIN 5            // Chip select
#define RFID_RST_PIN 17          // Reset pin
#define SPI_SCK 18               // SPI Clock
#define SPI_MOSI 23              // SPI MOSI
#define SPI_MISO 19              // SPI MISO

// ==================== Buzzer/Speaker ====================
#define BUZZER_PIN 13            // PWM pin for buzzer
#define BUZZER_CHANNEL 0         // PWM channel

// ==================== 4x4 Keypad ====================
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
const uint8_t KEYPAD_ROW_PINS[KEYPAD_ROWS] = {32, 33, 25, 26};  // Row pins
const uint8_t KEYPAD_COL_PINS[KEYPAD_COLS] = {27, 14, 12, 4};   // Column pins

// Keypad Layout
const char KEYPAD_KEYS[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// ==================== Joystick ====================
#define JOYSTICK_X_PIN 35        // Analog X axis
#define JOYSTICK_Y_PIN 34        // Analog Y axis
#define JOYSTICK_BTN_PIN 39      // Digital button
#define JOYSTICK_THRESHOLD 1500  // Analog threshold for detection

// ==================== Lock ====================
#define LOCK_GPIO_PIN 16         // GPIO pin for unlock signal

// ==================== Power Management ====================
#define SLEEP_TIMEOUT_MS 60000   // 60 seconds default
#define WAKE_PIN JOYSTICK_BTN_PIN

// ==================== Audio Tones ====================
#define STARTUP_TONE_FREQ 800
#define STARTUP_TONE_DURATION 200
#define MENU_BEEP_FREQ 1000
#define MENU_BEEP_DURATION 100
#define SELECT_SOUND_FREQ 1200
#define SELECT_SOUND_DURATION 150
#define BACK_SOUND_FREQ 600
#define BACK_SOUND_DURATION 100
#define ERROR_TONE_FREQ 300
#define ERROR_TONE_DURATION 300

// ==================== Battery ====================
#define BATTERY_ADC_PIN 36       // Analog pin for battery voltage
#define BATTERY_VOLTAGE_MAX 8.4  // 2S Li-ion max
#define BATTERY_VOLTAGE_MIN 6.0  // 2S Li-ion min

// ==================== App State Timeouts ====================
#define APP_IDLE_TIMEOUT 30000   // 30 seconds
#define RFID_READ_TIMEOUT 5000   // 5 seconds

// ==================== Memory ====================
#define MAX_STORED_CARDS 50      // Maximum RFID cards to store
#define MAX_WIFI_NETWORKS 20     // Maximum Wi-Fi networks to display

#endif
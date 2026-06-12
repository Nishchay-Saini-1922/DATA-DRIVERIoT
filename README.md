# Data Driver v1.0 Alpha

A feature-rich handheld device firmware for ESP32 DevKit V4 with RFID, WiFi, Lock management, and more.

## Features

- **RFID Card Management**: Read, store, and manage RFID card UIDs with associated values
- **WiFi Management**: Scan networks, connect with secure password input, test connectivity
- **Lock Control**: GPIO-based lock/unlock control with timed automation
- **Settings**: Persistent user preferences (volume, sleep timeout, brightness)
- **Device Info**: View firmware version, free memory, and uptime
- **Non-blocking Architecture**: All operations use millis() timing
- **Modular Design**: Easy to extend with new apps

## Hardware

- ESP32 DevKit V4
- 16x2 I2C LCD Display
- MFRC522 RFID Reader
- HW104 Buzzer/Speaker
- 4x4 Matrix Keypad
- Analog Joystick with Push Button
- 2x 2500mAh Li-ion Batteries

## Project Structure

```
src/
├── main.cpp              # Main entry point and boot sequence
├── config.h              # Pin definitions and constants
├── DisplayManager.*      # LCD display control
├── MenuSystem.*          # Menu navigation
├── KeypadHandler.*       # 4x4 keypad input
├── JoystickHandler.*     # Joystick input
├── AudioManager.*        # Buzzer/speaker control
├── RFIDManager.*         # RFID reading/storage
├── NetworkManager.*      # WiFi operations
├── LockManager.*         # Lock control
├── SettingsManager.*     # Persistent settings
├── TextInputEngine.*     # Reusable keyboard input
├── App.h                 # App base class
└── *App.h/.cpp           # Individual app implementations
```

## Build & Upload

### Requirements

- Arduino IDE 1.8.19+ or PlatformIO
- ESP32 Board Support Package
- Required Libraries (see below)

### Required Libraries

Add these via Arduino IDE Library Manager or PlatformIO:

- `LiquidCrystal_I2C` - LCD display control
- `MFRC522` - RFID reader support
- `WiFi` - Built-in ESP32 library
- `EEPROM` - Built-in ESP32 library
- `SPI` - Built-in ESP32 library

### Installation Steps

1. **Arduino IDE Method**:
   ```bash
   # Open Arduino IDE
   # Go to Tools > Board > Boards Manager
   # Search for "esp32" and install latest version
   # Sketch > Include Library > Manage Libraries
   # Install: LiquidCrystal_I2C, MFRC522
   ```

2. **PlatformIO Method**:
   ```bash
   platformio run -t upload
   ```

3. **Manual Compilation**:
   ```bash
   # Set up Arduino environment and compile src/main.cpp
   ```

## Usage

### Boot Sequence

1. Device displays "DATA DRIVER" / "v1.0 ALPHA"
2. Animated loading bar plays
3. Startup sound plays
4. Main menu displayed

### Navigation

- **Joystick Up/Down**: Navigate menu items
- **Joystick Press**: Select item
- **Keypad D**: Back/Return to main menu
- **Keypad 0-9**: Direct number input
- **Keypad A**: Cycle lowercase letters
- **Keypad B**: Toggle uppercase
- **Keypad C**: Cycle symbols
- **Keypad \***: Append character
- **Keypad #**: Confirm input

### Apps

#### RFID App
- Place card on reader to capture UID
- Associate float values with cards
- View stored card information

#### Network App
- Scan available WiFi networks
- Connect with secure password entry
- Display signal strength and IP address

#### Lock App
- View current lock status
- Press joystick to toggle lock
- Supports 3-second auto-lock

#### Settings App
- Adjust volume (0-100%)
- Set sleep timeout (10-600 seconds)
- Adjust LCD brightness
- Toggle sound effects
- Reset to factory defaults

#### About App
- View device name and version
- Display free RAM
- Show system uptime

## Power Management

- **Sleep Mode**: Device enters deep sleep after timeout
- **Wake Sources**: Joystick button
- **Battery**: 2x 2500mAh Li-ion (8.4V max, 6V min)

## Future Enhancements

- Morse code generator
- Simple AI assistant interface
- Retro games
- File browser with SD card support
- NFC tag support (upgrade from RFID)
- Data logging and export
- Custom firmware updates via WiFi

## Contributing

This is an alpha release. Future versions will include:

- Improved UI/UX
- More robust error handling
- Power consumption optimization
- Extended app ecosystem

## License

MIT License - See LICENSE file

## Author

Created by Nishchay Saini

## Support

For issues, feature requests, or questions, please open an issue in the GitHub repository.
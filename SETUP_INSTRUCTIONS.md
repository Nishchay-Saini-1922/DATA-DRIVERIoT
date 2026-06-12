# Data Driver v1.0 Alpha - Setup Instructions

## Prerequisites

- Arduino IDE 1.8.19 or later (or PlatformIO)
- ESP32 Board Support Package installed
- USB-to-Serial programmer or ESP32 DevKit with onboard USB
- All components as listed in README.md

## Step 1: Install Arduino IDE & ESP32 Support

### Windows/Mac/Linux

1. Download Arduino IDE from https://www.arduino.cc/en/software
2. Install and launch Arduino IDE
3. Go to **Preferences** (Arduino > Preferences on Mac)
4. Add this URL to "Additional Boards Manager URLs":
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
5. Click OK, then go to **Tools > Board > Boards Manager**
6. Search for "esp32" and install latest version
7. Restart Arduino IDE

## Step 2: Install Required Libraries

In Arduino IDE:

1. Go to **Sketch > Include Library > Manage Libraries**
2. Search and install:
   - **LiquidCrystal_I2C** (by Frank de Brabander)
   - **MFRC522** (by Miguel Balboa)
   - **WiFi** (built-in, verify it's available)
   - **EEPROM** (built-in, verify it's available)
   - **SPI** (built-in, verify it's available)

3. Click Install for each library
4. Wait for installation to complete

## Step 3: Create Project Folder Structure

Create the following directory structure on your computer:

```
Data-Driver-V1.0-Alpha/
│
└── src/
    ├── main.cpp
    ├── config.h
    ├── DisplayManager.h
    ├── DisplayManager.cpp
    ├── MenuSystem.h
    ├── MenuSystem.cpp
    ├── KeypadHandler.h
    ├── KeypadHandler.cpp
    ├── JoystickHandler.h
    ├── JoystickHandler.cpp
    ├── AudioManager.h
    ├── AudioManager.cpp
    ├── RFIDManager.h
    ├── RFIDManager.cpp
    ├── NetworkManager.h
    ├── NetworkManager.cpp
    ├── LockManager.h
    ├── LockManager.cpp
    ├── SettingsManager.h
    ├── SettingsManager.cpp
    ├── TextInputEngine.h
    ├── TextInputEngine.cpp
    ├── App.h
    ├── RFIDApp.h
    ├── RFIDApp.cpp
    ├── NetworkApp.h
    ├── NetworkApp.cpp
    ├── LockApp.h
    ├── LockApp.cpp
    ├── SettingsApp.h
    ├── SettingsApp.cpp
    ├── AboutApp.h
    └── AboutApp.cpp
```

## Step 4: Copy Source Files

Copy all the source code files provided in this project into the `src/` folder.

## Step 5: Verify Hardware Connections

Before uploading code:

1. **Power OFF** the ESP32
2. Double-check all pin connections against **WIRING_DIAGRAM.md**
3. Verify no loose wires or short circuits
4. Check I2C address of LCD (default: 0x27, may vary)
5. Ensure RFID reader is properly seated

### Finding LCD I2C Address

If LCD doesn't display, find its address:

1. Upload the I2C Scanner sketch:
```cpp
#include <Wire.h>

void setup() {
  Wire.begin(21, 22); // SDA, SCL on ESP32
  Serial.begin(115200);
}

void loop() {
  for (int addr = 0; addr < 128; addr++) {
    Wire.beginTransmission(addr);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found I2C device at 0x");
      Serial.println(addr, HEX);
    }
  }
  delay(5000);
}
```

2. Update **config.h**:
```cpp
#define LCD_ADDR 0x?? // Use found address
```

## Step 6: Configure Board Settings

In Arduino IDE:

1. Go to **Tools > Board** and select **ESP32 Dev Module**
2. Configure these settings:
   - **CPU Frequency**: 240 MHz
   - **Flash Mode**: DIO
   - **Flash Size**: 4MB
   - **Partition Scheme**: Default 4MB with spiffs
   - **Core Debug Level**: None
   - **PSRAM**: Disabled
   - **Port**: Select your COM port (COMx on Windows, /dev/ttyUSBx on Linux)
   - **Upload Speed**: 921600 (or 115200 if upload fails)

## Step 7: Upload Code

### Method A: Arduino IDE

1. Open **src/main.cpp** in Arduino IDE
2. Go to **Sketch > Verify** to check for compilation errors
3. If verification passes, go to **Sketch > Upload**
4. Wait for upload to complete (may take 1-2 minutes)

Monitor output in Serial Monitor:
- Go to **Tools > Serial Monitor**
- Set Baud Rate to **115200**
- You should see boot messages

### Method B: PlatformIO (Recommended for Advanced Users)

1. Install PlatformIO Extension in VS Code
2. Create **platformio.ini**:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600
lib_deps =
    LiquidCrystal_I2C
    MFRC522
    WiFi
```

3. Run: `platformio run -t upload`

## Step 8: First Boot

1. Power on the ESP32
2. Watch the boot sequence:
   - "DATA DRIVER" / "v1.0 ALPHA" displayed
   - Loading bar animation
   - Startup sound plays
   - Main menu appears
3. Check Serial Monitor for debug messages

### Initial Troubleshooting

**LCD Not Displaying**:
- Verify I2C address (see Step 5)
- Check SDA/SCL wiring
- Verify 3.3V power supply
- Try I2C scanner to confirm connection

**RFID Not Working**:
- Verify SPI pins (SCK, MOSI, MISO, CS, RST)
- Ensure RFID powered at 3.3V
- Check antenna range (place card 1-3cm from reader)
- Monitor serial output for RFID initialization messages

**Keypad Not Responding**:
- Verify row/column pin connections
- Test with simple key press detection sketch
- Check debounce timing in KeypadHandler

**Joystick Not Working**:
- Monitor ADC values in serial monitor
- Verify VRx/VRy analog pins
- Check center position values
- Adjust JOYSTICK_THRESHOLD in config.h

**Buzzer Silent**:
- Verify GPIO 13 PWM capability
- Check buzzer polarity
- Monitor PWM frequency output
- Verify audio manager is initialized

## Step 9: Configuration Customization

Edit **config.h** to customize:

```cpp
// Change pin assignments
#define LCD_SDA_PIN 21
#define LCD_SCL_PIN 22

// Adjust sensitivity
#define JOYSTICK_THRESHOLD 1500

// Modify timeouts
#define SLEEP_TIMEOUT_MS 60000

// Change audio frequencies
#define STARTUP_TONE_FREQ 800
```

## Step 10: Testing Each System

### Test 1: Display
```cpp
// In main.cpp setup():
displayManager->displayBoth("Testing LCD", "All systems OK");
```

### Test 2: Audio
```cpp
// In main.cpp setup():
audioManager->playStartupSound();
```

### Test 3: Keypad
Monitor Serial Monitor while pressing keys, should show key codes.

### Test 4: Joystick
Move joystick and watch Serial Monitor output.

### Test 5: RFID
Place RFID card on reader, should output UID in Serial Monitor.

### Test 6: WiFi
Launch Network App and scan for available networks.

## Step 11: Power Management Setup

1. **Battery Connection**:
   - Connect positive terminal to battery management circuit
   - Connect negative to GND
   - Use 8.4V nominal (2S Li-ion in series)

2. **Testing Power**:
   - Monitor current draw with multimeter
   - Should be ~200mA average
   - Peaks to 300-400mA during RF operations

3. **Sleep Mode** (Advanced):
   - Device sleeps after SLEEP_TIMEOUT_MS
   - Wake with joystick button
   - Configured in config.h

## Step 12: Data Storage

The device stores settings in EEPROM:

- Volume level
- Sleep timeout
- LCD brightness
- Sound preferences
- RFID card database (in-memory during operation)

Settings persist after power cycles.

## Troubleshooting Common Issues

| Issue | Solution |
|-------|----------|
| Upload fails | Reduce upload speed to 115200 bps |
| Compilation errors | Verify all libraries installed |
| Device won't boot | Check USB cable and serial driver |
| Serial Monitor shows garbage | Set baud rate to 115200 |
| App crashes on startup | Monitor heap size (may need to optimize) |
| RFID unreliable | Reduce SPI frequency or check wiring |
| WiFi doesn't connect | Verify password input mechanism |
| Buzzer won't sound | Check GPIO 13 is PWM-capable |

## Verification Checklist

- [ ] Arduino IDE and ESP32 board support installed
- [ ] All required libraries installed
- [ ] Source files copied to correct locations
- [ ] Hardware connections verified against wiring diagram
- [ ] LCD I2C address confirmed
- [ ] Code compiles without errors
- [ ] Code uploads successfully
- [ ] Device boots and displays main menu
- [ ] All 5 apps launch and respond to input
- [ ] Serial Monitor shows initialization messages
- [ ] Battery management tested
- [ ] Settings save and persist

## Next Steps

1. **Customize Apps**: Modify app behavior in respective .cpp files
2. **Add New Apps**: Create new app class inheriting from App base class
3. **Expand Features**: Add new managers for additional hardware
4. **Optimize Power**: Fine-tune sleep settings for battery life
5. **Data Logging**: Store operation logs in EEPROM/SPIFFS

## Support & Documentation

- Refer to **README.md** for feature overview
- Check **WIRING_DIAGRAM.md** for hardware connections
- Review source code comments for detailed implementation info
- ESP32 Docs: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/
- Arduino Reference: https://www.arduino.cc/reference/en/

---

**Happy Building!** 🚀

For issues or questions, refer to the GitHub repository or create an issue.
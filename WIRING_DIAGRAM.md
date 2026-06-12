# Data Driver v1.0 Alpha - Wiring Diagram

## Pinout Summary

```
ESP32 PIN          COMPONENT              PIN
================   =======================  ==========
GPIO 21 (SDA)      16x2 LCD I2C          SDA
GPIO 22 (SCL)      16x2 LCD I2C          SCL
GND                16x2 LCD I2C          GND
3V3                16x2 LCD I2C          VCC

GPIO 5             MFRC522 RFID          CS (Chip Select)
GPIO 17            MFRC522 RFID          RST (Reset)
GPIO 18 (SCK)      MFRC522 RFID          CLK
GPIO 23 (MOSI)     MFRC522 RFID          MOSI
GPIO 19 (MISO)     MFRC522 RFID          MISO
GND                MFRC522 RFID          GND
3V3                MFRC522 RFID          3.3V

GPIO 13 (PWM)      HW104 Buzzer          Signal
GND                HW104 Buzzer          GND

GPIO 32            4x4 Keypad            Row 1
GPIO 33            4x4 Keypad            Row 2
GPIO 25            4x4 Keypad            Row 3
GPIO 26            4x4 Keypad            Row 4
GPIO 27            4x4 Keypad            Col 1
GPIO 14            4x4 Keypad            Col 2
GPIO 12            4x4 Keypad            Col 3
GPIO 4             4x4 Keypad            Col 4
GND                4x4 Keypad            GND

GPIO 35 (ADC)      Joystick              VRx (X-axis)
GPIO 34 (ADC)      Joystick              VRy (Y-axis)
GPIO 39            Joystick              SW (Push Button)
+5V                Joystick              +5V
GND                Joystick              GND

GPIO 16            Lock Control Relay    Signal
GND                Lock Control Relay    GND

GPIO 36 (ADC)      Battery Voltage       Signal (optional)
GND                Battery               GND

GND                All Components        GND (Common)
3V3                All 3.3V Components   3.3V (Common)
5V                 5V Components         5V (Common)
```

## Detailed Connections

### 16x2 I2C LCD Module

```
LCD Module Pin    ESP32 Pin    Notes
=============     =========    =====
GND               GND          Ground
VCC               3V3          Power (3.3V)
SDA               GPIO 21      I2C Data
SCL               GPIO 22      I2C Clock
```

### MFRC522 RFID Reader

```
RFID Pin      ESP32 Pin    SPI Function    Notes
========      =========    ============    =====
SDA(CS)       GPIO 5       Chip Select     Active Low
SCK           GPIO 18      SPI Clock       
MOSI          GPIO 23      Master Out      
MISO          GPIO 19      Master In       
IRQ           (not used)   Interrupt       Optional
GND           GND          Ground          
RST           GPIO 17      Reset           Active Low
3.3V          3V3          Power           

SPI Frequency: 1 MHz (MFRC522 supports up to 10 MHz)
```

### HW104 Buzzer/Speaker

```
Buzzer Pin    ESP32 Pin    Notes
==========    =========    =====
Signal        GPIO 13      PWM for frequency control
GND           GND          Ground
(Positive)    GPIO 13      (if active high)
(Negative)    GND          
```

### 4x4 Matrix Keypad

```
Keypad Layout:
1  2  3  A
4  5  6  B
7  8  9  C
*  0  #  D

Row Pins:
Row 1  -  GPIO 32
Row 2  -  GPIO 33
Row 3  -  GPIO 25
Row 4  -  GPIO 26

Column Pins:
Col 1  -  GPIO 27
Col 2  -  GPIO 14
Col 3  -  GPIO 12
Col 4  -  GPIO 4

All rows and columns tied to GND via pull-down resistors (optional, ESP32 has internal pull-ups)
```

### Joystick Module

```
Joystick Pin      ESP32 Pin    ADC Channel    Notes
============      =========    ===========    =====
GND               GND          N/A            Ground
+5V               5V           N/A            Power (can also use 3V3)
VRx (X-axis)      GPIO 35      ADC1_CH7       Analog input
VRy (Y-axis)      GPIO 34      ADC1_CH6       Analog input
SW (Button)       GPIO 39      N/A            Digital input (0=pressed)

Range: 0-4095 (12-bit ADC)
Threshold: ~2048 (center) ±1500 for direction detection
```

### Lock Control (GPIO Relay Module)

```
Relay Module      ESP32 Pin    Notes
============      =========    =====
GND               GND          Ground
IN (Signal)       GPIO 16      Active HIGH = Unlock
(Power)           5V           External relay power
NC/NO/COM         Lock Solenoid Connect based on lock type
```

### Battery Voltage Monitoring (Optional)

```
Battery (2S Li-ion)    ESP32 Pin    Notes
===================    =========    =====
+8.4V (max)            GPIO 36      Via voltage divider
                       (ADC Input)  
GND                    GND          Ground
```

Voltage Divider Calculation (optional):
- For 8.4V max to 3.3V ADC:
- R1 = 10kΩ, R2 = 4.7kΩ
- Vout = Vin * (R2 / (R1 + R2))
- 8.4V * (4.7 / 14.7) ≈ 2.67V

## Power Distribution

```
Power Hierarchy:
==================

2x 2500mAh Li-ion Batteries (Series = 8.4V nominal)
         ↓
[Battery Management Circuit]
         ↓
         ├─→ 3V3 Regulator  ─→ ESP32, LCD, RFID, Keypad
         ├─→ 5V Regulator   ─→ Joystick, Relay module
         └─→ Logic Gate     ─→ Buzzer (GPIO PWM)

Capacitor Placement:
- 100µF near ESP32 power pins
- 10µF near RFID reader power
- 10µF near LCD power
- 100nF ceramic on each IC power pin (decoupling)
```

## Assembly Notes

1. **I2C Pullups**: LCD I2C usually has built-in 4.7kΩ pullups. If conflicts, disable or adjust.

2. **SPI Configuration**: All SPI devices use same SCK/MOSI/MISO, different CS pins.

3. **GPIO Availability**: 
   - Total GPIO: 30 (esp32)
   - ADC Channels: 16 (12-bit)
   - PWM Channels: 16 (timers)
   - Available after config: ~5-8 GPIO

4. **Current Draw**:
   - ESP32: ~80mA
   - LCD: ~15mA
   - RFID: ~50mA
   - Buzzer: ~30mA (variable)
   - Joystick: ~10mA
   - Keypad: <5mA
   - **Total**: ~200mA average

5. **Stability**:
   - Use short wires (minimize noise)
   - Keep SPI/I2C lines short
   - Add 100nF decoupling caps near power pins
   - Use ferrite bead on power supply if noisy

## Recommended Component Sources

- ESP32 DevKit V4: AZ-Delivery, Espressif
- 16x2 LCD I2C: Arduino-compatible module (generic)
- MFRC522: RC522 module (5V tolerant)
- HW104 Buzzer: 5V active buzzer or passive speaker with amplifier
- 4x4 Keypad: Standard matrix keypad
- Joystick: 5V analog joystick module
- Relay Module: 1-channel 5V relay

## Testing Checklist

- [ ] Power supply stability (measure with multimeter)
- [ ] SPI communication with RFID
- [ ] I2C communication with LCD
- [ ] All GPIO inputs/outputs
- [ ] Keypad matrix scanning
- [ ] Joystick ADC values
- [ ] Buzzer PWM frequency output
- [ ] Battery monitoring (if implemented)
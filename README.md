# Audio-input-selector

A digitally controlled audio input selector based on Arduino, designed to switch between 6 different audio sources. The project features a rotary encoder for menu navigation, an OLED display for visual feedback, and LED indicators for the active channel.

It retains the last selected input in non-volatile memory (EEPROM), ensuring the system boots up with the previously used source active.

## Features

- **6-Channel Input Switching:** Supports AUX, USB, Bluetooth, Optical, Wi-Fi, and HDMI ARC.
- **Intuitive Interface:** Rotary encoder for scrolling and selection.
- **Visual Feedback:**
  - **OLED Display (128x64):** Shows custom bitmap icons and status (Active/Select) for each mode.
  - **LED Indicators:** Dedicated LED output for the currently active channel.
- **Memory Function:** Automatically saves the active channel to EEPROM and restores it on reboot.
- **Smart LED Management:** LEDs remain off while scrolling and only light up upon confirmation.

## Hardware Requirements

- **Microcontroller:** Arduino Nano / Uno (or compatible)
- **Display:** 0.96" I2C OLED (SSD1306 driver, 128x64 pixels)
- **Input Device:** Rotary Encoder (EC11 or similar) with Push Button
- **Indicators:** 6x LEDs (one for each channel)
- **Audio Switching:** Relays or Audio Multiplexer IC (e.g., CD4052) controlled by the LED pins.

## Pin Configuration

| Component           | Pin Name    | Arduino Pin     |
| :------------------ | :---------- | :-------------- |
| **Rotary Encoder**  | CLK (A)     | D3              |
|                     | DT (B)      | D2              |
|                     | SW (Button) | D7              |
| **OLED Display**    | SDA         | A4 (or SDA pin) |
|                     | SCL         | A5 (or SCL pin) |
| **Channel Outputs** | AUX         | D4              |
|                     | USB         | D5              |
|                     | Bluetooth   | D6              |
|                     | Optical     | D9              |
|                     | Wi-Fi       | D10             |
|                     | HDMI        | D11             |

_> **Note:** The LEDs in this code are configured as **Active LOW** (LOW = ON, HIGH = OFF). If you are using standard LEDs connected to Ground, you may need to invert the logic in `updateLEDs()` or wire your LEDs to VCC._

## 📦 Dependencies

This project requires the following Arduino libraries (installable via Library Manager):

1.  **Adafruit_GFX**
2.  **Adafruit_SSD1306**
3.  **Wire** (Built-in)
4.  **EEPROM** (Built-in)

## How It Works

1.  **Boot Up:** The system reads the last saved mode from EEPROM (address 0). It immediately activates that channel and displays "ACTIVE".
2.  **Navigation:** Turning the rotary encoder scrolls through the 6 modes.
    - The screen displays `< SELECT >` to indicate browsing mode.
    - The channel LEDs turn **OFF** while scrolling to indicate the new choice is not yet active.
3.  **Selection:** Pressing the encoder button selects the current mode.
    - The selection is saved to EEPROM.
    - The corresponding pin goes LOW (activating the LED/Relay).
    - The screen updates to show "ACTIVE".

## Custom Icons

The code includes 18x16 pixel bitmaps for each input source:

- `icon_aux`
- `icon_bt` (Bluetooth)
- `icon_hdmi`
- `icon_optical`
- `icon_usb`
- `icon_wifi`

## License

MIT License - Open for modification and use.

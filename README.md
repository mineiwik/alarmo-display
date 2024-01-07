# alarmo-display

**alarmo-display** is a project that provides an interface for the [alarmo HomeAssistant integration](https://github.com/nielsfaber/alarmo). It allows you to arm and disarm your alarm system via a touchscreen keypad. This project is designed to work specifically with the following hardware:

- MCU: NodeMCU V2 (ESP8266)
- TFT screen Driver: ILI9341
- Touchscreen Driver: XPT2046

**alarmo-display** communicates with the alarmo integration using MQTT.

## Features

- Easily arm and disarm your alarm system via a touchscreen keypad.
- MQTT integration ensures real-time communication with the alarmo HomeAssistant integration.
- Configurable settings to adapt to your specific requirements.

## Installation

To set up **alarmo-display**, follow these steps:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/mineiwik/alarmo-display.git
   ```

2. Open the project with VSCode and make sure the [PlatformIO](https://platformio.org/install/ide?install=vscode) extension is installed.

3. Copy and rename the `secrets.ini.example` file to `secrets.ini`

4. Configure the project by editing the `secrets.ini` file to match your MQTT broker settings, WiFi settings and other preferences.

5. Build and flash the binary using the PlatformIO interface.

8. Enjoy controlling your alarm system with the **alarmo-display** touchscreen interface!

## Contributing

Contributions to **alarmo-display** are welcome! If you'd like to improve this project, please feel free to open issues or submit pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to [nielsfaber](https://github.com/nielsfaber) for creating the [alarmo HomeAssistant integration](https://github.com/nielsfaber/alarmo), which this project is built to complement.

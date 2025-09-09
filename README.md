# Smart Home Temperature Control System with Password Protection

This project is a **smart home temperature control system** developed using an **ATmega32 microcontroller**, **LM35 temperature sensor**, **16x2 LCD display**, and a **keypad**. It allows the user to monitor room temperature and control the system only after entering a valid password. The password is stored in the EEPROM to ensure it is saved even after power loss.

## Features

- **Password protection** for secure access  
- Real-time temperature monitoring using **LM35 sensor**  
- User-settable password stored in **EEPROM**  
- Temperature displayed on **16x2 LCD**  
- Keypad interface for password entry and system interaction  

## Components Used

- **Microcontroller:** ATmega32  
- **Temperature Sensor:** LM35  
- **Display:** 16x2 LCD  
- **Input:** 4x4 Keypad  
- **Power Supply:** 5V DC  

## How It Works

1. On system startup, the user is prompted to enter a password.  
2. The password is compared with the one stored in EEPROM.  
   - If correct: The system grants access to temperature monitoring and control.  
   - If incorrect: The system denies access and prompts for retry.  
3. Once authenticated, the LM35 sensor reads the room temperature and displays it on the LCD.  
4. The user can change the password, which will overwrite the old one in EEPROM.  

## Circuit Overview

- **LM35 sensor** connected to ADC pin of ATmega32  
- **LCD** operates in 4-bit mode  
- **Keypad** connected to digital I/O pins for password input  
- **EEPROM** stores the password permanently (until changed)  

## Software & Tools

- **Language:** C (AVR-GCC)  
- **IDE:** Eclipse   

## License

This project is licensed under the **MIT License** – feel free to use and modify it.
only test

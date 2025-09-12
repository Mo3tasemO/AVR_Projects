# ========= Project Settings =========
MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = usbasp        # change to arduino if using Arduino-as-ISP
PORT = COM3                # only needed if uploading via Arduino bootloader
BAUD = 115200

# ========= Tools =========
CXX = avr-g++
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

# ========= Build Flags =========
CXXFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Wextra -fno-exceptions -fno-rtti -std=gnu++17

# ========= Project Files =========
SRC = main.cpp uart.cpp spi_eeprom.cpp nvm_manager.cpp protocol.cpp
OBJ = $(SRC:.cpp=.o)

# ========= Targets =========
all: seat_eeprom.hex

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

seat_eeprom.elf: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

seat_eeprom.hex: seat_eeprom.elf
	$(OBJCOPY) -O ihex -R .eeprom seat_eeprom.elf seat_eeprom.hex

upload: seat_eeprom.hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

clean:
	rm -f *.o *.elf *.hex

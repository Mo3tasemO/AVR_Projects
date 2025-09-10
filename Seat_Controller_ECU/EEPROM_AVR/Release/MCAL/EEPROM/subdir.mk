################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/EEPROM/EEPROM.c 

OBJS += \
./MCAL/EEPROM/EEPROM.o 

C_DEPS += \
./MCAL/EEPROM/EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/EEPROM/%.o: ../MCAL/EEPROM/%.c MCAL/EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



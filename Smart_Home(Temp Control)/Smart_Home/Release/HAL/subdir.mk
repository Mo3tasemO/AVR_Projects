################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KEYPAD.c \
../HAL/LCD.c \
../HAL/LED.c \
../HAL/LM35.c 

OBJS += \
./HAL/KEYPAD.o \
./HAL/LCD.o \
./HAL/LED.o \
./HAL/LM35.o 

C_DEPS += \
./HAL/KEYPAD.d \
./HAL/LCD.d \
./HAL/LED.d \
./HAL/LM35.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c HAL/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



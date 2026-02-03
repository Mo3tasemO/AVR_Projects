################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Integration_Test/APP/main.c 

OBJS += \
./Integration_Test/APP/main.o 

C_DEPS += \
./Integration_Test/APP/main.d 


# Each subdirectory must supply rules for building sources it contributes
Integration_Test/APP/%.o: ../Integration_Test/APP/%.c Integration_Test/APP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



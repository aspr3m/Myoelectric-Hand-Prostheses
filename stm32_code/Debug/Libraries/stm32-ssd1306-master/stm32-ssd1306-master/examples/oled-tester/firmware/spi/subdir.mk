################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/startup_stm32f411xe.s 

S_DEPS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/startup_stm32f411xe.d 

OBJS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/startup_stm32f411xe.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/%.o: ../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/%.s Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi

clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi:
	-$(RM) ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/startup_stm32f411xe.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/startup_stm32f411xe.o

.PHONY: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.c \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.c \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.c \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.c 

C_DEPS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.d \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.d \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.d \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.d 

OBJS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.o \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.o \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.o \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/%.o Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/%.su Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/%.cyclo: ../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/%.c Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I"C:/Users/Mathi/Downloads/prothesis/Prothesis STM32/ProthesisMain/Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi-2f-Src

clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi-2f-Src:
	-$(RM) ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/main.su ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_hal_msp.su ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/stm32f4xx_it.su ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/examples/oled-tester/firmware/spi/Src/system_stm32f4xx.su

.PHONY: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-examples-2f-oled-2d-tester-2f-firmware-2f-spi-2f-Src


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.c \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.c \
../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.c 

C_DEPS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.d \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.d \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.d 

OBJS += \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.o \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.o \
./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.o 


# Each subdirectory must supply rules for building sources it contributes
Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/%.o Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/%.su Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/%.cyclo: ../Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/%.c Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -I"C:/Users/Mathi/Downloads/prothesis/Prothesis STM32/ProthesisMain/Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-ssd1306-2f-src

clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-ssd1306-2f-src:
	-$(RM) ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306.su ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_fonts.su ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.cyclo ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.d ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.o ./Libraries/stm32-ssd1306-master/stm32-ssd1306-master/ssd1306/src/ssd1306_tests.su

.PHONY: clean-Libraries-2f-stm32-2d-ssd1306-2d-master-2f-stm32-2d-ssd1306-2d-master-2f-ssd1306-2f-src


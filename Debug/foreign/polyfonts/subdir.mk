################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../foreign/polyfonts/pfPSansBold16.o \
../foreign/polyfonts/polyfonts.o 

C_SRCS += \
../foreign/polyfonts/pfPSansBold16.c \
../foreign/polyfonts/polyfonts.c 

OBJS += \
./foreign/polyfonts/pfPSansBold16.o \
./foreign/polyfonts/polyfonts.o 

C_DEPS += \
./foreign/polyfonts/pfPSansBold16.d \
./foreign/polyfonts/polyfonts.d 


# Each subdirectory must supply rules for building sources it contributes
foreign/polyfonts/%.o: ../foreign/polyfonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



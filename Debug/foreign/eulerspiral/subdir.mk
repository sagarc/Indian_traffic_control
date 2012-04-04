################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../foreign/eulerspiral/BiArc.o \
../foreign/eulerspiral/euler.o 

CPP_SRCS += \
../foreign/eulerspiral/BiArc.cpp \
../foreign/eulerspiral/euler.cpp 

OBJS += \
./foreign/eulerspiral/BiArc.o \
./foreign/eulerspiral/euler.o 

CPP_DEPS += \
./foreign/eulerspiral/BiArc.d \
./foreign/eulerspiral/euler.d 


# Each subdirectory must supply rules for building sources it contributes
foreign/eulerspiral/%.o: ../foreign/eulerspiral/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



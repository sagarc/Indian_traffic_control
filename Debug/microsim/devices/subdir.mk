################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/devices/MSDevice_HBEFA.o \
../microsim/devices/MSDevice_Routing.o 

CPP_SRCS += \
../microsim/devices/MSDevice_HBEFA.cpp \
../microsim/devices/MSDevice_Routing.cpp 

OBJS += \
./microsim/devices/MSDevice_HBEFA.o \
./microsim/devices/MSDevice_Routing.o 

CPP_DEPS += \
./microsim/devices/MSDevice_HBEFA.d \
./microsim/devices/MSDevice_Routing.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/devices/%.o: ../microsim/devices/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/trigger/MSBusStop.o \
../microsim/trigger/MSCalibrator.o \
../microsim/trigger/MSEmitter.o \
../microsim/trigger/MSLaneSpeedTrigger.o \
../microsim/trigger/MSTriggeredReader.o \
../microsim/trigger/MSTriggeredRerouter.o \
../microsim/trigger/MSTriggeredXMLReader.o 

CPP_SRCS += \
../microsim/trigger/MSBusStop.cpp \
../microsim/trigger/MSCalibrator.cpp \
../microsim/trigger/MSEmitter.cpp \
../microsim/trigger/MSLaneSpeedTrigger.cpp \
../microsim/trigger/MSTriggeredReader.cpp \
../microsim/trigger/MSTriggeredRerouter.cpp \
../microsim/trigger/MSTriggeredXMLReader.cpp 

OBJS += \
./microsim/trigger/MSBusStop.o \
./microsim/trigger/MSCalibrator.o \
./microsim/trigger/MSEmitter.o \
./microsim/trigger/MSLaneSpeedTrigger.o \
./microsim/trigger/MSTriggeredReader.o \
./microsim/trigger/MSTriggeredRerouter.o \
./microsim/trigger/MSTriggeredXMLReader.o 

CPP_DEPS += \
./microsim/trigger/MSBusStop.d \
./microsim/trigger/MSCalibrator.d \
./microsim/trigger/MSEmitter.d \
./microsim/trigger/MSLaneSpeedTrigger.d \
./microsim/trigger/MSTriggeredReader.d \
./microsim/trigger/MSTriggeredRerouter.d \
./microsim/trigger/MSTriggeredXMLReader.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/trigger/%.o: ../microsim/trigger/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/traffic_lights/MSActuatedTrafficLightLogic.o \
../microsim/traffic_lights/MSAgentbasedTrafficLightLogic.o \
../microsim/traffic_lights/MSOffTrafficLightLogic.o \
../microsim/traffic_lights/MSSimpleTrafficLightLogic.o \
../microsim/traffic_lights/MSTLLogicControl.o \
../microsim/traffic_lights/MSTrafficLightLogic.o 

CPP_SRCS += \
../microsim/traffic_lights/MSActuatedTrafficLightLogic.cpp \
../microsim/traffic_lights/MSAgentbasedTrafficLightLogic.cpp \
../microsim/traffic_lights/MSOffTrafficLightLogic.cpp \
../microsim/traffic_lights/MSSimpleTrafficLightLogic.cpp \
../microsim/traffic_lights/MSTLLogicControl.cpp \
../microsim/traffic_lights/MSTrafficLightLogic.cpp 

OBJS += \
./microsim/traffic_lights/MSActuatedTrafficLightLogic.o \
./microsim/traffic_lights/MSAgentbasedTrafficLightLogic.o \
./microsim/traffic_lights/MSOffTrafficLightLogic.o \
./microsim/traffic_lights/MSSimpleTrafficLightLogic.o \
./microsim/traffic_lights/MSTLLogicControl.o \
./microsim/traffic_lights/MSTrafficLightLogic.o 

CPP_DEPS += \
./microsim/traffic_lights/MSActuatedTrafficLightLogic.d \
./microsim/traffic_lights/MSAgentbasedTrafficLightLogic.d \
./microsim/traffic_lights/MSOffTrafficLightLogic.d \
./microsim/traffic_lights/MSSimpleTrafficLightLogic.d \
./microsim/traffic_lights/MSTLLogicControl.d \
./microsim/traffic_lights/MSTrafficLightLogic.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/traffic_lights/%.o: ../microsim/traffic_lights/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



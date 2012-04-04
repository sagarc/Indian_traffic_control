################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/gui/tracker/GUIParameterTracker.o \
../utils/gui/tracker/TrackerValueDesc.o 

CPP_SRCS += \
../utils/gui/tracker/GUIParameterTracker.cpp \
../utils/gui/tracker/TrackerValueDesc.cpp 

OBJS += \
./utils/gui/tracker/GUIParameterTracker.o \
./utils/gui/tracker/TrackerValueDesc.o 

CPP_DEPS += \
./utils/gui/tracker/GUIParameterTracker.d \
./utils/gui/tracker/TrackerValueDesc.d 


# Each subdirectory must supply rules for building sources it contributes
utils/gui/tracker/%.o: ../utils/gui/tracker/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



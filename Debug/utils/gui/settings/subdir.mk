################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/gui/settings/GUICompleteSchemeStorage.o \
../utils/gui/settings/GUISettingsHandler.o \
../utils/gui/settings/GUIVisualizationSettings.o 

CPP_SRCS += \
../utils/gui/settings/GUICompleteSchemeStorage.cpp \
../utils/gui/settings/GUISettingsHandler.cpp \
../utils/gui/settings/GUIVisualizationSettings.cpp 

OBJS += \
./utils/gui/settings/GUICompleteSchemeStorage.o \
./utils/gui/settings/GUISettingsHandler.o \
./utils/gui/settings/GUIVisualizationSettings.o 

CPP_DEPS += \
./utils/gui/settings/GUICompleteSchemeStorage.d \
./utils/gui/settings/GUISettingsHandler.d \
./utils/gui/settings/GUIVisualizationSettings.d 


# Each subdirectory must supply rules for building sources it contributes
utils/gui/settings/%.o: ../utils/gui/settings/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



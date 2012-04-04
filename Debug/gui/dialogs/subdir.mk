################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gui/dialogs/GUIDialog_AboutSUMO.o \
../gui/dialogs/GUIDialog_AppSettings.o \
../gui/dialogs/GUIDialog_Breakpoints.o \
../gui/dialogs/GUIDialog_GLObjChooser.o 

CPP_SRCS += \
../gui/dialogs/GUIDialog_AboutSUMO.cpp \
../gui/dialogs/GUIDialog_AppSettings.cpp \
../gui/dialogs/GUIDialog_Breakpoints.cpp \
../gui/dialogs/GUIDialog_GLObjChooser.cpp 

OBJS += \
./gui/dialogs/GUIDialog_AboutSUMO.o \
./gui/dialogs/GUIDialog_AppSettings.o \
./gui/dialogs/GUIDialog_Breakpoints.o \
./gui/dialogs/GUIDialog_GLObjChooser.o 

CPP_DEPS += \
./gui/dialogs/GUIDialog_AboutSUMO.d \
./gui/dialogs/GUIDialog_AppSettings.d \
./gui/dialogs/GUIDialog_Breakpoints.d \
./gui/dialogs/GUIDialog_GLObjChooser.d 


# Each subdirectory must supply rules for building sources it contributes
gui/dialogs/%.o: ../gui/dialogs/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



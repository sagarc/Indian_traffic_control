################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../gui/GUIApplicationWindow.o \
../gui/GUIGlobals.o \
../gui/GUILoadThread.o \
../gui/GUIManipulator.o \
../gui/GUIRunThread.o \
../gui/GUISUMOViewParent.o \
../gui/GUITLLogicPhasesTrackerWindow.o \
../gui/GUIViewTraffic.o 

CPP_SRCS += \
../gui/GUIApplicationWindow.cpp \
../gui/GUIGlobals.cpp \
../gui/GUILoadThread.cpp \
../gui/GUIManipulator.cpp \
../gui/GUIRunThread.cpp \
../gui/GUISUMOViewParent.cpp \
../gui/GUITLLogicPhasesTrackerWindow.cpp \
../gui/GUIViewTraffic.cpp 

OBJS += \
./gui/GUIApplicationWindow.o \
./gui/GUIGlobals.o \
./gui/GUILoadThread.o \
./gui/GUIManipulator.o \
./gui/GUIRunThread.o \
./gui/GUISUMOViewParent.o \
./gui/GUITLLogicPhasesTrackerWindow.o \
./gui/GUIViewTraffic.o 

CPP_DEPS += \
./gui/GUIApplicationWindow.d \
./gui/GUIGlobals.d \
./gui/GUILoadThread.d \
./gui/GUIManipulator.d \
./gui/GUIRunThread.d \
./gui/GUISUMOViewParent.d \
./gui/GUITLLogicPhasesTrackerWindow.d \
./gui/GUIViewTraffic.d 


# Each subdirectory must supply rules for building sources it contributes
gui/%.o: ../gui/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



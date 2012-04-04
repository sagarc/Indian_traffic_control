################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/gui/windows/GUIAppGlobals.o \
../utils/gui/windows/GUIDanielPerspectiveChanger.o \
../utils/gui/windows/GUIDialog_EditViewport.o \
../utils/gui/windows/GUIDialog_ViewSettings.o \
../utils/gui/windows/GUIGlChildWindow.o \
../utils/gui/windows/GUIMainWindow.o \
../utils/gui/windows/GUIPerspectiveChanger.o \
../utils/gui/windows/GUISUMOAbstractView.o 

CPP_SRCS += \
../utils/gui/windows/GUIAppGlobals.cpp \
../utils/gui/windows/GUIDanielPerspectiveChanger.cpp \
../utils/gui/windows/GUIDialog_EditViewport.cpp \
../utils/gui/windows/GUIDialog_ViewSettings.cpp \
../utils/gui/windows/GUIGlChildWindow.cpp \
../utils/gui/windows/GUIMainWindow.cpp \
../utils/gui/windows/GUIPerspectiveChanger.cpp \
../utils/gui/windows/GUISUMOAbstractView.cpp 

OBJS += \
./utils/gui/windows/GUIAppGlobals.o \
./utils/gui/windows/GUIDanielPerspectiveChanger.o \
./utils/gui/windows/GUIDialog_EditViewport.o \
./utils/gui/windows/GUIDialog_ViewSettings.o \
./utils/gui/windows/GUIGlChildWindow.o \
./utils/gui/windows/GUIMainWindow.o \
./utils/gui/windows/GUIPerspectiveChanger.o \
./utils/gui/windows/GUISUMOAbstractView.o 

CPP_DEPS += \
./utils/gui/windows/GUIAppGlobals.d \
./utils/gui/windows/GUIDanielPerspectiveChanger.d \
./utils/gui/windows/GUIDialog_EditViewport.d \
./utils/gui/windows/GUIDialog_ViewSettings.d \
./utils/gui/windows/GUIGlChildWindow.d \
./utils/gui/windows/GUIMainWindow.d \
./utils/gui/windows/GUIPerspectiveChanger.d \
./utils/gui/windows/GUISUMOAbstractView.d 


# Each subdirectory must supply rules for building sources it contributes
utils/gui/windows/%.o: ../utils/gui/windows/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



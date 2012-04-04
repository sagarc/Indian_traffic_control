################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/gui/globjects/GUIGLObjectPopupMenu.o \
../utils/gui/globjects/GUIGLObjectToolTip.o \
../utils/gui/globjects/GUIGlObject.o \
../utils/gui/globjects/GUIGlObjectStorage.o \
../utils/gui/globjects/GUIGlObject_AbstractAdd.o \
../utils/gui/globjects/GUIPointOfInterest.o \
../utils/gui/globjects/GUIPolygon2D.o 

CPP_SRCS += \
../utils/gui/globjects/GUIGLObjectPopupMenu.cpp \
../utils/gui/globjects/GUIGLObjectToolTip.cpp \
../utils/gui/globjects/GUIGlObject.cpp \
../utils/gui/globjects/GUIGlObjectStorage.cpp \
../utils/gui/globjects/GUIGlObject_AbstractAdd.cpp \
../utils/gui/globjects/GUIPointOfInterest.cpp \
../utils/gui/globjects/GUIPolygon2D.cpp 

OBJS += \
./utils/gui/globjects/GUIGLObjectPopupMenu.o \
./utils/gui/globjects/GUIGLObjectToolTip.o \
./utils/gui/globjects/GUIGlObject.o \
./utils/gui/globjects/GUIGlObjectStorage.o \
./utils/gui/globjects/GUIGlObject_AbstractAdd.o \
./utils/gui/globjects/GUIPointOfInterest.o \
./utils/gui/globjects/GUIPolygon2D.o 

CPP_DEPS += \
./utils/gui/globjects/GUIGLObjectPopupMenu.d \
./utils/gui/globjects/GUIGLObjectToolTip.d \
./utils/gui/globjects/GUIGlObject.d \
./utils/gui/globjects/GUIGlObjectStorage.d \
./utils/gui/globjects/GUIGlObject_AbstractAdd.d \
./utils/gui/globjects/GUIPointOfInterest.d \
./utils/gui/globjects/GUIPolygon2D.d 


# Each subdirectory must supply rules for building sources it contributes
utils/gui/globjects/%.o: ../utils/gui/globjects/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



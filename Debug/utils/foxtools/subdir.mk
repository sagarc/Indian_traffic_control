################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/foxtools/FXBaseObject.o \
../utils/foxtools/FXLCDLabel.o \
../utils/foxtools/FXLinkLabel.o \
../utils/foxtools/FXRealSpinDial.o \
../utils/foxtools/FXSevenSegment.o \
../utils/foxtools/FXSingleEventThread.o \
../utils/foxtools/FXThreadEvent.o \
../utils/foxtools/MFXAddEditTypedTable.o \
../utils/foxtools/MFXCheckableButton.o \
../utils/foxtools/MFXEditableTable.o \
../utils/foxtools/MFXEventQue.o \
../utils/foxtools/MFXImageHelper.o \
../utils/foxtools/MFXMenuHeader.o \
../utils/foxtools/MFXMutex.o \
../utils/foxtools/MFXUtils.o 

CPP_SRCS += \
../utils/foxtools/FXBaseObject.cpp \
../utils/foxtools/FXLCDLabel.cpp \
../utils/foxtools/FXLinkLabel.cpp \
../utils/foxtools/FXRealSpinDial.cpp \
../utils/foxtools/FXSevenSegment.cpp \
../utils/foxtools/FXSingleEventThread.cpp \
../utils/foxtools/FXThreadEvent.cpp \
../utils/foxtools/MFXAddEditTypedTable.cpp \
../utils/foxtools/MFXCheckableButton.cpp \
../utils/foxtools/MFXEditableTable.cpp \
../utils/foxtools/MFXEventQue.cpp \
../utils/foxtools/MFXImageHelper.cpp \
../utils/foxtools/MFXMenuHeader.cpp \
../utils/foxtools/MFXMutex.cpp \
../utils/foxtools/MFXUtils.cpp 

OBJS += \
./utils/foxtools/FXBaseObject.o \
./utils/foxtools/FXLCDLabel.o \
./utils/foxtools/FXLinkLabel.o \
./utils/foxtools/FXRealSpinDial.o \
./utils/foxtools/FXSevenSegment.o \
./utils/foxtools/FXSingleEventThread.o \
./utils/foxtools/FXThreadEvent.o \
./utils/foxtools/MFXAddEditTypedTable.o \
./utils/foxtools/MFXCheckableButton.o \
./utils/foxtools/MFXEditableTable.o \
./utils/foxtools/MFXEventQue.o \
./utils/foxtools/MFXImageHelper.o \
./utils/foxtools/MFXMenuHeader.o \
./utils/foxtools/MFXMutex.o \
./utils/foxtools/MFXUtils.o 

CPP_DEPS += \
./utils/foxtools/FXBaseObject.d \
./utils/foxtools/FXLCDLabel.d \
./utils/foxtools/FXLinkLabel.d \
./utils/foxtools/FXRealSpinDial.d \
./utils/foxtools/FXSevenSegment.d \
./utils/foxtools/FXSingleEventThread.d \
./utils/foxtools/FXThreadEvent.d \
./utils/foxtools/MFXAddEditTypedTable.d \
./utils/foxtools/MFXCheckableButton.d \
./utils/foxtools/MFXEditableTable.d \
./utils/foxtools/MFXEventQue.d \
./utils/foxtools/MFXImageHelper.d \
./utils/foxtools/MFXMenuHeader.d \
./utils/foxtools/MFXMutex.d \
./utils/foxtools/MFXUtils.d 


# Each subdirectory must supply rules for building sources it contributes
utils/foxtools/%.o: ../utils/foxtools/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/gui/images/GUIIconSubSys.o \
../utils/gui/images/GUIImageGlobals.o \
../utils/gui/images/GUITexturesHelper.o 

CPP_SRCS += \
../utils/gui/images/GUIIconSubSys.cpp \
../utils/gui/images/GUIImageGlobals.cpp \
../utils/gui/images/GUITexturesHelper.cpp \
../utils/gui/images/flag.cpp \
../utils/gui/images/flag_minus.cpp \
../utils/gui/images/flag_plus.cpp \
../utils/gui/images/manip.cpp 

OBJS += \
./utils/gui/images/GUIIconSubSys.o \
./utils/gui/images/GUIImageGlobals.o \
./utils/gui/images/GUITexturesHelper.o \
./utils/gui/images/flag.o \
./utils/gui/images/flag_minus.o \
./utils/gui/images/flag_plus.o \
./utils/gui/images/manip.o 

CPP_DEPS += \
./utils/gui/images/GUIIconSubSys.d \
./utils/gui/images/GUIImageGlobals.d \
./utils/gui/images/GUITexturesHelper.d \
./utils/gui/images/flag.d \
./utils/gui/images/flag_minus.d \
./utils/gui/images/flag_plus.d \
./utils/gui/images/manip.d 


# Each subdirectory must supply rules for building sources it contributes
utils/gui/images/%.o: ../utils/gui/images/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



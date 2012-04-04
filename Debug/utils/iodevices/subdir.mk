################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/iodevices/BinaryInputDevice.o \
../utils/iodevices/OutputDevice.o \
../utils/iodevices/OutputDevice_COUT.o \
../utils/iodevices/OutputDevice_File.o \
../utils/iodevices/OutputDevice_Network.o \
../utils/iodevices/OutputDevice_String.o 

CPP_SRCS += \
../utils/iodevices/BinaryInputDevice.cpp \
../utils/iodevices/OutputDevice.cpp \
../utils/iodevices/OutputDevice_COUT.cpp \
../utils/iodevices/OutputDevice_File.cpp \
../utils/iodevices/OutputDevice_Network.cpp \
../utils/iodevices/OutputDevice_String.cpp 

OBJS += \
./utils/iodevices/BinaryInputDevice.o \
./utils/iodevices/OutputDevice.o \
./utils/iodevices/OutputDevice_COUT.o \
./utils/iodevices/OutputDevice_File.o \
./utils/iodevices/OutputDevice_Network.o \
./utils/iodevices/OutputDevice_String.o 

CPP_DEPS += \
./utils/iodevices/BinaryInputDevice.d \
./utils/iodevices/OutputDevice.d \
./utils/iodevices/OutputDevice_COUT.d \
./utils/iodevices/OutputDevice_File.d \
./utils/iodevices/OutputDevice_Network.d \
./utils/iodevices/OutputDevice_String.d 


# Each subdirectory must supply rules for building sources it contributes
utils/iodevices/%.o: ../utils/iodevices/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



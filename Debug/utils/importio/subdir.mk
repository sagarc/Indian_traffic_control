################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/importio/LineReader.o \
../utils/importio/NamedColumnsParser.o 

CPP_SRCS += \
../utils/importio/LineReader.cpp \
../utils/importio/NamedColumnsParser.cpp 

OBJS += \
./utils/importio/LineReader.o \
./utils/importio/NamedColumnsParser.o 

CPP_DEPS += \
./utils/importio/LineReader.d \
./utils/importio/NamedColumnsParser.d 


# Each subdirectory must supply rules for building sources it contributes
utils/importio/%.o: ../utils/importio/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



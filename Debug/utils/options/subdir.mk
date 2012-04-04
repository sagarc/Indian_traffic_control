################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/options/Option.o \
../utils/options/OptionsCont.o \
../utils/options/OptionsIO.o \
../utils/options/OptionsLoader.o \
../utils/options/OptionsParser.o 

CPP_SRCS += \
../utils/options/Option.cpp \
../utils/options/OptionsCont.cpp \
../utils/options/OptionsIO.cpp \
../utils/options/OptionsLoader.cpp \
../utils/options/OptionsParser.cpp 

OBJS += \
./utils/options/Option.o \
./utils/options/OptionsCont.o \
./utils/options/OptionsIO.o \
./utils/options/OptionsLoader.o \
./utils/options/OptionsParser.o 

CPP_DEPS += \
./utils/options/Option.d \
./utils/options/OptionsCont.d \
./utils/options/OptionsIO.d \
./utils/options/OptionsLoader.d \
./utils/options/OptionsParser.d 


# Each subdirectory must supply rules for building sources it contributes
utils/options/%.o: ../utils/options/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



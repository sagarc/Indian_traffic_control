################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../foreign/tcpip/socket.o \
../foreign/tcpip/storage.o 

CPP_SRCS += \
../foreign/tcpip/socket.cpp \
../foreign/tcpip/storage.cpp 

OBJS += \
./foreign/tcpip/socket.o \
./foreign/tcpip/storage.o 

CPP_DEPS += \
./foreign/tcpip/socket.d \
./foreign/tcpip/storage.d 


# Each subdirectory must supply rules for building sources it contributes
foreign/tcpip/%.o: ../foreign/tcpip/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



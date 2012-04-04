################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/actions/Command_SaveTLCoupledDet.o \
../microsim/actions/Command_SaveTLCoupledLaneDet.o \
../microsim/actions/Command_SaveTLSState.o \
../microsim/actions/Command_SaveTLSSwitchStates.o \
../microsim/actions/Command_SaveTLSSwitches.o 

CPP_SRCS += \
../microsim/actions/Command_SaveTLCoupledDet.cpp \
../microsim/actions/Command_SaveTLCoupledLaneDet.cpp \
../microsim/actions/Command_SaveTLSState.cpp \
../microsim/actions/Command_SaveTLSSwitchStates.cpp \
../microsim/actions/Command_SaveTLSSwitches.cpp 

OBJS += \
./microsim/actions/Command_SaveTLCoupledDet.o \
./microsim/actions/Command_SaveTLCoupledLaneDet.o \
./microsim/actions/Command_SaveTLSState.o \
./microsim/actions/Command_SaveTLSSwitchStates.o \
./microsim/actions/Command_SaveTLSSwitches.o 

CPP_DEPS += \
./microsim/actions/Command_SaveTLCoupledDet.d \
./microsim/actions/Command_SaveTLCoupledLaneDet.d \
./microsim/actions/Command_SaveTLSState.d \
./microsim/actions/Command_SaveTLSSwitchStates.d \
./microsim/actions/Command_SaveTLSSwitches.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/actions/%.o: ../microsim/actions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



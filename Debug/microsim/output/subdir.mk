################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/output/MSDetectorControl.o \
../microsim/output/MSE2Collector.o \
../microsim/output/MSE3Collector.o \
../microsim/output/MSInductLoop.o \
../microsim/output/MSMeanData.o \
../microsim/output/MSMeanData_HBEFA.o \
../microsim/output/MSMeanData_Harmonoise.o \
../microsim/output/MSMeanData_Net.o \
../microsim/output/MSMsgInductLoop.o \
../microsim/output/MSRouteProbe.o \
../microsim/output/MSVTypeProbe.o \
../microsim/output/MSXMLRawOut.o \
../microsim/output/MS_E2_ZS_CollectorOverLanes.o 

CPP_SRCS += \
../microsim/output/MSDetectorControl.cpp \
../microsim/output/MSE2Collector.cpp \
../microsim/output/MSE3Collector.cpp \
../microsim/output/MSInductLoop.cpp \
../microsim/output/MSMeanData.cpp \
../microsim/output/MSMeanData_HBEFA.cpp \
../microsim/output/MSMeanData_Harmonoise.cpp \
../microsim/output/MSMeanData_Net.cpp \
../microsim/output/MSMsgInductLoop.cpp \
../microsim/output/MSRouteProbe.cpp \
../microsim/output/MSVTypeProbe.cpp \
../microsim/output/MSXMLRawOut.cpp \
../microsim/output/MS_E2_ZS_CollectorOverLanes.cpp 

OBJS += \
./microsim/output/MSDetectorControl.o \
./microsim/output/MSE2Collector.o \
./microsim/output/MSE3Collector.o \
./microsim/output/MSInductLoop.o \
./microsim/output/MSMeanData.o \
./microsim/output/MSMeanData_HBEFA.o \
./microsim/output/MSMeanData_Harmonoise.o \
./microsim/output/MSMeanData_Net.o \
./microsim/output/MSMsgInductLoop.o \
./microsim/output/MSRouteProbe.o \
./microsim/output/MSVTypeProbe.o \
./microsim/output/MSXMLRawOut.o \
./microsim/output/MS_E2_ZS_CollectorOverLanes.o 

CPP_DEPS += \
./microsim/output/MSDetectorControl.d \
./microsim/output/MSE2Collector.d \
./microsim/output/MSE3Collector.d \
./microsim/output/MSInductLoop.d \
./microsim/output/MSMeanData.d \
./microsim/output/MSMeanData_HBEFA.d \
./microsim/output/MSMeanData_Harmonoise.d \
./microsim/output/MSMeanData_Net.d \
./microsim/output/MSMsgInductLoop.d \
./microsim/output/MSRouteProbe.d \
./microsim/output/MSVTypeProbe.d \
./microsim/output/MSXMLRawOut.d \
./microsim/output/MS_E2_ZS_CollectorOverLanes.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/output/%.o: ../microsim/output/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../netload/NLBuilder.o \
../netload/NLDetectorBuilder.o \
../netload/NLDiscreteEventBuilder.o \
../netload/NLEdgeControlBuilder.o \
../netload/NLGeomShapeBuilder.o \
../netload/NLHandler.o \
../netload/NLJunctionControlBuilder.o \
../netload/NLSucceedingLaneBuilder.o \
../netload/NLTriggerBuilder.o 

CPP_SRCS += \
../netload/NLBuilder.cpp \
../netload/NLDetectorBuilder.cpp \
../netload/NLDiscreteEventBuilder.cpp \
../netload/NLEdgeControlBuilder.cpp \
../netload/NLGeomShapeBuilder.cpp \
../netload/NLHandler.cpp \
../netload/NLJunctionControlBuilder.cpp \
../netload/NLSucceedingLaneBuilder.cpp \
../netload/NLTriggerBuilder.cpp 

OBJS += \
./netload/NLBuilder.o \
./netload/NLDetectorBuilder.o \
./netload/NLDiscreteEventBuilder.o \
./netload/NLEdgeControlBuilder.o \
./netload/NLGeomShapeBuilder.o \
./netload/NLHandler.o \
./netload/NLJunctionControlBuilder.o \
./netload/NLSucceedingLaneBuilder.o \
./netload/NLTriggerBuilder.o 

CPP_DEPS += \
./netload/NLBuilder.d \
./netload/NLDetectorBuilder.d \
./netload/NLDiscreteEventBuilder.d \
./netload/NLEdgeControlBuilder.d \
./netload/NLGeomShapeBuilder.d \
./netload/NLHandler.d \
./netload/NLJunctionControlBuilder.d \
./netload/NLSucceedingLaneBuilder.d \
./netload/NLTriggerBuilder.d 


# Each subdirectory must supply rules for building sources it contributes
netload/%.o: ../netload/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



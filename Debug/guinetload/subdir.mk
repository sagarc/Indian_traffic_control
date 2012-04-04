################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../guinetload/GUIDetectorBuilder.o \
../guinetload/GUIEdgeControlBuilder.o \
../guinetload/GUIGeomShapeBuilder.o \
../guinetload/GUITriggerBuilder.o 

CPP_SRCS += \
../guinetload/GUIDetectorBuilder.cpp \
../guinetload/GUIEdgeControlBuilder.cpp \
../guinetload/GUIGeomShapeBuilder.cpp \
../guinetload/GUITriggerBuilder.cpp 

OBJS += \
./guinetload/GUIDetectorBuilder.o \
./guinetload/GUIEdgeControlBuilder.o \
./guinetload/GUIGeomShapeBuilder.o \
./guinetload/GUITriggerBuilder.o 

CPP_DEPS += \
./guinetload/GUIDetectorBuilder.d \
./guinetload/GUIEdgeControlBuilder.d \
./guinetload/GUIGeomShapeBuilder.d \
./guinetload/GUITriggerBuilder.d 


# Each subdirectory must supply rules for building sources it contributes
guinetload/%.o: ../guinetload/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/shapes/Polygon2D.o \
../utils/shapes/ShapeContainer.o 

CPP_SRCS += \
../utils/shapes/Polygon2D.cpp \
../utils/shapes/ShapeContainer.cpp 

OBJS += \
./utils/shapes/Polygon2D.o \
./utils/shapes/ShapeContainer.o 

CPP_DEPS += \
./utils/shapes/Polygon2D.d \
./utils/shapes/ShapeContainer.d 


# Each subdirectory must supply rules for building sources it contributes
utils/shapes/%.o: ../utils/shapes/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



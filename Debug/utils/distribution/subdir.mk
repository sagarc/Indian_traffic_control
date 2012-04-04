################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/distribution/DistributionCont.o \
../utils/distribution/Distribution_MeanDev.o \
../utils/distribution/Distribution_Points.o 

CPP_SRCS += \
../utils/distribution/DistributionCont.cpp \
../utils/distribution/Distribution_MeanDev.cpp \
../utils/distribution/Distribution_Points.cpp 

OBJS += \
./utils/distribution/DistributionCont.o \
./utils/distribution/Distribution_MeanDev.o \
./utils/distribution/Distribution_Points.o 

CPP_DEPS += \
./utils/distribution/DistributionCont.d \
./utils/distribution/Distribution_MeanDev.d \
./utils/distribution/Distribution_Points.d 


# Each subdirectory must supply rules for building sources it contributes
utils/distribution/%.o: ../utils/distribution/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



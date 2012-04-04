################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/cfmodels/MSCFModel_IDM.o \
../microsim/cfmodels/MSCFModel_IITBNN.o \
../microsim/cfmodels/MSCFModel_Kerner.o \
../microsim/cfmodels/MSCFModel_Krauss.o \
../microsim/cfmodels/MSCFModel_KraussOrig1.o \
../microsim/cfmodels/MSCFModel_PWag2009.o 

CPP_SRCS += \
../microsim/cfmodels/MSCFModel_IDM.cpp \
../microsim/cfmodels/MSCFModel_IITBNN.cpp \
../microsim/cfmodels/MSCFModel_Kerner.cpp \
../microsim/cfmodels/MSCFModel_Krauss.cpp \
../microsim/cfmodels/MSCFModel_KraussOrig1.cpp \
../microsim/cfmodels/MSCFModel_PWag2009.cpp 

OBJS += \
./microsim/cfmodels/MSCFModel_IDM.o \
./microsim/cfmodels/MSCFModel_IITBNN.o \
./microsim/cfmodels/MSCFModel_Kerner.o \
./microsim/cfmodels/MSCFModel_Krauss.o \
./microsim/cfmodels/MSCFModel_KraussOrig1.o \
./microsim/cfmodels/MSCFModel_PWag2009.o 

CPP_DEPS += \
./microsim/cfmodels/MSCFModel_IDM.d \
./microsim/cfmodels/MSCFModel_IITBNN.d \
./microsim/cfmodels/MSCFModel_Kerner.d \
./microsim/cfmodels/MSCFModel_Krauss.d \
./microsim/cfmodels/MSCFModel_KraussOrig1.d \
./microsim/cfmodels/MSCFModel_PWag2009.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/cfmodels/%.o: ../microsim/cfmodels/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



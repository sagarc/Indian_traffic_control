################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/xml/GenericSAXHandler.o \
../utils/xml/SAXWeightsHandler.o \
../utils/xml/SUMOSAXAttributes.o \
../utils/xml/SUMOSAXAttributesImpl_Xerces.o \
../utils/xml/SUMOSAXHandler.o \
../utils/xml/SUMOVehicleParserHelper.o \
../utils/xml/SUMOXMLDefinitions.o \
../utils/xml/XMLSubSys.o 

CPP_SRCS += \
../utils/xml/GenericSAXHandler.cpp \
../utils/xml/SAXWeightsHandler.cpp \
../utils/xml/SUMOSAXAttributes.cpp \
../utils/xml/SUMOSAXAttributesImpl_Xerces.cpp \
../utils/xml/SUMOSAXHandler.cpp \
../utils/xml/SUMOVehicleParserHelper.cpp \
../utils/xml/SUMOXMLDefinitions.cpp \
../utils/xml/XMLSubSys.cpp 

OBJS += \
./utils/xml/GenericSAXHandler.o \
./utils/xml/SAXWeightsHandler.o \
./utils/xml/SUMOSAXAttributes.o \
./utils/xml/SUMOSAXAttributesImpl_Xerces.o \
./utils/xml/SUMOSAXHandler.o \
./utils/xml/SUMOVehicleParserHelper.o \
./utils/xml/SUMOXMLDefinitions.o \
./utils/xml/XMLSubSys.o 

CPP_DEPS += \
./utils/xml/GenericSAXHandler.d \
./utils/xml/SAXWeightsHandler.d \
./utils/xml/SUMOSAXAttributes.d \
./utils/xml/SUMOSAXAttributesImpl_Xerces.d \
./utils/xml/SUMOSAXHandler.d \
./utils/xml/SUMOVehicleParserHelper.d \
./utils/xml/SUMOXMLDefinitions.d \
./utils/xml/XMLSubSys.d 


# Each subdirectory must supply rules for building sources it contributes
utils/xml/%.o: ../utils/xml/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



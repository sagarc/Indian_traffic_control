################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../microsim/MSCFModel.o \
../microsim/MSCORN.o \
../microsim/MSEdge.o \
../microsim/MSEdgeControl.o \
../microsim/MSEdgeWeightsStorage.o \
../microsim/MSEmitControl.o \
../microsim/MSEventControl.o \
../microsim/MSFrame.o \
../microsim/MSGlobals.o \
../microsim/MSInternalJunction.o \
../microsim/MSInternalLane.o \
../microsim/MSJunction.o \
../microsim/MSJunctionControl.o \
../microsim/MSJunctionLogic.o \
../microsim/MSLCM_DK2004.o \
../microsim/MSLane.o \
../microsim/MSLink.o \
../microsim/MSLinkCont.o \
../microsim/MSLogicJunction.o \
../microsim/MSMessageEmitter.o \
../microsim/MSMoveReminder.o \
../microsim/MSNet.o \
../microsim/MSNoLogicJunction.o \
../microsim/MSPerson.o \
../microsim/MSPersonControl.o \
../microsim/MSRightOfWayJunction.o \
../microsim/MSRoute.o \
../microsim/MSRouteHandler.o \
../microsim/MSRouteLoader.o \
../microsim/MSRouteLoaderControl.o \
../microsim/MSStrip.o \
../microsim/MSStripChanger.o \
../microsim/MSVehicle.o \
../microsim/MSVehicleContainer.o \
../microsim/MSVehicleControl.o \
../microsim/MSVehicleTransfer.o \
../microsim/MSVehicleType.o 

CPP_SRCS += \
../microsim/MSCFModel.cpp \
../microsim/MSCORN.cpp \
../microsim/MSEdge.cpp \
../microsim/MSEdgeControl.cpp \
../microsim/MSEdgeWeightsStorage.cpp \
../microsim/MSEmitControl.cpp \
../microsim/MSEventControl.cpp \
../microsim/MSFrame.cpp \
../microsim/MSGlobals.cpp \
../microsim/MSInternalJunction.cpp \
../microsim/MSInternalLane.cpp \
../microsim/MSJunction.cpp \
../microsim/MSJunctionControl.cpp \
../microsim/MSJunctionLogic.cpp \
../microsim/MSLCM_DK2004.cpp \
../microsim/MSLane.cpp \
../microsim/MSLink.cpp \
../microsim/MSLinkCont.cpp \
../microsim/MSLogicJunction.cpp \
../microsim/MSMessageEmitter.cpp \
../microsim/MSMoveReminder.cpp \
../microsim/MSNet.cpp \
../microsim/MSNoLogicJunction.cpp \
../microsim/MSPerson.cpp \
../microsim/MSPersonControl.cpp \
../microsim/MSRightOfWayJunction.cpp \
../microsim/MSRoute.cpp \
../microsim/MSRouteHandler.cpp \
../microsim/MSRouteLoader.cpp \
../microsim/MSRouteLoaderControl.cpp \
../microsim/MSStrip.cpp \
../microsim/MSStripChanger.cpp \
../microsim/MSVehicle.cpp \
../microsim/MSVehicleContainer.cpp \
../microsim/MSVehicleControl.cpp \
../microsim/MSVehicleTransfer.cpp \
../microsim/MSVehicleType.cpp 

OBJS += \
./microsim/MSCFModel.o \
./microsim/MSCORN.o \
./microsim/MSEdge.o \
./microsim/MSEdgeControl.o \
./microsim/MSEdgeWeightsStorage.o \
./microsim/MSEmitControl.o \
./microsim/MSEventControl.o \
./microsim/MSFrame.o \
./microsim/MSGlobals.o \
./microsim/MSInternalJunction.o \
./microsim/MSInternalLane.o \
./microsim/MSJunction.o \
./microsim/MSJunctionControl.o \
./microsim/MSJunctionLogic.o \
./microsim/MSLCM_DK2004.o \
./microsim/MSLane.o \
./microsim/MSLink.o \
./microsim/MSLinkCont.o \
./microsim/MSLogicJunction.o \
./microsim/MSMessageEmitter.o \
./microsim/MSMoveReminder.o \
./microsim/MSNet.o \
./microsim/MSNoLogicJunction.o \
./microsim/MSPerson.o \
./microsim/MSPersonControl.o \
./microsim/MSRightOfWayJunction.o \
./microsim/MSRoute.o \
./microsim/MSRouteHandler.o \
./microsim/MSRouteLoader.o \
./microsim/MSRouteLoaderControl.o \
./microsim/MSStrip.o \
./microsim/MSStripChanger.o \
./microsim/MSVehicle.o \
./microsim/MSVehicleContainer.o \
./microsim/MSVehicleControl.o \
./microsim/MSVehicleTransfer.o \
./microsim/MSVehicleType.o 

CPP_DEPS += \
./microsim/MSCFModel.d \
./microsim/MSCORN.d \
./microsim/MSEdge.d \
./microsim/MSEdgeControl.d \
./microsim/MSEdgeWeightsStorage.d \
./microsim/MSEmitControl.d \
./microsim/MSEventControl.d \
./microsim/MSFrame.d \
./microsim/MSGlobals.d \
./microsim/MSInternalJunction.d \
./microsim/MSInternalLane.d \
./microsim/MSJunction.d \
./microsim/MSJunctionControl.d \
./microsim/MSJunctionLogic.d \
./microsim/MSLCM_DK2004.d \
./microsim/MSLane.d \
./microsim/MSLink.d \
./microsim/MSLinkCont.d \
./microsim/MSLogicJunction.d \
./microsim/MSMessageEmitter.d \
./microsim/MSMoveReminder.d \
./microsim/MSNet.d \
./microsim/MSNoLogicJunction.d \
./microsim/MSPerson.d \
./microsim/MSPersonControl.d \
./microsim/MSRightOfWayJunction.d \
./microsim/MSRoute.d \
./microsim/MSRouteHandler.d \
./microsim/MSRouteLoader.d \
./microsim/MSRouteLoaderControl.d \
./microsim/MSStrip.d \
./microsim/MSStripChanger.d \
./microsim/MSVehicle.d \
./microsim/MSVehicleContainer.d \
./microsim/MSVehicleControl.d \
./microsim/MSVehicleTransfer.d \
./microsim/MSVehicleType.d 


# Each subdirectory must supply rules for building sources it contributes
microsim/%.o: ../microsim/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



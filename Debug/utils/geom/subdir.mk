################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../utils/geom/Boundary.o \
../utils/geom/Bresenham.o \
../utils/geom/GeoConvHelper.o \
../utils/geom/GeomConvHelper.o \
../utils/geom/GeomHelper.o \
../utils/geom/Helper_ConvexHull.o \
../utils/geom/Line2D.o \
../utils/geom/Position2DVector.o \
../utils/geom/bezier.o 

CPP_SRCS += \
../utils/geom/Boundary.cpp \
../utils/geom/Bresenham.cpp \
../utils/geom/GeoConvHelper.cpp \
../utils/geom/GeomConvHelper.cpp \
../utils/geom/GeomHelper.cpp \
../utils/geom/Helper_ConvexHull.cpp \
../utils/geom/Line2D.cpp \
../utils/geom/Position2DVector.cpp \
../utils/geom/bezier.cpp 

OBJS += \
./utils/geom/Boundary.o \
./utils/geom/Bresenham.o \
./utils/geom/GeoConvHelper.o \
./utils/geom/GeomConvHelper.o \
./utils/geom/GeomHelper.o \
./utils/geom/Helper_ConvexHull.o \
./utils/geom/Line2D.o \
./utils/geom/Position2DVector.o \
./utils/geom/bezier.o 

CPP_DEPS += \
./utils/geom/Boundary.d \
./utils/geom/Bresenham.d \
./utils/geom/GeoConvHelper.d \
./utils/geom/GeomConvHelper.d \
./utils/geom/GeomHelper.d \
./utils/geom/Helper_ConvexHull.d \
./utils/geom/Line2D.d \
./utils/geom/Position2DVector.d \
./utils/geom/bezier.d 


# Each subdirectory must supply rules for building sources it contributes
utils/geom/%.o: ../utils/geom/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



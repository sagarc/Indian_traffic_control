################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../foreign/nvwa/bool_array.o \
../foreign/nvwa/debug_new.o \
../foreign/nvwa/mem_pool_base.o \
../foreign/nvwa/static_mem_pool.o 

CPP_SRCS += \
../foreign/nvwa/bool_array.cpp \
../foreign/nvwa/debug_new.cpp \
../foreign/nvwa/mem_pool_base.cpp \
../foreign/nvwa/static_mem_pool.cpp 

OBJS += \
./foreign/nvwa/bool_array.o \
./foreign/nvwa/debug_new.o \
./foreign/nvwa/mem_pool_base.o \
./foreign/nvwa/static_mem_pool.o 

CPP_DEPS += \
./foreign/nvwa/bool_array.d \
./foreign/nvwa/debug_new.d \
./foreign/nvwa/mem_pool_base.d \
./foreign/nvwa/static_mem_pool.d 


# Each subdirectory must supply rules for building sources it contributes
foreign/nvwa/%.o: ../foreign/nvwa/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/sagar/Eclipseworkspace/iSUMO_GUI" -I/usr/include/xercesc -I/usr/include/fox-1.6 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



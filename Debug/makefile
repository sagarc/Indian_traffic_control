################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utils/xml/subdir.mk
-include utils/shapes/subdir.mk
-include utils/options/subdir.mk
-include utils/iodevices/subdir.mk
-include utils/importio/subdir.mk
-include utils/gui/windows/subdir.mk
-include utils/gui/tracker/subdir.mk
-include utils/gui/settings/subdir.mk
-include utils/gui/images/subdir.mk
-include utils/gui/globjects/subdir.mk
-include utils/gui/div/subdir.mk
-include utils/geom/subdir.mk
-include utils/foxtools/subdir.mk
-include utils/distribution/subdir.mk
-include utils/common/subdir.mk
-include netload/subdir.mk
-include microsim/trigger/subdir.mk
-include microsim/traffic_lights/subdir.mk
-include microsim/output/subdir.mk
-include microsim/devices/subdir.mk
-include microsim/cfmodels/subdir.mk
-include microsim/actions/subdir.mk
-include microsim/subdir.mk
-include guisim/subdir.mk
-include guinetload/subdir.mk
-include gui/dialogs/subdir.mk
-include gui/subdir.mk
-include foreign/tcpip/subdir.mk
-include foreign/polyfonts/subdir.mk
-include foreign/nvwa/subdir.mk
-include foreign/eulerspiral/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: iSUMO_GUI

# Tool invocations
iSUMO_GUI: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/lib -o "iSUMO_GUI" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) iSUMO_GUI
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

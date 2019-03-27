################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommandLine.cpp \
../MRShell.cpp \
../MRShellDriver.cpp \
../Path.cpp \
../Prompt.cpp 

OBJS += \
./CommandLine.o \
./MRShell.o \
./MRShellDriver.o \
./Path.o \
./Prompt.o 

CPP_DEPS += \
./CommandLine.d \
./MRShell.d \
./MRShellDriver.d \
./Path.d \
./Prompt.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../rbf/pfm.cc \
../rbf/rbfm.cc \
../rbf/rbftest7.cc 

OBJS += \
./rbf/pfm.o \
./rbf/rbfm.o \
./rbf/rbftest7.o 

CC_DEPS += \
./rbf/pfm.d \
./rbf/rbfm.d \
./rbf/rbftest7.d 


# Each subdirectory must supply rules for building sources it contributes
rbf/%.o: ../rbf/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



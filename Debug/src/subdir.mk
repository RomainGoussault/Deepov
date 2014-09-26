################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Board.cpp \
../src/Color.cpp \
../src/Main.cpp \
../src/Piece.cpp \
../src/Position.cpp 

OBJS += \
./src/Board.o \
./src/Color.o \
./src/Main.o \
./src/Piece.o \
./src/Position.o 

CPP_DEPS += \
./src/Board.d \
./src/Color.d \
./src/Main.d \
./src/Piece.d \
./src/Position.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



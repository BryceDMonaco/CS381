################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Aspect.cpp \
../src/Command.cpp \
../src/Engine.cpp \
../src/Entity381.cpp \
../src/EntityMgr.cpp \
../src/GameMgr.cpp \
../src/GfxMgr.cpp \
../src/InputMgr.cpp \
../src/Mgr.cpp \
../src/PhysicsAspect.cpp \
../src/RenderableAspect.cpp \
../src/RotatorAspect.cpp \
../src/SoundMgr.cpp \
../src/SphereEntity.cpp \
../src/UnitAI.cpp \
../src/Utils.cpp \
../src/main.cpp 

OBJS += \
./src/Aspect.o \
./src/Command.o \
./src/Engine.o \
./src/Entity381.o \
./src/EntityMgr.o \
./src/GameMgr.o \
./src/GfxMgr.o \
./src/InputMgr.o \
./src/Mgr.o \
./src/PhysicsAspect.o \
./src/RenderableAspect.o \
./src/RotatorAspect.o \
./src/SoundMgr.o \
./src/SphereEntity.o \
./src/UnitAI.o \
./src/Utils.o \
./src/main.o 

CPP_DEPS += \
./src/Aspect.d \
./src/Command.d \
./src/Engine.d \
./src/Entity381.d \
./src/EntityMgr.d \
./src/GameMgr.d \
./src/GfxMgr.d \
./src/InputMgr.d \
./src/Mgr.d \
./src/PhysicsAspect.d \
./src/RenderableAspect.d \
./src/RotatorAspect.d \
./src/SoundMgr.d \
./src/SphereEntity.d \
./src/UnitAI.d \
./src/Utils.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



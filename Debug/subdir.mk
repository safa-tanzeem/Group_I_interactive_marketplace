################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../\ inventory_creation.c \
../buyer_functions.c \
../buyer_wallet.c \
../display_inventory.c \
../main.c \
../scanner.c \
../seller_manager.c \
../stock_update.c \
../update_buyer_info.c 

OBJS += \
./\ inventory_creation.o \
./buyer_functions.o \
./buyer_wallet.o \
./display_inventory.o \
./main.o \
./scanner.o \
./seller_manager.o \
./stock_update.o \
./update_buyer_info.o 

C_DEPS += \
./\ inventory_creation.d \
./buyer_functions.d \
./buyer_wallet.d \
./display_inventory.d \
./main.d \
./scanner.d \
./seller_manager.d \
./stock_update.d \
./update_buyer_info.d 


# Each subdirectory must supply rules for building sources it contributes
\ inventory_creation.o: ../\ inventory_creation.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF" inventory_creation.d" -MT"\ inventory_creation.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



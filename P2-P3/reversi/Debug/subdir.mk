################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../8led.c \
../Bmp.c \
../boton_antirebotes.c \
../button.c \
../cola_pantalla.c \
../control_modo_procesador.c \
../controlador_excepciones.c \
../controlador_latido.c \
../debug_stack.c \
../jugada_por_botones.c \
../jugada_por_pantalla.c \
../lcd.c \
../led.c \
../main.c \
../pantalla_reversi.c \
../reversi8_2019.c \
../timer.c \
../timer1.c \
../timer2.c \
../tp.c 

ASM_SRCS += \
../generardor_interrupciones.asm \
../patron_volteo_arm_arm.asm \
../patron_volteo_arm_c.asm 

OBJS += \
./8led.o \
./Bmp.o \
./boton_antirebotes.o \
./button.o \
./cola_pantalla.o \
./control_modo_procesador.o \
./controlador_excepciones.o \
./controlador_latido.o \
./debug_stack.o \
./generardor_interrupciones.o \
./jugada_por_botones.o \
./jugada_por_pantalla.o \
./lcd.o \
./led.o \
./main.o \
./pantalla_reversi.o \
./patron_volteo_arm_arm.o \
./patron_volteo_arm_c.o \
./reversi8_2019.o \
./timer.o \
./timer1.o \
./timer2.o \
./tp.o 

C_DEPS += \
./8led.d \
./Bmp.d \
./boton_antirebotes.d \
./button.d \
./cola_pantalla.d \
./control_modo_procesador.d \
./controlador_excepciones.d \
./controlador_latido.d \
./debug_stack.d \
./jugada_por_botones.d \
./jugada_por_pantalla.d \
./lcd.d \
./led.d \
./main.d \
./pantalla_reversi.d \
./reversi8_2019.d \
./timer.d \
./timer1.d \
./timer2.d \
./tp.d 

ASM_DEPS += \
./generardor_interrupciones.d \
./patron_volteo_arm_arm.d \
./patron_volteo_arm_c.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -I"C:\Users\Martin\Desktop\Clase\Universidad\Tercero\cuatri_1\Proyecto Hardware\Practicas\Practica 3\LAB-18-12-19 - FINAL\reversi\common" -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -mapcs-frame -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

%.o: ../%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC Assembler'
	arm-none-eabi-gcc -x assembler-with-cpp -I"C:\Users\Martin\Desktop\Clase\Universidad\Tercero\cuatri_1\Proyecto Hardware\Practicas\Practica 3\LAB-18-12-19 - FINAL\reversi\common" -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=arm7tdmi -g3 -gdwarf-2 -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



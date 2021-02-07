.global patron_volteo_arm_c
.extern ficha_valida
espacio: .space 4
#r0 tablero
#r1 longitud
#r2 FA
#r3 CA
.arm
patron_volteo_arm_c:
	@r0-->@tablero
	@r1-->@longitud
	@r2-->FA
	@r3-->CA
	@r4-->SF
	@r5-->SC
	@r6-->color
	@r7-->@pos_valida

	mov ip, sp								@Cargamos la direccion en pila de los parametros
	stmfd sp!, {r0,r1,r4-r7, lr} 			@Salvamos el contexto y r0 y r1 para no perderlo en la llamada

	ldmfd ip, {r4-r6}						@Cargamos valores de las variables

	add r2, r2, r4
	add r3, r3, r5
	stmfd sp!, {r2, r3}

	mov r1, r2			@r1<--FA		|
	mov r2, r3			@r2<--CA		|	cargamos los parametros de ficha_valida
	ldr r3, =espacio	@r3<--pos_valida|

	bl  ficha_valida

bucle:
	ldr r3, =espacio					@
	ldr r3, [r3]						@	Cargamos el contenido de posicion valida

	cmp r3, #1							@	si la posicion no es valida
	bne salir_bucle						@

	cmp r0, r6							@ 	si el color es igual
	beq salir_bucle						@
	ldmia sp!, {r2,r3}

	add r2, r2, r4						@FA = FA + SF
	add r3, r3, r5						@CA = CA + SC

	ldmia sp!, {r0,r1}					@	Recuperamos tablero y longitud

	ldr r7, [r1, #0]					@	|
	add r7, r7, #1						@	|	longitud ++
	str r7, [r1, #0]					@ 	|

	stmdb sp!, {r0,r1}

	stmfd sp!, {r2, r3}
	mov r1, r2							@ 	|	cargo los parametros a pasar a ficha valida (tablero, FA, CA)
	mov r2, r3							@	|
	ldr r3, =espacio

	bl  ficha_valida
	b bucle

salir_bucle:

	ldr r3, =espacio					@
	ldr r3, [r3]						@	Cargamos el contenido de posicion valida

	cmp r3, #1							@	si la posicion no es valida
	bne no_patron_carga_pila			@

	ldmia sp!, {r2,r3}
	cmp r0, r6							@	Si el color de la ultima ficha de patron_volteo no es igual a la
	bne no_patron						@   inicial entonces no hay patron

	ldmia sp, {r0, r1}

	ldr r7, [r1, #0]					@
	cmp r7, #0							@	Si la longitud es menor o igual que 0 no hay patron
	bls no_patron						@

	ldmia sp!, {r0,r1,r4-r7, lr} 		@	Recuperamos el contexto

	mov r0, #1							@ 	Si he llegado hasta aqui es porque hay patron

	bx lr								@	Volvemos a la siguiente instruccion a la de llamada a patron_volteo_arm

no_patron_carga_pila:
	ldmia sp!, {r2, r3}
no_patron:
	ldmia sp!, {r0,r1,r4-r7, lr} 		@   Recuperamos el contexto
	mov r0, #0
	bx lr
.end

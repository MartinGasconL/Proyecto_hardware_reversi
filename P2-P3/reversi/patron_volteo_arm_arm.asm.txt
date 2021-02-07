.global patron_volteo_arm_arm
espacio: .space 4
#r0 tablero
#r1 longitud
#r2 FA
#r3 CA
.arm
patron_volteo_arm_arm:
	@r0-->@tablero
	@r1-->@longitud
	@r2-->FA
	@r3-->CA
	@r4-->SF
	@r5-->SC
	@r6-->color
	@r7-->casilla
	@r8-->auxiliar
	@r9-->posicion_valida

	mov ip, sp							@Cargamos la direccion en pila de los parametros
	stmfd sp!, {r0,r1,r4-r9, lr} 		@Salvamos el contexto y r0 y r1 para no perderlo en la llamada

	ldmfd ip, {r4-r6}					@Cogemos valores de las variables

	add r2, r2, r4						@	FA = FA + SF
	add r3, r3, r5						@	CA = CA + SC

	cmp r2, #8							@	|	FA < 8
	bge else							@	|

	cmp r2, #0							@	|	FA >= 0
	blt else							@	|

	cmp r3, #8							@	|	CA < 8
	bge else							@	|

	cmp r3, #0							@	|	CA >= 0
	blt else							@	|

	add r7, r3, r2, lsl #3				@	Posición del tablero r7 = r3 + r2 * 8
	ldrb r7, [r0, r7] 					@	r7 = tablero[FA, CA]

	cmp r7, #0							@	|	tablero[FA, CA] != 0
	beq else							@	|

	ldr r9, =espacio 					@	|	*posicion_valida = 1
	mov r8, #1							@	|
	str r8, [r9, #0]					@	|

	b end_if
else:
	ldr r9, =espacio					@	|	*posicion_valida = 0
	mov r8, #0							@	|
	str r8, [r9, #0]					@	|

	mov r7, #0

end_if:

bucle:
	ldr r9, [r9, #0]					@	|	*posicion_valida == 1
	cmp r9, #1							@	|
	bne salir_bucle						@	|

	cmp r7, r6							@ 	|	si el color es igual, a tablero[FA, CA]
	beq salir_bucle						@	|

	add r2, r2, r4						@	FA = FA + SF
	add r3, r3, r5						@	CA = CA + SC

	ldr r7, [r1, #0]					@	|
	add r7, r7, #1						@	|	longitud ++
	str r7, [r1, #0]					@ 	|

	cmp r2, #8							@ 	|	FA < 8
	bge else1							@	|

	cmp r2, #0							@ 	|	FA >= 0
	blt else1							@	|

	cmp r3, #8							@	|	CA < 8
	bge else1							@	|

	cmp r3, #0							@	|	Ca >= 0
	blt else1							@	|

	add r7, r3, r2, lsl #3				@	Posición del tablero r7 = r3 + r2 * 8
	ldrb r7, [r0, r7] 					@	r7 = tablero[FA, CA]

	cmp r7, #0							@	|	r7 != 0
	beq else1							@	|

	ldr r9, =espacio 					@	|	posición valida* = 1
	mov r8, #1							@	|
	str r8, [r9, #0]					@	|

	b end_if1

else1:

	ldr r9, =espacio					@	|	posición valida* = 0
	mov r8, #0							@	|
	str r8, [r9, #0]					@	|

	mov r7, #0

end_if1:
	b bucle

salir_bucle:
	ldr r9, =espacio
	ldr r9, [r9]						@	Cargamos el contenido de posicion valida

	cmp r9, #1							@	si la posicion no es valida
	bne no_patron						@

	cmp r7, r6							@	Si la ultima ficha de patron_volteo no es igual a la inicial entonces no hay patron
	bne no_patron						@

	ldr r7, [r1, #0]					@
	cmp r7, #0							@	Si la longitud es menor o igual que 0 no hay patron
	bls no_patron						@

	ldmia sp!, {r0,r1,r4-r9, lr} 		@	Recuperamos el contexto
	mov r0, #1							@ 	Si he llegado hasta aqui es porque hay patron
	bx lr								@	Volvemos a la siguiente instruccion a la de llamada a patron_volteo_arm

no_patron:

	ldmia sp!, {r0,r1,r4-r9, lr} 	@Recuperamos el contexto
	mov r0, #0
	bx lr

.end

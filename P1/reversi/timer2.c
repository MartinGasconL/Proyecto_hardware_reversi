/*********************************************************************************************
* Fichero:      timer.c
* Autor:
* Descrip:      funciones de control del timer0 del s3c44b0x
* Version:
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"

/*--- variables globales ---*/
unsigned volatile int timer2_num_int = 0;

/*--- declaracion de funciones ---*/
void timer2_ISR(void) __attribute__((interrupt("IRQ")));
void timer2_inicializar(void);

/*--- codigo de las funciones ---*/
void timer2_ISR(void)
{
    timer2_num_int++; //incrementamos el numero de interrupciones
    /* borrar bit en I_ISPC para desactivar la solicitud de interrupción*/
    rI_ISPC |= BIT_TIMER2; // BIT_TIMER2 está definido en 44b.h y pone un uno en el bit que correponde al Timer2
}

void timer2_inicializar(void)
{
	/* Configuraion controlador de interrupciones */

		    rINTMOD = 0x0; 							// Configura las linas como de tipo IRQ
		    rINTMSK &= ~(BIT_TIMER2); 				// Emascara todas las lineas excepto Timer2

		    pISR_TIMER2 = (unsigned) timer2_ISR; 	// Establece la rutina de servicio para TIMER2

		/* Configuraion del timer */

			rTCFG0 &= 0xFFFF00FF;		//  Prescalado a 0 de los timer 2, 3 y 4
			rTCFG1 &= ~ 0x00000F00;		//  Para que sean el maximo de ciclos por interrupcion el divisor = 1/2

			rTCNTB2 = 65535;			// 	Es un registro de 16 bits y debe ser lo maximo, luego 0xFFFF = 65535
			rTCMPB2 = 0;				//	El valor minimo en el que se disparara la interrupcion

			rTCON = 0x2000;				//  Manual update(13) a 1 y el resto a 0
			rTCON = 0x8000;				//  autoreload(15) a 1 y el resto a 0 (Manual-update también)
}

unsigned int timer2_leer(void){
	unsigned int int_antes = timer2_num_int;
	unsigned int ticks = rTCNTB2 - rTCNTO2;
	unsigned int int_despues = timer2_num_int;

	unsigned int total_ticks = (int_despues << 16) - int_despues;

	if (int_antes == int_despues) {		//Si estan dentro del mismo ciclo hay tics pendientes
		total_ticks += ticks;
	}
										//Si estan en diferente ciclo estás en el primer tic del segundo ciclo
	return total_ticks >> 5;
}

void timer2_empezar(void){
	timer2_num_int = 0;

	rTCON = 0x2000;			// Manual update(13) a 1 y el resto a 0
	rTCON = 0x9000;			// autoreload(15) a 1 y el resto a 0 (Manual-update también)

}

unsigned int timer2_parar(void){
	rTCON &= ~(1 << 12);	//Paramos el timer
	return timer2_leer();
}

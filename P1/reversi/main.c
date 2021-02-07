/*********************************************************************************************
* Fichero:	main.c
* Autor:
* Descrip:	punto de entrada de C
* Version:  <P4-ARM.timer-leds>
*********************************************************************************************/

/*--- ficheros de cabecera ---*/

#include "timer.h"
#include "44blib.h"
#include "44b.h"

/*--- variables globales ---*/


/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializa controladores */
	sys_init();         // Inicializacion de la placa, interrupciones y puertos
	//reversi8();
	test();
	//test_timer();

}

void test_timer(){
	timer2_inicializar();
	timer2_empezar();
	Delay(10);	// * 100 us
	unsigned int primera_lectura = timer2_parar();
	timer2_empezar();
	Delay(100);	// * 100 us
	unsigned int segunda_lectura = timer2_parar();
	timer2_empezar();
	Delay(10000);	// * 100 us
	unsigned int tercera_lectura = timer2_parar();
	timer2_empezar();
	Delay(100000);	// * 100 us
	unsigned int cuarta_lectura = timer2_leer();
	timer2_parar();
}


/* Controla tareas periodicas de tiempo-real de manera sencilla */

#include <avr/interrupt.h>


/* Símbolos comunes a C */
#ifndef NULL
#define NULL 0
#endif


/* Tipo de datos para una tarea:
 * Contiene un reloj por software y una funcion (tarea)
 */
typedef struct {
	int ms; 	/* período */
	int st;		/* soft timer tick */
	void (*func) (void);
} task_t;

#define N_TAREAS 4

/* Arreglo que mantiene un listado de tareas con sus respectivos
 * relojes de software
 */
static task_t tasks[N_TAREAS];

volatile int task_sync = 0;	/* para sincronizar con timer */

int n = 0; 	/* n current tasks */


void tasks_init()
{
	int i;

	for (i=0; i<N_TAREAS; i++)
		tasks[i].func = NULL;
}


int tasks_def(int ms, void (*f))
{
	if (n == N_TAREAS)
		return -1;

	tasks[n].ms = ms;
	tasks[n].st = ms;
	tasks[n].func = f;
	n++;

	return 0;
}


void tasks_do()
{
	int i;

	if (task_sync == 0)
		return;

	/* región critica */
	cli();
	task_sync = 0;
	sei();
		
	for (i=0; i < n ; i++) {

		tasks[i].st--;
		if (tasks[i].st == 0) {	/* timer done: run the task */
			tasks[i].st = tasks[i].ms;
			tasks[i].func();
		};
	}
}

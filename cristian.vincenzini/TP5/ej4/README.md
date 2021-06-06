Implementa varios software timers que utilizan el mismo
hardware timer (timer0) para ejecutar varias tareas:

* Parpadear led integrado al arduino
* Parpadear led externo (pin 10)
* Enviar la hora/fecha por puerto serial

tasks.c define la estructura task_t la cual posee tres atributos:
* Periodo, tiempo que ira variando y al llegar a cero se reiniciará
* Timer, valor al que se reiniciará el periodo
* Función, tarea que se realizará

Un arreglo de tipo task_t contendrá la cantidad de tareas a realizar.

Para ejecutar las tareas se utiliza la variable de sincronización task_sync.
La variable comienza en 0 y es incrementada a traves de timer.c cuando ocurre una interrupción.

El metodo tasks_do chequea la variable task_sync
si no se han producido interrupciones no ejecuta las tareas
si se han producido se ejecuta cada tarea.

Pasos:

1. make clean
2. make
3. make flash

Presionar el boton de reset un tiempo y soltar,
repetir si no funciona

Datos cutecom:

* baudrate = 9600
* data bits = 8
* bit de stop = 1

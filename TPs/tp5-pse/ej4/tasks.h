
/* Controla tareas periodicas de tiempo-real de manera sencilla */

#ifndef TASKS_H
#define TASKS_H

void tasks_init(void);
int tasks_def(int ms, void (*f));
void tasks_do(void);

#endif /* TASKS_H */

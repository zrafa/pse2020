#ifndef _CLOCK_H
#define _CLOCK_H

void timer0_init(void);
int cant_ticks(void);
void timer0_rtc_to_str(char buffer[]);
char timer0_rtc_get_tos(void);

#endif


#ifndef _CLOCK_H
#define _CLOCK_H

void timer0_init( void );

int cant_ticks();
void timer0_rtc_to_str(char buffer[]);
char timer0_rtc_get_tos();
void timer0_rtc_set(int year, int month, int day, int hour, int m, int sec);
int timer0_rtc_get_sec();

#endif

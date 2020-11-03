
#ifndef _CLOCK_H
#define _CLOCK_H

void timer0_init( void );
char timer0_rtc_get_tos();
void timer0_rtc_to_str(char buffer[]);

#endif

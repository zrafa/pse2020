/**********************************************************************
 *
 * Filename:    serial.h
 * 
 * API para la aplicacion embebida 
 * META : ocultar el hardware a la aplicacion 
 *
 **********************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H


void serial_init(void);
void serial_put_char(char out_put_char);
char serial_get_char(void);
void serial_put_String(char cadena[]);

#endif /* _SERIAL_H */

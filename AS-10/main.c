/*
 * File:   main.c
 */
#pragma config WDTE = OFF

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000 
#endif

#include <xc.h>
#include "config.h"        
#include "digital_keypad.h"

void main(void) {
    init_config();
    show_login_screen();
    
    while (1) {
        // Use the getter function to safely check the remaining attempts
        if (get_attempts_left() > 0) {
            
            unsigned char key = read_digital_keypad(EDGE);   
            
            handle_blinker();
            process_keypress(key);
            verify_password();
            
        } else {
            handle_lockout();
        }
    }
}
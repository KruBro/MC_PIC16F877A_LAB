#include "config.h"
#include <xc.h>
#include "clcd.h"
#include "digital_keypad.h"
#include "my_string.h"

/* ==========================================
 * PRIVATE STATE VARIABLES (Data Hiding)
 * ========================================== */
static unsigned char i = 0; 
static unsigned char attempts_left = MAX_ATTEMPTS;
static char my_pass[PASS_LENGTH + 1]; 
static const char user_pass[PASS_LENGTH + 1] = "11110000";

static unsigned int blink_counter = 0;
static unsigned char cursor_visible = 0;

/* ==========================================
 * HELPER FUNCTIONS
 * ========================================== */
void init_config(void) {
    initKeypad();
    init_clcd();
}

void show_login_screen(void) {
    clcd_print("PassWord:       ", LINE1(0)); 
    clcd_putch('_', LINE2(0)); 
}

void handle_blinker(void) {
    if (blink_counter++ >= 10000) { 
        blink_counter = 0;
        cursor_visible = !cursor_visible; 
        
        if (i < PASS_LENGTH) {
            clcd_putch(cursor_visible ? '_' : ' ', LINE2(i));
        }
    }
}

void process_keypress(unsigned char key) {
    if (key == SW1 || key == SW2) {
        my_pass[i] = (key == SW1) ? '0' : '1';
        clcd_putch('*', LINE2(i)); 
        i++;
        
        blink_counter = 0;
        cursor_visible = 1;
        
        if (i < PASS_LENGTH) {
            clcd_putch('_', LINE2(i)); 
        }
    }
}

void verify_password(void) {
    if (i == PASS_LENGTH) {
        my_pass[PASS_LENGTH] = '\0'; 
        
        if (my_strcmp(user_pass, my_pass) == 0) {
            clcd_print("Correct Entry   ", LINE1(0));
            clcd_print("Access Granted  ", LINE2(0));
            while(1); 
        } else {
            attempts_left--;
            clcd_print("Invalid Entry   ", LINE1(0));
            clcd_putch(attempts_left + '0', LINE2(0)); 
            clcd_print(" Left!        ", LINE2(1));
            
            for(volatile unsigned long wait = 0; wait < 200000; wait++); 
            
            i = 0;              
            clcd_clear();
            
            if (attempts_left > 0) {
                show_login_screen();
            }
        }
    }
}

void handle_lockout(void) {
    clcd_print("Device Locked   ", LINE1(0));
    clcd_print("Contact Admin   ", LINE2(0));
    while(1); 
}

unsigned char get_attempts_left(void) {
    return attempts_left;
}
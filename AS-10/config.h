#ifndef CONFIG_H
#define CONFIG_H

#define PASS_LENGTH 8
#define MAX_ATTEMPTS 5

// Helper function prototypes
void init_config(void);
void show_login_screen(void);
void handle_blinker(void);
void process_keypress(unsigned char key);
void verify_password(void);
void handle_lockout(void);

// Getter function so main.c can check the remaining attempts
unsigned char get_attempts_left(void);

#endif /* CONFIG_H */
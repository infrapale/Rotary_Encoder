#include <Arduino.h>
#include <time.h>
#include "rotenc.h"
// private declarations
void irq_rotenc_rot(void);
void irq_rotenc_press(void);



#define LED 13
static volatile int position;
static volatile uint8_t slow_down = 0;
static volatile uint8_t ups = 0;
static volatile uint8_t downs = 0;
static volatile int max_pos = 100;
static volatile int min_pos = 0;
static volatile unsigned long int last_not_pressed_time;
static volatile uint8_t pressed_state = 1;
static volatile uint8_t pressed_value = 0;
static volatile uint8_t inpA;
static volatile uint8_t inpB;
static volatile uint8_t inpC;

void rotenc_init(uint8_t _inpA, uint8_t _inpB, uint8_t _inpC)
{
    // Rotary encoder input lines
    // Configure as input, turn on pullup resistors
	inpA = _inpA;
	inpB = _inpB;
	inpC = _inpC;
    pinMode(inpA, INPUT_PULLUP);
    pinMode(inpB, INPUT_PULLUP);
	pinMode(inpC, INPUT_PULLUP);
	last_not_pressed_time = millis();
    attachInterrupt(digitalPinToInterrupt(inpA), irq_rotenc_rot, RISING);
	attachInterrupt(digitalPinToInterrupt(inpC), irq_rotenc_press, CHANGE);
}
void rotenc_set_step(int _pos, int _min, int _max, uint8_t _slow_down){
	position = _pos;
	min_pos = _min;
	max_pos = _max;
	slow_down = _slow_down;
} 
int get_pos(void)
{
	return(position);
}

void irq_rotenc_rot(void)
{
    if(digitalRead(inpB)){
        ups++;
    } else  {
        downs++;
    }
    if (ups > slow_down ){
        if (position < max_pos) position++;
        ups = 0; downs = 0;
    } else if (downs > slow_down) {
        if (position > min_pos) position--;
        ups = 0; downs = 0;
    }
}

uint8_t rd_pressed(void){
	uint8_t tmp = pressed_value;
	pressed_value = 0;
	return(tmp);
}
void irq_rotenc_press(void){
	unsigned long int time_now = millis();
	unsigned long int time_pressed;
	if (digitalRead(inpC) == LOW) 
	{
		if (pressed_state == 1){
			last_not_pressed_time = time_now;
			pressed_state = 0;
		} else {
			;
		}
	} 
	else {
		if (pressed_state == 0){
			time_pressed = time_now - last_not_pressed_time;
			if (time_pressed < 100) {
				;  // neglect
			}	
			else {
				if (time_pressed < 500)  {
					pressed_value = 1;
				}
				else {
					if (time_pressed < 2000)  {
						pressed_value = 2;
					} 
					else {
						pressed_value = 3;
					}	
				}
			}
		}
		pressed_state = 1;
	}
	
}
//attachInterrupt(digitalPinToInterrupt(pin), ISR, mode) (recommended)

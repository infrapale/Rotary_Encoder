#ifndef ROTENC_H
#define ROTENC_H 

#ifdef __cplusplus
extern "C" {
#endif
void rotenc_init(uint8_t inpA, uint8_t inpB, uint8_t inpC);
void rotenc_set_step(int _pos, int _min, int _max, uint8_t _slow_down);
int get_pos(void);
uint8_t rd_pressed(void);

#ifdef  __cplusplus
}
#endif

#endif
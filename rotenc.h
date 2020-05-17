#ifndef ROTENC_H
#define ROTENC_H 

#ifdef __cplusplus
extern "C" {
#endif
void    rotenc_init(uint8_t inpA, uint8_t inpB, uint8_t inpC);
void    rotenc_set_step(int _pos, int _min, int _max, int _direction);
int     rotenc_get_pos(void);
uint8_t rotenc_rd_pressed(void);

#ifdef  __cplusplus
}
#endif

#endif
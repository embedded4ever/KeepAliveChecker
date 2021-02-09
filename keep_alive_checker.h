//vvolkanunal@gmail.com wrote this file.

#ifndef KEEP_ALIVE_CHECKER_H_INCLUDED
#define KEEP_ALIVE_CHECKER_H_INCLUDED

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

struct keep_alive_checker_t;

struct keep_alive_checker_t* new_checker(void);

void checker_ctr(struct keep_alive_checker_t* self);

void checker_dtr(struct keep_alive_checker_t* self);

uint8_t* checker_data_packed(struct keep_alive_checker_t* self, int opcode);

void checker_inc_tx(struct keep_alive_checker_t* self);

void checker_inc_rx(struct keep_alive_checker_t* self);

uint32_t checker_get_tx(const struct  keep_alive_checker_t* self);

uint32_t checker_get_rx(const struct keep_alive_checker_t* self);

int parse(struct keep_alive_checker_t* self, const struct keep_alive_checker_t* fakeself);

#ifdef __cplusplus
}
#endif

#endif



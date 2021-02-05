//vvolkanunal@gmail.com wrote this file.

#ifndef KEEP_ALIVE_PLATFORM_H_INCLUDED
#define KEEP_ALIVE_PLATFORM_H_INCLUDED

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*tx_cbf)(const uint8_t* send_buf, uint8_t size);
typedef void (*fault_cbf)(void* self);

struct keep_alive_platform_t;

struct keep_alive_platform_t* new_platform(void);

void platform_ctr(struct keep_alive_platform_t* self, uint16_t timeout_ms, tx_cbf tx_cb, fault_cbf fault_cb);

void platform_dtr(struct keep_alive_platform_t* self);

void platform_systick(struct keep_alive_platform_t* self);

int is_timeout_overflow(const struct keep_alive_platform_t* self);

void add_buf_and_parse(struct keep_alive_platform_t* self, const uint8_t* buf);

uint32_t get_rx(const struct keep_alive_platform_t* self);

uint32_t get_tx(const struct keep_alive_platform_t* self);

void change_frequency_checker(struct keep_alive_platform_t* self, uint16_t timeout);


#ifdef __cplusplus
}
#endif

#endif
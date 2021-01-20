//vvolkanunal@gmail.com wrote this file.

#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "keep_alive_checker.h"
#include "stdio.h"

typedef void (*tx_cbf)(const uint8_t* send_buf, uint8_t size);

typedef enum e_opcode
{
    KEEP_ALIVE_CHECK = 0x02,
    KEEP_ALIVE_CHECK_RETRY,
    KEEP_ALIVE_LAST_CHECK,

}e_opcode;

e_opcode code = KEEP_ALIVE_CHECK;

typedef struct 
{   
    uint16_t ticker;
    uint16_t timeout;
    uint32_t old_rx;
    uint32_t old_tx;
    tx_cbf tx_cb;
    uint8_t buffer[11];
    struct keep_alive_checker_t* kac;

}keep_alive_platform_t;

keep_alive_platform_t* new_platform(void)
{
    return (keep_alive_platform_t*)malloc(sizeof(keep_alive_platform_t));
}

void platform_ctr(keep_alive_platform_t* self, uint16_t timeout_ms, tx_cbf tx_cb)
{
    self -> timeout = timeout_ms;
    self -> tx_cb = tx_cb;
    self -> ticker = 0;
    self -> old_rx = 0;
    self -> old_tx = 0;

    memset(self -> buffer, 0, sizeof(self -> buffer));

    self -> kac = new_checker();
    checker_ctr(self -> kac);
}

void platform_dtr(keep_alive_platform_t* self)
{
    checker_dtr(self -> kac);

    free(self -> kac);
}

int is_timeout_overflow(const keep_alive_platform_t* self)
{
    return (self -> ticker > self -> timeout);
}

void platform_systick(keep_alive_platform_t* self)
{
    self -> ticker++;

    if (is_timeout_overflow(self)) 
    {
        uint8_t *buffer = checker_data_packed(self -> kac, code);
               
        self -> tx_cb (buffer, 12);

        self -> ticker = 0;
        
        //checker_inc_tx(self -> kac);     
    }    
}

void add_buf_and_parse(keep_alive_platform_t* self, const uint8_t* buf)
{
    struct keep_alive_checker_t *cm =  (struct keep_alive_checker_t*)buf;
    
    if (parse (self -> kac, cm))
    {
        printf("\r\n True Frame, Inc Tx");
        checker_inc_tx(self -> kac);
    }

    else
    {
        code = KEEP_ALIVE_CHECK_RETRY;
    }    
}

uint32_t get_rx(const keep_alive_platform_t* self)
{
    return checker_get_rx(self -> kac);
}

uint32_t get_tx(const keep_alive_platform_t* self)
{
    return checker_get_tx(self -> kac);
}

void change_frequency_checker(keep_alive_platform_t* self, uint16_t timeout)
{
    self -> timeout = timeout;
}





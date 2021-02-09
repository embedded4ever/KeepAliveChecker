#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum e_opcode
{
    KEEP_ALIVE_CHECK = 0x02,
    KEEP_ALIVE_CHECK_RETRY,
    KEEP_ALIVE_LAST_CHECK,

}e_opcode;

/*static e_opcode ret_opcode(int val)
{
    switch (val)
    {
    case 1:
        return KEEP_ALIVE_CHECK;
    case 2:
        return KEEP_ALIVE_CHECK_RETRY;
    case 3: 
        return KEEP_ALIVE_LAST_CHECK;    
    default:
        break;
    }
}*/

typedef struct __attribute__((packed))
{     
    uint8_t start_of_frame;
    uint8_t op_code;
    uint32_t tx_cnt;
    uint32_t rx_cnt;
    uint8_t end_of_frame;

}keep_alive_checker_t;

keep_alive_checker_t* new_checker(void)
{
    return (keep_alive_checker_t*)malloc(sizeof(keep_alive_checker_t));
}

void checker_ctr(keep_alive_checker_t* self)
{
    self -> start_of_frame = 0x01;
    self -> tx_cnt = 0;
    self -> rx_cnt = 0;
    self -> end_of_frame = 0x21;
}

void checker_dtr(keep_alive_checker_t* self)
{
    //Nothing
}

uint8_t* checker_data_packed(keep_alive_checker_t* self, int opcode)
{
    self -> start_of_frame = 0x01;
    self -> op_code = opcode; //ret_opcode(opcode);
    self -> tx_cnt = self -> tx_cnt + 1;
    self -> rx_cnt = self -> rx_cnt;
    self -> end_of_frame = 0x21;

    static uint8_t test[11] = {0};

    memcpy(test, self, 11);
    
    return test;    
}

void checker_inc_tx(keep_alive_checker_t* self)
{
    self -> tx_cnt = self -> tx_cnt + 1;
}

void checker_inc_rx(keep_alive_checker_t* self)
{
    self -> rx_cnt = self -> rx_cnt + 1;
}

uint32_t checker_get_tx(const keep_alive_checker_t* self)
{
    return self -> tx_cnt;
}

uint32_t checker_get_rx(const keep_alive_checker_t* self)
{
    return self -> rx_cnt;
}

int parse(keep_alive_checker_t* self, const keep_alive_checker_t* fakeself)
{   
    int ret = 0;

    if (self -> start_of_frame == fakeself -> start_of_frame &&
                self -> tx_cnt ==  fakeself -> tx_cnt        && 
                        self -> rx_cnt == fakeself -> rx_cnt &&
                            self -> end_of_frame == fakeself -> end_of_frame)
    {		
        printf("\r\n True ");
        return (ret = 1);
    }

    return ret;    

///*
//    printf("\r\n fakeself %d", fakeself -> start_of_frame);
//    printf("\r\n fakeself %d", fakeself -> op_code);
//    printf("\r\n fakeself %d", fakeself -> tx_cnt);
//    printf("\r\n fakeself %d", fakeself -> rx_cnt);
//    printf("\r\n fakeself %d", fakeself -> end_of_frame);
//*/
}

#ifdef __cplusplus
}
#endif

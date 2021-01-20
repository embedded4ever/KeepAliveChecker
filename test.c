//Basic Test
#include "keep_alive_checker.h"
#include "keep_alive_platform.h"
#include "stdio.h"
#include "stdlib.h"

static void uart_tx_platform_specific(const uint8_t* data, uint8_t size)
{
    for (int i = 0; i < 12; ++i)
    {
        printf("\r\n data[%d] = %d", i, data[i]);
    }	
}

int main()
{
    struct keep_alive_platform_t* kap = new_platform();

    platform_ctr(kap, 5000, uart_tx_platform_specific);

    static uint8_t buf[11] = {
        0x01, //start of frame
        0x02, //opcde
        0x00, 0x00, 0x00, 0x00, //rx_cnt
        0x00, 0x00, 0x00, 0x00, //tx_cnt
        0x21, //end of frame
    };

    add_buf_and_parse(kap, buf);
    add_buf_and_parse(kap, buf);

    /*
    platform_systick(kap);    
    platform_systick(kap);    
    platform_systick(kap);   
    platform_systick(kap);
    platform_systick(kap);
    platform_systick(kap);
    platform_systick(kap);
    platform_systick(kap);
    platform_systick(kap);
    */

    uint32_t ct = get_tx(kap);
    printf("\r\n ct = %d", ct);
    free(kap);

}
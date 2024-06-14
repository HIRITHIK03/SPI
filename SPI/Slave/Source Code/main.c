#include <stdint.h>
#include <SPI_SLAVE_Init.h>

#define SSI0_DR_R             (*((volatile uint32_t *)0x40008008))  // SSI Data
#define SSI0_SR_R             (*((volatile uint32_t *)0x4000800C))  // SSI Status

volatile unsigned char data;

int main(void) {

    SPI_SLAVE_Init();
    while (1) {

        while ((SSI0_SR_R & 0x04)==0) {}

            data=SSI0_DR_R;

        while(SSI0_SR_R & 0x10){}
   }
}

#include "SPI0_init.h"
#include "SPI0_Write.h"
#include "Delay.h"

// Main routine
int main(void)

{
    unsigned char val1 = 'A';

    SPI0_init();
    while (1)
    {
        SPI0_Write(val1); /* write a character */
        Delay(1000);
    }
}

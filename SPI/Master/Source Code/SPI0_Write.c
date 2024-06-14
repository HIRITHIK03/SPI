// Synchronous Serial Interface (SSI) Registers
#define SSI0_DR           (*(volatile unsigned long *)(SSI0_BASE + 0x8))
#define SSI0_SR           (*(volatile unsigned long *)(SSI0_BASE + 0xC))

#define SSI0_BASE         0x40008000

// Function to transmit data over SPI0
void SPI0_Write(unsigned char data)
{
    while ((SSI0_SR & 0x01) == 0);    /* wait until Tx FIFO is not full */
    SSI0_DR = data;                /* transmit byte over SSI0Tx line */
    while (SSI0_SR & 0x10);         /* wait until transmit complete */
}

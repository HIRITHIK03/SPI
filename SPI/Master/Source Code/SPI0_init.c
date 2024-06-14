// Define base addresses for registers
#define SYSCTL_BASE       0x400FE000
#define GPIO_PORTA_BASE   0x40058000
#define GPIO_PORTF_BASE   0x4005D000
#define SSI0_BASE         0x40008000

// System Control (SYSCTL) Registers
#define SYSCTL_RCGCSSI    (*(volatile unsigned long *)(SYSCTL_BASE + 0x61C))
#define SYSCTL_RCGCGPIO (*((volatile unsigned long *)0x400FE608))

// General-Purpose Input/Output (GPIO) Registers
#define GPIO_PORTA_DEN    (*(volatile unsigned long *)(GPIO_PORTA_BASE + 0x51C))
#define GPIO_PORTA_AFSEL  (*(volatile unsigned long *)(GPIO_PORTA_BASE + 0x420))
#define GPIO_PORTA_PCTL   (*(volatile unsigned long *)(GPIO_PORTA_BASE + 0x52C))
#define GPIO_PORTA_DIR    (*(volatile unsigned long *)(GPIO_PORTA_BASE + 0x400))
#define GPIO_PORTA_DATA   (*(volatile unsigned long *)(GPIO_PORTA_BASE + 0x3FC))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40058528))
#define GPIO_PORTA_PUR          (*((volatile unsigned int*)0x40058510))

#define GPIO_PORTF_DEN    (*(volatile unsigned long *)(GPIO_PORTF_BASE + 0x51C))
#define GPIO_PORTF_DIR    (*(volatile unsigned long *)(GPIO_PORTF_BASE + 0x400))
#define GPIO_PORTF_DATA   (*(volatile unsigned long *)(GPIO_PORTF_BASE + 0x3FC))

// Synchronous Serial Interface (SSI) Registers
#define SSI0_CR1          (*(volatile unsigned long *)(SSI0_BASE + 0x4))
#define SSI0_CC           (*(volatile unsigned long *)(SSI0_BASE + 0xFC8))
#define SSI0_CPSR         (*(volatile unsigned long *)(SSI0_BASE + 0x10))
#define SSI0_CR0          (*(volatile unsigned long *)(SSI0_BASE + 0x0))
#define SSI0_DR           (*(volatile unsigned long *)(SSI0_BASE + 0x8))
#define SSI0_SR           (*(volatile unsigned long *)(SSI0_BASE + 0xC))

// Define addresses
#define RCGCGPIO_ADDR   ((*(volatile unsigned int *)0x400FE608))
#define GPIOFDEN_ADDR   ((*(volatile unsigned int *)0x4005D51C))
#define GPIOFDIR_ADDR   ((*(volatile unsigned int *)0x4005D400))
#define GPIOFDATA_ADDR  ((*(volatile unsigned int *)0x4005D3FC))

// Define constants
#define GPIO_PIN_1      0x01
// Function to initialize SPI0
void SPI0_init(void)
{
    // Enable clock to SPI0, GPIOA, and GPIOF
    SYSCTL_RCGCSSI |= (1 << 0);   /* set clock enabling bit for SPI0 */
    SYSCTL_RCGCGPIO |= (1 << 0);  /* enable clock to GPIOA for SPI0 */


    // Initialize PA2 and PA3 for SPI0 alternate function
    GPIO_PORTA_AMSEL_R &=~0x03C;
    GPIO_PORTA_DEN |= 0x03C;       /* Set PA4 and PA5,PA2 AND PA3 as digital pins */
    GPIO_PORTA_AFSEL |= 0x03C;     /* enable alternate function of PA4 and PA5,PA2 AND PA3 */
    GPIO_PORTA_PCTL |= 0x00FFFF00;  /* assign PA4 and PA5 pins to SPI0 */

    // Initialize PF3 as a digital output as a slave select pin
     GPIO_PORTA_DEN |= (1 << 3);    /* set PA3 pin digital */
    GPIO_PORTA_DIR |= (1 << 3);    /* set PA3 pin output */
    GPIO_PORTA_DATA |= (1 << 3);   /* keep SS idle high */


    // Select SPI0 as a MasYter, POL = 0, PHA = 0, clock = 4 MHz, 8 bit data
    SSI0_CR1 = 0;                  /* disable SPI0 and configure it as a Master */
    SSI0_CC = 0;                   /* Enable System clock Option */
    SSI0_CPSR = 2;                 /* Select prescaler value of 4, i.e., 16MHz/4 = 4MHz */
    SSI0_CR0 = 0x0B07;           /* 4MHz SPI0 clock, SPI mode, 8 bit data */ //0x000B07
    SSI0_CR1 |= 0x02;              /* enable SPI0 */
}

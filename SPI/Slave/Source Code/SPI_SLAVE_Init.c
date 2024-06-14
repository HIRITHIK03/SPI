#include <stdint.h>

#define SYSCTL_RCGCSSI        (*((volatile uint32_t *)0x400FE61C))  // SSI Run Mode Clock Gating Control
#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608))  // GPIO Run Mode Clock Gating Control
#define SYSCTL_RCGCUART_R     (*((volatile unsigned long *)0x400FE618))
#define SYSCTL_RCGCSSI_R     0x00000001  // SSI Module 0 Run Mode Clock Gating Control

#define GPIO_PORTA_AFSEL_R    (*((volatile uint32_t *)0x40058420))  // GPIO Port A Alternate Function Select
#define GPIO_PORTA_DEN_R      (*((volatile uint32_t *)0x4005851C))  // GPIO Port A Digital Enable
#define GPIO_PORTA_PCTL_R     (*((volatile uint32_t *)0x4005852C))  // GPIO Port A Port Control
#define GPIO_PORTA_AMSEL_R    (*((volatile uint32_t *)0x40058528))  // GPIO Port A Analog Mode Select
#define GPIO_PORTA_DIR_R      (*((volatile uint32_t *)0x40058400))  // GPIO Port A Direction
#define GPIO_PORTA_DR8R_R     (*((volatile uint32_t *)0x40058508))  // GPIO Port A 8 mA Drive Select
#define GPIO_PORTA_PUR_R      (*((volatile uint32_t *)0x40058510))  // GPIO Port A Pull-Up Select
#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400583FC))


#define SSI0_CR0_R            (*((volatile uint32_t *)0x40008000))  // SSI Control 0
#define SSI0_CR1_R            (*((volatile uint32_t *)0x40008004))  // SSI Control 1
#define SSI0_DR_R             (*((volatile uint32_t *)0x40008008))  // SSI Data
#define SSI0_SR_R             (*((volatile uint32_t *)0x4000800C))  // SSI Status
#define SSI0_CPSR_R           (*((volatile uint32_t *)0x40008010))  // SSI Clock Prescale
#define SSI0_CC_R             (*((volatile uint32_t *)0x40008FC8))  // SSI Clock Control
#define SSI0_SSIEN_R          (*((volatile uint32_t *)0x40008FC0))  // SSI Enable


#define GPIO_PORTF_DEN_R       (*((volatile unsigned long *)0x4005D51C))
#define GPIO_PORTF_DIR_R       (*((volatile unsigned long *)0x4005D400))
#define GPIO_PORTF_DATA_R      (*((volatile unsigned long *)0x4005D3FC))

// Function to Initialization SPI Slave
void SPI_SLAVE_Init() {
    SYSCTL_RCGCSSI |= SYSCTL_RCGCSSI_R;       // Enable SSI0 module clock
    SYSCTL_RCGCGPIO_R |= 0x01;     // Enable GPIO Port A clock

    GPIO_PORTA_AFSEL_R |= 0x3C;                // Enable alternate function on PA2, PA3, PA4, PA5, and PA6
    GPIO_PORTA_DEN_R |= 0x3C;                  // Enable digital I/O on PA2, PA3, PA4, PA5, and PA6
    GPIO_PORTA_PCTL_R = 0xFFFF00;  // SSI pins on PA2, PA3, PA4, PA5, and PA6
    GPIO_PORTA_AMSEL_R &= ~0x3C;               // Disable analog functionality on PA2, PA3, PA4, PA5, and PA6

    SSI0_CR1_R = 0x00000000;                   // Disable SSI
    SSI0_CR1_R &= ~(0x00000002);               // Configure SSI as slave mode
    SSI0_CC_R = 0x0;                           // Use system clock
    SSI0_CPSR_R = 2;
    SSI0_CR0_R = 0x000B07;                   // Freescale SPI mode, 8-bit data
    SSI0_CR1_R |= 0x00000106;                  // Enable SSI
}

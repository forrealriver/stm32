 #define RCC_APB2ENR *(volatile unsigned long *)0x40021018
 #define GPIOB_CRL *(volatile unsigned long *)0x40010C00
 #define GPIOB_ODR *(volatile unsigned long *)0x40010C0C

int main(void)
 {
 RCC_APB2ENR |= 1<<3;

 GPIOB_CRL = (2<<0) | (0<<2);

 GPIOB_ODR = 0<<0;
 }

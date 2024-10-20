#include "stm32f4xx.h"  // Include device header for STM32F4
#include "VGA_Core.h"

static void HSYNC_Init(void)
{
    // Enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // Configure PA0 as Alternate Function
    GPIOA->MODER &= ~GPIO_MODER_MODER0;
    GPIOA->MODER |= GPIO_MODER_MODER0_1;
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL0;
    GPIOA->AFR[0] |= 0x01;
    // Set up TIM2 for PWM mode (PWM Mode 1)
    TIM2->PSC = 8 - 1;
    TIM2->ARR = 264 - 1;
    TIM2->CCR1 = 232;
    // Set OC1M to PWM Mode 1 (110)
    TIM2->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    // Enable Output Pre-load
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
    // Enable the output compare for channel 1 (CC1E)
    TIM2->CCER |= TIM_CCER_CC1E;
    // Enable the timer counter
    TIM2->CR1 |= TIM_CR1_CEN;
    // Force an update event to load the registers
    TIM2->EGR |= TIM_EGR_UG;
}

static void VSYNC_Init(void)
{
	// Enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    // Configure PB4 as Alternate Function (AF2)
    GPIOB->MODER &= ~GPIO_MODER_MODER4;
    GPIOB->MODER |= GPIO_MODER_MODER4_1;
    GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL4;
    GPIOB->AFR[0] |= 0x02;
    // Set up TIM3 for PWM mode (PWM Mode 1)
    TIM3->PSC = 80 - 1;
    TIM3->ARR = 16579 - 1;
    TIM3->CCR1 = 16474 - 1;
    // Set OC1M to PWM Mode 1 (110)
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    // Enable Output Pre-load
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    // Enable the output compare for channel 1 (CC1E)
    TIM3->CCER |= TIM_CCER_CC1E;
    // Enable the timer counter
    TIM3->CR1 |= TIM_CR1_CEN;
    // Force an update event to load the registers
    TIM3->EGR |= TIM_EGR_UG;
}

void PIXEL_Init(void)
{
	// Enable clock access
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    // Configure PB6 as Alternate Function (AF2)
    GPIOB->MODER &= ~(GPIO_MODER_MODE6);
    GPIOB->MODER |= (GPIO_MODER_MODE6_1);
    GPIOB->AFR[0] |= (2 << (6 * 4));
    // Configure TIM4 to generate a 40 MHz clock
    TIM4->PSC = 0;
    TIM4->ARR = 1;
    // Configure TIM4 in output compare toggle mode
    TIM4->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1;
    TIM4->CCER |= TIM_CCER_CC1E;
    // Enable the Counter
    TIM4->CR1 |= TIM_CR1_CEN;
}

void VGA_Init(void)
{
	HSYNC_Init();
	VSYNC_Init();
	PIXEL_Init();
}




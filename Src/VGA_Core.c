/**
 * @file VGA_Core.c
 * @brief Source file for VGA Core Functions
 *
 * This file provides definitions for functions
 * to initialize the synchronization signals and
 * transferring data to the monitor
 */

#include "VGA_Core.h"

volatile uint16_t currentLine = 0;

/**
 * @brief Initializes TIM2 to generate a 40 MHz signal
 * 		  for HSYNC line
 */
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

    TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM2->CCER |= TIM_CCER_CC1E;
    TIM2->CR1 |= TIM_CR1_CEN;
    TIM2->EGR |= TIM_EGR_UG;
}

/**
 * @brief Initializes TIM3 to generate a 40 MHz signal
 * 		  for VSYNC line
 */
static void VSYNC_Init(void)
{
    // Enable clock access for TIM3 and GPIOA
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA6 as Alternate Function (AF2)
    GPIOA->MODER &= ~GPIO_MODER_MODER6;
    GPIOA->MODER |= GPIO_MODER_MODER6_1;
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFRL6;
    GPIOA->AFR[0] |= 0x02 << (6 * 4);

    // Set up TIM3 for PWM mode
    TIM3->PSC = 80 - 1;
    TIM3->ARR = 16579 - 1;
    TIM3->CCR1 = 16474 - 1;

    // Set OC1M to PWM Mode 1 (110)
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M;
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;

    TIM3->CCMR1 |= TIM_CCMR1_OC1PE;
    TIM3->CCER |= TIM_CCER_CC1E;
    TIM3->CR1 |= TIM_CR1_CEN;
    TIM3->EGR |= TIM_EGR_UG;
}

/**
 * @brief Initializes TIM4 to generate a 40 MHz signal
 * 		  for PIXEL line
 */
static void PIXEL_Init(void)
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


/**
 * @brief Initializes PB0 as the Monochrome Data signal
 */
static void DATA_Init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= GPIO_MODER_MODER0_0;
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0;
}

/**
 * @brief Initializes DMA1 Stream5 Channel 7
 * 		  to transfer Frame Buffer to Data
 * 		  pin
 */
static void DMA_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
    DMA1_Stream5->CR &= ~DMA_SxCR_EN;
    DMA1_Stream5->CR |= DMA_SxCR_CHSEL;
    DMA1_Stream5->CR |= DMA_SxCR_DIR_0;
    DMA1_Stream5->CR |= DMA_SxCR_MINC;
    DMA1_Stream5->CR |= DMA_SxCR_PSIZE_0;
    DMA1_Stream5->CR |= DMA_SxCR_MSIZE_0;
    DMA1_Stream5->CR |= DMA_SxCR_CIRC;
    DMA1_Stream5->PAR = (uint32_t)&GPIOB->ODR;
    DMA1_Stream5->CR |= DMA_SxCR_EN;
}

/**
 * @brief Transfers a single line of pixel data
 * 		  from memory to GPIO Port B and manages
 * 		  active frame line
 */
void TIM2_IRQHandler(void)
{
    if (TIM2->SR & TIM_SR_UIF)
    {
    	TIM2->SR &= ~TIM_SR_UIF;
        if (currentLine < SCREEN_HEIGHT)
        {
            DMA1_Stream5->M0AR = (uint32_t)&frameBuffer[currentLine][0];
            DMA1_Stream5->NDTR = SCREEN_WIDTH / 8;
            DMA1_Stream5->CR |= DMA_SxCR_EN;
        }
        else
        {
            DMA1_Stream5->CR &= ~DMA_SxCR_EN; // Disable DMA transfer during blanking
        }
        currentLine++;
        if (currentLine >= TOTAL_HEIGHT)
        {
            currentLine = 0;
        }
    }
}

/**
 * @brief Restarts active frame line on interrupt trigger.
 */
void TIM3_IRQHandler(void)
{
    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;
        currentLine = 0;
    }
}

/**
 * @brief Initializes HSYNC, VSYNC and PIXEL signals
 */
void VGA_Init(void)
{
	HSYNC_Init();
	VSYNC_Init();
	PIXEL_Init();
	DATA_Init();
	DMA_Init();
}




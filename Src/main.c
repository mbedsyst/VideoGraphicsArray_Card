/**
 * @file main.c
 * @brief Source file for Application
 *
 * This file provides application logic for
 * interfacing the VGA Monitor
 */

#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>
#include <Tools/logger.h>
#include "VGA_Core.h"

int main(void)
{
	VGA_Init();

	while(1)
	{

	}

}

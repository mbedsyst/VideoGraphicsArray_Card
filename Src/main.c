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
		log_info("Hello World\n\r");
	}

}

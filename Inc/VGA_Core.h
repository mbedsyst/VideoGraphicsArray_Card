/**
 * @file VGA_Core.h
 * @brief Header file for VGA Core Functions
 *
 * This file provides declarations for functions
 * to initialize the synchronization signals and
 * transferring data to the monitor
 */

#ifndef VGA_CORE_H_
#define VGA_CORE_H_

#include "stm32f4xx.h"
#include "VGA_Draw.h"

/**
 * @brief Initializes HSYNC, VSYNC and PIXEL signals
 */
void VGA_Init(void);

#endif


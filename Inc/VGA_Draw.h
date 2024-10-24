/**
 * @file VGA_Draw.h
 * @brief Header file for VGA Drawing Functions
 *
 * This file provides declarations for functions
 * to draw pixel, characters and texts on the
 * VGA Monitor
 */

#ifndef VGA_DRAW_H_
#define VGA_DRAW_H_

/**
 * @brief Include standard integer types to be used.
 */
#include <stdint.h>
/**
 * @brief Include the font bitmap declarations
 */
#include "VGA_Font.h"

/**
 * @brief Number of lines in a single frame
 */
#define HEIGHT	800
/**
 * @brief Number of pixels in a single line
 */
#define WIDTH	600

/**
 * @brief Declaration of two dimensional frame buffer array
 */
extern uint8_t frameBuffer[HEIGHT][WIDTH];

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 */
void VGA_DrawPixel(int x, int y);

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 * @param Character ASCII character to be drawn
 */
void VGA_DrawChar(int x, int y, char Character);

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 * @param Text Pointer to character string
 */
void VGA_DrawText(int x, int y, const char *Text);

#endif /* VGA_DRAW_H_ */

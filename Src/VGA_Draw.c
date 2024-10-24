/**
 * @file VGA_Draw.c
 * @brief Source file for VGA Drawing Functions
 *
 * This file provides definitions for functions
 * to draw pixel, characters and texts on the
 * VGA Monitor
 */

#include "VGA_Draw.h"

/**
 * @brief Initializes frame buffer to zeroes
 *
 * This function can clear out the frame buffer
 * while initializing
 */
void VGA_InitFrameBuffer(void)
{
	for(int y = 0; y < HEIGHT; y++)
	{
		for(int x = 0; x < WIDTH; x++)
		{
			frameBuffer[y][x] = 0;
		}
	}
}

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 */
void VGA_DrawPixel(int x, int y)
{
	if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		frameBuffer[y][x] = 1;
	}
}

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 * @param Character ASCII character to be drawn
 */
void VGA_DrawChar(int x, int y, char Character)
{
    if (Character < 32 || Character > 126)
    	return; // Only handle printable ASCII characters
    const uint8_t *bitmap = font_8x8[Character - 32]; // Map the character to the bitmap
    for (int row = 0; row < 8; row++)
    { // Assuming 8x8 font size
        for (int col = 0; col < 8; col++)
        {
            if (bitmap[row] & (1 << col))
            {
                VGA_DrawPixel(x + col, y + row);
            }
        }
    }
}

/**
 * @brief Draws a pixel at coordinates (x, y)
 *
 * @param x Coordinate on the x-axis
 * @param y Coordinate on the y-axis
 * @param Text Pointer to character string
 */
void VGA_DrawText(int x, int y, const char *Text)
{
    int startX = x;
    while (*Text)
    {
        if (*Text == '\n')
        {
            y += 8; // Move to the next line (assuming 8 pixels per line height)
            x = startX; // Reset to start x position
        }
        else
        {
            VGA_DrawChar(x, y, *Text);
            x += 8; // Move to the next character position (assuming 8 pixels per character width)
        }
        Text++;
    }
}

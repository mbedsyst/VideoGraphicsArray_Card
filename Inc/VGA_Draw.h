#ifndef VGA_DRAW_H_
#define VGA_DRAW_H_

#define HEIGHT	600
#define WIDTH	480

extern uint8_t frameBuffer[HEIGHT][WIDTH];

void VGA_DrawPixel(int x, int y);
void VGA_DrawChar(int x, int y, char Character);
void VGA_DrawText(int x, int y, const char *Text);

#endif /* VGA_DRAW_H_ */

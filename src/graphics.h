#ifndef __graphics__h
#define __graphics__h

struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

void graphics_init();
void graphics_update();

void graphics_plot(int x, int y, Color color);
void graphics_draw_char(int index, int pos);
void graphics_clear(Color color);

void graphics_close();

#endif
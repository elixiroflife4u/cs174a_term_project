#ifndef _TEXT2D
#define _TEXT2D

#ifdef WIN32
#include <windows.h>
#endif

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/freeglut_ext.h"
#include "mat.h"
#include "vec.h"
#include "Angel.h"


class Text2D
{
	public:
		Text2D(void);
		void print_bitmap_string(void* font, char* s);
		void draw_stuff(char* s, vec4 color, GLfloat location_x, GLfloat location_y );

};

#endif
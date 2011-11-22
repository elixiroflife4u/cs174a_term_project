#include "Text2D.h"


Text2D::Text2D(void)
{}

void
Text2D::print_bitmap_string(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}


void
Text2D::draw_stuff(char* s, vec4 color, GLfloat location_x, GLfloat location_y )
{
   void* bitmap_fonts = GLUT_BITMAP_9_BY_15;

   char* bitmap_font_names = s;
     

   GLfloat x, y;

 
   /* Draw the strings, according to the current mode and font. */
   glColor4f(color.x, color.y, color.z, 0.0);
   x = location_x;
   y = location_y;
     
   glRasterPos2f(x, y);
   print_bitmap_string(bitmap_fonts, bitmap_font_names);
}
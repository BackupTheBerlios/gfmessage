
/*
 * gfmessage - gtk2 based on screen message displayer
 * Copyright (c) 2008 Nebil Reyhani
 *
 * This file is part of gfmesage.
 * Gfmessage is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Send your feedback or comments to: nebil.reyhani@gmail.com
 * http://mu.edu.tr/private/n_reyhani/gfmessage/
 *
 */

# include <stdlib.h>
# include <string.h>
# include <gtk/gtk.h>

#define TOP_LEFT                    101
#define TOP_RIGHT                   102
#define BOTTOM_LEFT                 103
#define BOTTOM_RIGHT                104
#define CENTER_CENTER               105

#define EXIT_ON_TIMEOUT             201
#define EXIT_ON_LEFT_CLICK          202
#define EXIT_ON_MOUSE_OVER          203
#define EXIT_ON_BUTTON_CLICK        204

#define SCROLLTEXT                  301
#define SCROLL_CHAOTIC              302
#define SCROLL_GRAVITY              303
#define SCROLL_NEWS                 304
#define COLOR_SLIDE                 305
#define COLOR_REVERSE               306
#define COLOR_CHANGE                307

struct OPTIONS_SET
{
   int alignment;
   int markup;
   int arg_text;
   int filename;
   int bg_color;
   int fg_color;
   int font;
   int font_size;
   int font_style;
   int text_alignment;
   int coordinates;
   int scroll_effect;
   int color_effect;
};

struct USER_OPTIONS
{
   int alignment;
   int delay;
   int exit_modus;
   char input_text[2000];
   gchar *utf8_text;
   char filename[256];
   GdkColor bg_color;
   GdkColor fg_color;
   char font[32];
   int font_size;
   PangoStyle font_style;
   PangoWeight font_weight;
   int text_alignment;
   int scroll_effect;
   int color_effect;
   char app_name[80];
   struct OPTIONS_SET set;
};

enum H_DIRECTION {H_NONE=0, RIGHT=1, LEFT=2};
enum V_DIRECTION {V_NONE=0, UP=1, DOWN=2};

struct WINDOW_GEOMETRY
{
   int x;
   int y;
   int t;                       /* Time dimension counted in refresh frequency unit */
   enum H_DIRECTION h_direction;
   enum V_DIRECTION v_direction;
   int width;
   int height;
   int screen_width;
   int screen_height;
};


struct USER_OPTIONS opt;

struct WINDOW_GEOMETRY wing;

void print_help_text(int, char *);
void get_defaults();
int get_opt(int, char **);

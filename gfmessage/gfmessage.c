
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

# include "gfmessage.h"


static GtkWidget *window = NULL;

int get_text()
{
gchar *text;
gsize length;
GError *error = NULL;
int i;


   if(opt.set.arg_text==1)
   {
      opt.utf8_text = g_locale_from_utf8 (opt.input_text, strlen(opt.input_text), NULL, NULL, &error);
      return 0;
   }
   else if(opt.set.filename==1)
   {
      if(g_file_get_contents(opt.filename, &text, &length, NULL)) 
      {
         if(opt.scroll_effect==SCROLL_NEWS)
         {
            for(i=0; i<strlen(text); i++)
            {
               if(text[i]=='\n')
                  text[i] = ' ';
            }
         }
         opt.utf8_text = g_locale_from_utf8 (text, length, NULL, NULL, &error);
         if(error!=NULL)
         {
            g_error_free(error);
            error = NULL;
            opt.utf8_text = g_convert (text, length,"UTF-8", "ISO-8859-1",  NULL, NULL, &error);
            if(error!=NULL)
            {
               fprintf (stderr, "%s: couldn't convert file %s to UTF-8\n", opt.app_name, opt.filename);
               g_error_free(error);
               return 1;
            }
         }
      }
      else
      {
         fprintf(stderr, "%s: unable to read file %s\n", opt.app_name, opt.filename);
         return 1;
      }
   }

   else 
   {
      /* If there is no text and no file, exit */
      printf("No message to display\nTry '%s --help' for more information.\n", opt.app_name);
      return 1;
   }
   return 0;
}


GSourceFunc sleep_n_go(GtkWidget *window)
{
   gtk_main_quit();
   return FALSE;
}


int randnumset[1200];

void scroll_text()
{
int i;

   if(opt.scroll_effect==SCROLL_CHAOTIC)
   {
      i = randnumset[wing.t%1200];
      if(i==0 || i==90)
      {
         wing.h_direction=wing.h_direction+1;
         if(wing.h_direction >= 3)
            wing.h_direction = 0;
      }
      if(i==90 || i==180)
      {
         wing.v_direction=wing.v_direction+1;
            if(wing.v_direction >= 3)
               wing.v_direction = 0;
      }
   }

   if(wing.v_direction==UP)
   {
      if(wing.y > 0)
         wing.y--;
      else
         wing.v_direction=DOWN;
   }
   if(wing.v_direction==DOWN)
   {
      if(wing.y < wing.screen_height-wing.height)
         wing.y++;
      else
         wing.v_direction=UP;
   }
   if(wing.h_direction==RIGHT)
   {
      if(wing.x < wing.screen_width-wing.width)
         wing.x++;
      else
         wing.h_direction=LEFT;
   }
   if(wing.h_direction==LEFT)
   {
      if(wing.x > 0)
         wing.x--;
      else
         wing.h_direction=RIGHT;
   }
   return;
}


int track[18000];

void gravity_effect()
{
int i, j;
int x;
int t=0;
float g=0.01;      /* Gravity = 1/100 pixel/win_time_unit^2 */
int ltrack[1800];
int total=0;

   if(wing.t==0)
   {
      x=wing.screen_height-wing.height;
      while(x>=0)
      {
         while(i<=x)
         {
            ltrack[t] = (double)1/2*g*(t*t);
            i=ltrack[t];
            t++;
         }
         /* We don't want to begin with spring movement, so we skip at the first step */
         if(total>0) 
         {
            for(j=t; j>0; j--)
               track[total++]=ltrack[j]+(wing.screen_height-wing.height-x);
         }
         for(j=0; j<t; j++)
            track[total++]=ltrack[j]+(wing.screen_height-wing.height-x);
         x=x-60;
         i=x;
         t=0;
      }
      for(i=total; i<18000; i++)
         track[i] = wing.screen_height-wing.height;
   }

   wing.y=track[wing.t%18000];

   return;
}


void set_news_frame()
{
GtkWidget *bwindow;
GtkWidget *bdrawing_area;

   bwindow=gtk_window_new(GTK_WINDOW_POPUP);

   g_signal_connect (bwindow, "destroy", G_CALLBACK (gtk_widget_destroyed), &bwindow);

   bdrawing_area = gtk_drawing_area_new ();

   gtk_container_add (GTK_CONTAINER (bwindow), bdrawing_area);

   gtk_widget_modify_bg (bdrawing_area, GTK_STATE_NORMAL, &opt.bg_color);

   gtk_window_move(GTK_WINDOW(bwindow), 0, wing.y);

   gtk_window_set_default_size (GTK_WINDOW (bwindow), wing.screen_width, wing.height);

   gtk_widget_show (bdrawing_area);

   gtk_widget_show (bwindow);

   return;
}



void news_effect()
{
int len;

   len = wing.screen_width + wing.width;

   wing.x = wing.screen_width - wing.t%len;

   return;
}


void change_color()
{
int i, j, k, t;
int a, b, c;

   if(opt.color_effect==COLOR_SLIDE)
   {
      if(wing.t%16==0)
      {
         t=wing.t/16;
         i=65536/8;
         j=65536/64;
         k=65536/512;

         a = t%8;
         b = t%64;
         c = t%512;

         opt.fg_color.red = a*i;
         opt.fg_color.green = b*j;
         opt.fg_color.blue = c*k;

         opt.bg_color.red = 65535 - opt.fg_color.red;
         opt.bg_color.green = 65535 - opt.fg_color.green;
         opt.bg_color.blue = 65535 - opt.fg_color.blue;
      }
   }

   if(opt.color_effect==COLOR_REVERSE)
   {
      if(wing.t%25==0)
      {
         opt.fg_color.red = 65535 - opt.fg_color.red;
         opt.fg_color.green = 65535 - opt.fg_color.green;
         opt.fg_color.blue = 65535 - opt.fg_color.blue;

         opt.bg_color.red = 65535 - opt.fg_color.red;
         opt.bg_color.green = 65535 - opt.fg_color.green;
         opt.bg_color.blue = 65535 - opt.fg_color.blue;
      }
   }

   if(opt.color_effect==COLOR_CHANGE)
   {
      i=wing.t%300;
      switch(i)
      {
         case 0: gdk_color_parse("red", &opt.fg_color); break;
         case 30: gdk_color_parse("pink", &opt.fg_color); break;
         case 60: gdk_color_parse("magenta", &opt.fg_color); break;
         case 90: gdk_color_parse("purpur", &opt.fg_color); break;
         case 120: gdk_color_parse("blue", &opt.fg_color); break;
         case 150: gdk_color_parse("darkblue", &opt.fg_color); break;
         case 180: gdk_color_parse("cyan", &opt.fg_color); break;
         case 210: gdk_color_parse("green", &opt.fg_color); break;
         case 240: gdk_color_parse("yellow", &opt.fg_color); break;
         case 270: gdk_color_parse("orange", &opt.fg_color); break;
      }
   }
   return;
}


gboolean refresh(GtkWidget *widget)
{

   if(opt.set.color_effect==1)
   {
      change_color();
/*
      gtk_widget_modify_bg (widget, GTK_STATE_NORMAL, &opt.bg_color);
*/
      gdk_window_invalidate_rect(widget->window, NULL, TRUE);
   }

   if(opt.set.scroll_effect==1)
   {
      if(opt.scroll_effect==SCROLL_GRAVITY)
         gravity_effect();
      else if(opt.scroll_effect==SCROLL_NEWS)
         news_effect();
      else
         scroll_text();

      gtk_window_move(GTK_WINDOW(window), wing.x, wing.y);
   }

   wing.t++;

   return TRUE;
}

static gboolean text_expose_event (GtkWidget *widget, GdkEventExpose *event, gpointer data)
{
PangoLayout *layout;
PangoRenderer *renderer;
PangoContext *context;
PangoFontDescription *desc;


   /* Get the default renderer for the screen, and set it up for drawing  */
   renderer = gdk_pango_renderer_get_default (gtk_widget_get_screen (widget));
   gdk_pango_renderer_set_drawable (GDK_PANGO_RENDERER (renderer), widget->window);
   gdk_pango_renderer_set_gc (GDK_PANGO_RENDERER (renderer), widget->style->black_gc);

   /* Create a PangoLayout, set the font and text */
   context = gtk_widget_create_pango_context (widget);
   layout = pango_layout_new (context);


   if(opt.set.markup==1)
      pango_layout_set_markup (layout, opt.utf8_text, -1);
   else
      pango_layout_set_text (layout, opt.utf8_text, -1);
   pango_layout_set_alignment(layout, opt.text_alignment);

   desc=pango_font_description_new();

   pango_font_description_set_family(desc, opt.font);
   pango_font_description_set_style(desc, opt.font_style);
   pango_font_description_set_weight(desc, opt.font_weight);
   pango_font_description_set_size(desc, opt.font_size*PANGO_SCALE);

   pango_layout_set_font_description (layout, desc);
   pango_font_description_free (desc);

   if(opt.set.markup!=1)
      gdk_pango_renderer_set_override_color (GDK_PANGO_RENDERER (renderer), PANGO_RENDER_PART_FOREGROUND, &opt.fg_color);

   pango_renderer_draw_layout (renderer, layout, 0, 0);

   /* Clean up default renderer, since it is shared */
   gdk_pango_renderer_set_override_color (GDK_PANGO_RENDERER (renderer), PANGO_RENDER_PART_FOREGROUND, NULL);

   gdk_pango_renderer_set_drawable (GDK_PANGO_RENDERER (renderer), NULL);
   gdk_pango_renderer_set_gc (GDK_PANGO_RENDERER (renderer), NULL);

   /* free the objects we created */
   g_object_unref (layout);
   g_object_unref (context);

   return FALSE;
}

void get_layout_size(GtkWidget *widget, int *width, int *height)
{
PangoLayout *layout;
PangoContext *context;
PangoFontDescription *desc; 

   context = gtk_widget_create_pango_context (widget);
   layout = pango_layout_new (context);

   if(opt.set.markup==1)
      pango_layout_set_markup (layout, opt.utf8_text, -1);
   else
      pango_layout_set_text (layout, opt.utf8_text, -1);

   desc=pango_font_description_new();

   pango_font_description_set_family(desc, opt.font);
   pango_font_description_set_style(desc, opt.font_style);
   pango_font_description_set_weight(desc, opt.font_weight);
   pango_font_description_set_size(desc, opt.font_size*PANGO_SCALE);

   pango_layout_set_font_description (layout, desc);
   pango_font_description_free (desc);
   pango_layout_get_size (layout, width, height);
   return;
}

void get_confirmation()
{
GtkWidget *bwindow;
GtkWidget *button;
int x, y;

   bwindow=gtk_window_new(GTK_WINDOW_POPUP);

   g_signal_connect (bwindow, "destroy", G_CALLBACK (gtk_widget_destroyed), &bwindow);

   button = gtk_button_new_with_label ("Press button to quit");

   g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (sleep_n_go), NULL);

   gtk_container_add (GTK_CONTAINER (bwindow), button);

   gtk_window_set_opacity(GTK_WINDOW(bwindow), 0);

   if(opt.alignment==TOP_LEFT)
   {
      x = wing.width-98;
      y = wing.height+4;
   }
   if(opt.alignment==TOP_RIGHT)
   {
      x = wing.x;
      y = wing.height+4;
   }
   if(opt.alignment==BOTTOM_LEFT)
   {
      x = wing.width-98;
      y = wing.y-26;
   }
   if(opt.alignment==BOTTOM_RIGHT)
   {
      x = wing.x;
      y = wing.y-26 ;
   }
   if(opt.alignment==CENTER_CENTER)
   {
      x = (wing.x-49)+(wing.width/2);
      y = wing.y+wing.height;
   }

   gtk_window_move(GTK_WINDOW(bwindow), x, y);

   gtk_widget_show (button);

   gtk_widget_show (bwindow);

   return;
}


int main(int argc, char* argv[])
{
GdkScreen *screen;
GtkWidget *drawing_area;
int layout_width;
int layout_height;
int i;

   gtk_init(&argc, &argv);

   if(get_opt(argc, argv)>0)
      return 1;

   if(get_text()>0)
      return 1;

   window = gtk_window_new (GTK_WINDOW_POPUP);
   gtk_window_set_screen (GTK_WINDOW (window), gtk_widget_get_screen (window));
   gtk_window_set_title (GTK_WINDOW (window), "You shouldn't see this!");
   g_signal_connect (window, "destroy", G_CALLBACK (gtk_widget_destroyed), &window);

   drawing_area = gtk_drawing_area_new ();
   gtk_container_add (GTK_CONTAINER (window), drawing_area);

   /* This overrides the background color from the theme */
   gtk_widget_modify_bg (drawing_area, GTK_STATE_NORMAL, &opt.bg_color);

   g_signal_connect (drawing_area, "expose-event", G_CALLBACK (text_expose_event), NULL);

   screen = gdk_screen_get_default();
   wing.screen_width = gdk_screen_get_width(screen);
   wing.screen_height = gdk_screen_get_height(screen);

   while(1)
   {
      get_layout_size(drawing_area, &layout_width, &layout_height);
      layout_height = layout_height/PANGO_SCALE;
      layout_width = layout_width/PANGO_SCALE;

      if(layout_width > wing.screen_width || layout_height > wing.screen_height)
      {
         if(opt.scroll_effect==SCROLL_NEWS || opt.font_size <= 8)
            break;
         else
            opt.font_size = opt.font_size - 2;
      }
      else
         break;
   }
   wing.width = layout_width;
   wing.height = layout_height;

   if(opt.alignment==TOP_LEFT || opt.alignment==BOTTOM_LEFT)
      wing.x = 4;

   if(opt.alignment==TOP_LEFT || opt.alignment==TOP_RIGHT)
      wing.y = 4;

   if(opt.alignment==TOP_RIGHT || opt.alignment==BOTTOM_RIGHT)
      wing.x = wing.screen_width-layout_width-4;

   if(opt.alignment==BOTTOM_LEFT || opt.alignment==BOTTOM_RIGHT)
      wing.y = wing.screen_height-layout_height-4;

   if(opt.alignment==CENTER_CENTER)
   {
      wing.x = (wing.screen_width-layout_width)/2;
      wing.y = (wing.screen_height-layout_height)/2;
   }

   gtk_window_move(GTK_WINDOW(window),wing.x, wing.y);

   gtk_window_set_default_size (GTK_WINDOW (window), layout_width, layout_height);

   if(opt.scroll_effect==SCROLL_NEWS)
      set_news_frame();

   if(opt.scroll_effect==SCROLL_CHAOTIC)
   {
      srand(time(NULL));
      for(i=0; i<1200; i++)
         randnumset[i] = rand()%270;
   }

   if(opt.set.scroll_effect || opt.set.color_effect)
      g_timeout_add(20, (GSourceFunc)refresh, drawing_area);

   switch(opt.exit_modus)
   {
      case EXIT_ON_TIMEOUT:
           g_timeout_add(1000*opt.delay, (GSourceFunc)sleep_n_go, NULL);
           break;
      case EXIT_ON_LEFT_CLICK:
           g_signal_connect (drawing_area, "button_press_event", G_CALLBACK (sleep_n_go), NULL);
           break;
      case EXIT_ON_MOUSE_OVER:
           g_signal_connect (drawing_area, "motion_notify_event", G_CALLBACK (sleep_n_go), NULL);
           break;
      case EXIT_ON_BUTTON_CLICK:
           get_confirmation(&wing);
           break;
      default: break;
   }

   if(opt.exit_modus==EXIT_ON_LEFT_CLICK || opt.exit_modus==EXIT_ON_MOUSE_OVER)
      gtk_widget_set_events (drawing_area, gtk_widget_get_events (drawing_area)
                  | GDK_LEAVE_NOTIFY_MASK | GDK_BUTTON_PRESS_MASK
                  | GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);

   if (!GTK_WIDGET_VISIBLE (window))
   {
      gtk_widget_show_all (window);
   }
   else
   {
      gtk_widget_destroy (window);
      window = NULL;
   }

   gtk_main();

   return 0;
 }

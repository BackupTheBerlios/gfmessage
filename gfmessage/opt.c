
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
# include "opt.h"

void print_help_text(int help_option, char *user_input)
{

   switch(help_option)
   {
      case HELP_INPUT_TEXT:
           printf("No message to display\nThe option '-t' requires a message text as argument.\nTry '%s --help' for more information.\n", opt.app_name);
           break;
      case HELP_INPUT_FILE:
           printf("No input file specified.\nThe option '-f' requires a file name as argument.\nTry '%s --help' for more information.\n", opt.app_name);
           break;
      case HELP_EXIT_MODUS:
           printf("Invalid exit modus: \"%s\".\nPossible values are: \"timeout\", \"mouseclick\", \"onmouseover\", and \"confirmation\".\nTry '%s --help' for more information.\n", user_input, opt.app_name);
           break;
      case HELP_TIMEOUT:
           printf("Invalid timeout value. Number of seconds for timeout must be specified.\nTry '%s --help' for more information.\n", opt.app_name);
           break;
      case HELP_ALIGNMENT:
           if(user_input==NULL || user_input[0]=='-')
              printf("Alignment is not specified.\n");
           else
              printf("Invalid alignment option: %s\n", user_input);
           printf("Available options: top_left, top_right, bottom_left, bottom_right, "
                  "center\nTry '%s --help' for more information.\n", opt.app_name);
           break;
      case HELP_TEXT_ALIGNMENT:
           printf("Invalid text alignment option: %s\n"
                  "Available options: left, right, center\n"
                  "Try '%s --help' for more information.\n", user_input, opt.app_name);
           break;
      case HELP_INVALID_OPTION:
           printf("%s: invalid option '%s'\nTry '%s --help' for more information\n",
                  opt.app_name, user_input, opt.app_name);
           break;
      case HELP_AMBIGUOUS_OPTION:
           printf("%s: ambiguous option '%s'\nTry '%s --help' for more information\n",
                  opt.app_name, user_input, opt.app_name);
           break;
      case HELP_COLOR_OPTION:
           printf("%s: specified color \"%s\" is invalid.\nTry '%s --help' for more "
                  "information.\n", opt.app_name, user_input, opt.app_name);
           break;
      case HELP_FONT_SIZE:
           printf("%s: specified font size \"%s\" is invalid.\nTry '%s --help' for more "
                  "information.\n", opt.app_name, user_input, opt.app_name);
           break;
      case HELP_FONT_STYLE_OPTION:
           printf("%s: specified font style \"%s\" is invalid.\nTry '%s --help' for "
                  "more information.\n", opt.app_name, user_input, opt.app_name);
           break;
      case HELP_COORDINATES:
           printf("%s: Invalid coordinates:\"%s\"\nTry '%s --help' for "
                  "more information.\n", opt.app_name, user_input, opt.app_name);
           break;
      case HELP_TEXT_EFFECT:
           printf("%s: Invalid text effect:\"%s\"\n"
                  "Available text effects: scroll, color.\n"
                  "Try '%s --help' for more information.\n",
                  opt.app_name, user_input, opt.app_name);
           break;
      case HELP_SCROLLTEXT:
           if(user_input==NULL || user_input[0]=='-')
              printf("%s: No scroll effect specified.\n", opt.app_name);
           else
              printf("%s: Invalid scroll text effect:\"%s\"\n", opt.app_name,user_input);
           printf("Available Scroll effects: vertical, horizontal, cross, chaotic, gravity, news.\nTry '%s --help' for more information.\n",opt.app_name);
           break;
      case HELP_COLOR_EFFECT:
           if(user_input==NULL || user_input[0]=='-')
              printf("%s: No color effect specified.\n", opt.app_name);
           else
              printf("%s: Invalid text color effect:\"%s\"\n",opt.app_name, user_input);
           printf("Available color effects: slide, reverse, change.\n"
                  "Try '%s --help' for more information.\n", opt.app_name);
           break;
      case HELP_VERSION:
           printf("%s\n", version);
           break;
      case HELP_SHORT:
           printf("Usage: %s %sTry '%s --help' for more information.\n",
                  opt.app_name, usage, opt.app_name);
           break;
      case HELP_FULL:
           printf("Usage: %s %s\n%s\n", opt.app_name, usage, help_text_full);
           break;
      default:
           printf("hadi\nbana\neyvallah!\n\n");
           break;
   }
   return;

}

void get_defaults()
{

   /* Default Settings */
   if(opt.set.alignment!=1 && opt.set.coordinates!=1)
      opt.alignment=BOTTOM_RIGHT;
   if(opt.exit_modus<=0)
   {
      opt.delay=4;
      opt.exit_modus=EXIT_ON_TIMEOUT;
   }
   if(opt.exit_modus==EXIT_ON_TIMEOUT && opt.delay<2)
      opt.delay=2;
   if(opt.set.bg_color!=1)
   {
      opt.bg_color.red   = 32765;
      opt.bg_color.green = 19273;
      opt.bg_color.blue  = 39782;
   }
   if(opt.set.fg_color!=1)
   {
      opt.fg_color.red   = 64535;
      opt.fg_color.green = 62174;
      opt.fg_color.blue  = 0;
   }
   if(opt.set.font!=1)
      sprintf(opt.font, "serif");
   if(opt.set.font_size!=1)
      opt.font_size=32;
   if(opt.set.font_style!=1)
      opt.font_style = PANGO_STYLE_ITALIC;
   if(opt.set.text_alignment!=1)
      opt.text_alignment=PANGO_ALIGN_RIGHT;

   return;
}

int get_opt(int argc, char **argv)
{
char str_buf[64];
int i=0, j=0, k=0;


   for(i=0; i<strlen(argv[0]); i++)
   {
      if(argv[0][i]=='/')
      {
         j=0;
         continue;
      }
      opt.app_name[j++]=argv[0][i];
   }
   opt.app_name[j]='\0';

   if(argc==1)
   {
      print_help_text(HELP_SHORT, NULL);
      return 1;
   }

   if(argv[1][0]!='-')
   {
      for(j=1; j<argc; j++) /* If no option is given, all arguments are text for output */
         sprintf(opt.input_text, "%s %s", opt.input_text, argv[j]);
      opt.set.arg_text=1;
      get_defaults();
      return 0;
   }

   for(i=1; i<argc; i++)
   {
      if(argv[i][0]=='-' && argv[i][1]!='-' && strlen(argv[i])>2)
      {
         print_help_text(HELP_AMBIGUOUS_OPTION, argv[i]);
         return 1;
      }
      if(argv[i][0]=='-')
      {
         switch(argv[i][1])
         {
            case 'f': if(argv[i+1]==NULL)
                      {
                         print_help_text(HELP_INPUT_FILE, NULL);
                         return 1;
                      }
                      else
                      {
                         sprintf(opt.filename, "%s", argv[i+1]); 
                         opt.set.filename=1;
                      }
                      break;
            case 't': if(argv[i+1]==NULL)
                      {
                         print_help_text(HELP_INPUT_TEXT, NULL);
                         return 1;
                      }
                      else
                      {
                         sprintf(opt.input_text, "%s", argv[i+1]);
                         opt.set.arg_text=1;
                      }
                      break;
            case 'a': if(argv[i+1]==NULL)
                      {
                         print_help_text(HELP_ALIGNMENT, NULL);
                         return 1;
                      }
                      else
                      {
                         if(strcmp(argv[i+1], "top_left")==0)
                            opt.alignment=TOP_LEFT;
                         else if(strcmp(argv[i+1], "top_right")==0)
                            opt.alignment=TOP_RIGHT;
                         else if(strcmp(argv[i+1], "bottom_left")==0)
                            opt.alignment=BOTTOM_LEFT;
                         else if(strcmp(argv[i+1], "bottom_right")==0)
                            opt.alignment=BOTTOM_RIGHT;
                         else if(strcmp(argv[i+1], "center")==0)
                            opt.alignment=CENTER_CENTER;
                         else
                         {
                            print_help_text(HELP_ALIGNMENT, argv[i+1]);
                            return 1;
                         }
                      }
                      opt.set.alignment=1;
                      break;
            case 'd':if(argv[i+1]==NULL)
                      {
                         print_help_text(HELP_TIMEOUT, NULL);
                         return 1;
                      }
                      else
                      {
                         opt.delay=atoi(argv[i+1]);
                         opt.exit_modus=EXIT_ON_TIMEOUT;
                      }
                      break;
            case 'b': opt.exit_modus=EXIT_ON_BUTTON_CLICK;
                      break;
            case 'c': opt.exit_modus=EXIT_ON_LEFT_CLICK;
                      break;
            case 'o': opt.exit_modus=EXIT_ON_MOUSE_OVER;
                      break;
            case '?': print_help_text(HELP_SHORT, NULL);
                      return 1;
            case 'v': print_help_text(HELP_VERSION, NULL);
                      return 1;
            case '-': if(strcmp(argv[i], "--help")==0)
                      {
                         print_help_text(HELP_FULL, NULL);
                         return 1;
                      }
                      if(strcmp(argv[i], "--version")==0)
                      {
                         print_help_text(HELP_VERSION, NULL);
                         return 1;
                      }
                      else if(strncmp(argv[i], "--exit-modus=", 13)==0) 
                      {
                         sscanf(argv[i], "--exit-modus=%s", str_buf);
                         if(strcmp(str_buf, "timeout")==0)
                         {
                            if(argv[i+1]==NULL)
                            {
                               print_help_text(HELP_TIMEOUT, NULL);
                               return 1;
                            }
                            else
                            {
                               opt.delay=atoi(argv[i+1]);
                               opt.exit_modus=EXIT_ON_TIMEOUT;
                            }
                         }
                         else if(strcmp(str_buf, "mouseclick")==0)
                            opt.exit_modus=EXIT_ON_LEFT_CLICK;
                         else if(strcmp(str_buf, "onmouseover")==0)
                            opt.exit_modus=EXIT_ON_MOUSE_OVER;
                         else if(strcmp(str_buf, "confirmation")==0)
                            opt.exit_modus=EXIT_ON_BUTTON_CLICK;
                         else
                         {
                            print_help_text(HELP_EXIT_MODUS, str_buf);
                            return 1;
                         }
                      }
                      else if(strncmp(argv[i], "--bgcolor=", 10)==0)
                      {
                         sscanf(argv[i], "--bgcolor=%s", str_buf);
                         if(gdk_color_parse(str_buf, &opt.bg_color))
                            opt.set.bg_color=1;
                         else
                         {
                            print_help_text(HELP_COLOR_OPTION, str_buf);
                            return 1;
                         }
                      }
                      else if(strncmp(argv[i], "--fgcolor=", 10)==0)
                      {
                         sscanf(argv[i], "--fgcolor=%s", str_buf);
                         if(gdk_color_parse(str_buf, &opt.fg_color))
                            opt.set.fg_color=1;
                         else
                         {
                            print_help_text(HELP_COLOR_OPTION, str_buf);
                            return 1;
                         }
                      }
                      else if(strncmp(argv[i], "--font=", 7)==0)
                      {
                         sscanf(argv[i], "--font=%s", opt.font);
                         opt.set.font=1;
                      }
                      else if(strncmp(argv[i], "--font-size=", 12)==0)
                      {
                         sscanf(argv[i], "--font-size=%d", &opt.font_size);
                         if(opt.font_size <= 6)
                         {
                            sscanf(argv[i], "--font-size=%s", str_buf);
                            print_help_text(HELP_FONT_SIZE, str_buf);
                            return 1;
                         }
                         opt.set.font_size=1;
                      }
                      else if(strncmp(argv[i], "--font-style=", 13)==0)
                      {
                         sscanf(argv[i], "--font-style=%s", str_buf);
                         if(strcmp(str_buf, "normal")==0)
                            opt.font_style=PANGO_STYLE_NORMAL;
                         else if(strcmp(str_buf, "italic")==0)
                            opt.font_style=PANGO_STYLE_ITALIC;
                         else if(strcmp(str_buf, "bold")==0)
                            opt.font_weight=PANGO_WEIGHT_BOLD;
                         else
                         {
                            print_help_text(HELP_FONT_STYLE_OPTION, str_buf);
                            return 1;
                         }
                         opt.set.font_style=1;
                      }
                      else if(strncmp(argv[i], "--text-alignment=", 17)==0)
                      {
                         sscanf(argv[i], "--text-alignment=%s", str_buf);
                         if(strcmp(str_buf, "left")==0)
                            opt.text_alignment=PANGO_ALIGN_LEFT;
                         else if(strcmp(str_buf, "center")==0)
                            opt.text_alignment=PANGO_ALIGN_CENTER;
                         else if(strcmp(str_buf, "right")==0)
                            opt.text_alignment=PANGO_ALIGN_RIGHT;
                         else
                         {
                            print_help_text(HELP_TEXT_ALIGNMENT, str_buf);
                            return 1;
                         }
                         opt.set.text_alignment=1;
                      }
                      else if(strncmp(argv[i], "--markup-text=", 14)==0)
                      {

                         if(strcmp(argv[i], "--markup-text=file")==0)
                         {
                            sprintf(opt.filename, "%s", argv[i+1]);
                            opt.set.markup=1;
                            opt.set.filename=1;
                         }
                         else
                         {
                            k=0;
                            for(j=14; j<strlen(argv[i]); j++)
                               opt.input_text[k++]=argv[i][j];
                            opt.input_text[k]='\0';
                            opt.set.arg_text=1;
                            opt.set.markup=1;
                         }
                      }
                      else if(strncmp(argv[i], "--coordinates=", 14)==0)
                      {
                         sscanf(argv[i], "--coordinates=%d:%d", &wing.x, &wing.y);

                         if(wing.x >= 0 && wing.y >= 0)
                            opt.set.coordinates=1;
                         else
                         {
                            sscanf(argv[i], "--coordinates=%s", str_buf);
                            print_help_text(HELP_COORDINATES, str_buf);
                            return 1;
                         }
                      }
                      else if(strncmp(argv[i], "--text-effect=", 14)==0)
                      {
                         sscanf(argv[i], "--text-effect=%s", str_buf);
                         if(strcmp(str_buf, "scroll")==0)
                         {
                            if(argv[i+1]==NULL)
                            {
                               print_help_text(HELP_SCROLLTEXT, NULL);
                               return 1;
                            }
                            opt.scroll_effect=SCROLLTEXT;
                            if(strcmp(argv[i+1], "vertical")==0)
                               wing.v_direction=DOWN;
                            else if(strcmp(argv[i+1], "horizontal")==0)
                               wing.h_direction=RIGHT;
                            else if(strcmp(argv[i+1], "cross")==0)
                            {
                               wing.v_direction=DOWN;
                               wing.h_direction=LEFT;
                            }
                            else if(strcmp(argv[i+1], "chaotic")==0)
                            {
                               opt.scroll_effect=SCROLL_CHAOTIC;
                               wing.v_direction=DOWN;
                               wing.h_direction=LEFT;
                            }
                            else if(strcmp(argv[i+1], "gravity")==0)
                               opt.scroll_effect=SCROLL_GRAVITY;
                            else if(strcmp(argv[i+1], "news")==0)
                               opt.scroll_effect=SCROLL_NEWS;
                            else
                            {
                               print_help_text(HELP_SCROLLTEXT, argv[i+1]);
                               return 1;
                            }
                            opt.set.scroll_effect=1;
                         }
                         else if(strcmp(str_buf, "color")==0)
                         {
                            if(argv[i+1]==NULL)
                            {
                               print_help_text(HELP_COLOR_EFFECT, NULL);
                               return 1;
                            }
                            if(strcmp(argv[i+1], "reverse")==0)
                               opt.color_effect=COLOR_REVERSE;
                            else if(strcmp(argv[i+1], "change")==0)
                               opt.color_effect=COLOR_CHANGE;
                            else if(strcmp(argv[i+1], "slide")==0)
                               opt.color_effect=COLOR_SLIDE;
                            else
                            {
                               print_help_text(HELP_COLOR_EFFECT, argv[i+1]);
                               return 1;
                            }
                            opt.set.color_effect=1;
                         }
                         else
                         {
                            print_help_text(HELP_TEXT_EFFECT, str_buf);
                            return 1;
                         }
                      }
                      else
                      {
                         print_help_text(HELP_INVALID_OPTION, argv[i]);
                         return 1;
                      }
                      break;
            default : print_help_text(HELP_INVALID_OPTION, argv[i]);
                      return 1;
         }
      }
   }
   get_defaults();
   return 0;
}

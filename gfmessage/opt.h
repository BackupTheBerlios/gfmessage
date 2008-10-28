
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

#define HELP_FULL                   600
#define HELP_SHORT                  601
#define HELP_INVALID_OPTION         602
#define HELP_AMBIGUOUS_OPTION       603
#define HELP_INPUT_TEXT             604
#define HELP_INPUT_FILE             605
#define HELP_EXIT_MODUS             606
#define HELP_TIMEOUT                607
#define HELP_ALIGNMENT              608
#define HELP_TEXT_ALIGNMENT         609
#define HELP_COLOR_OPTION           610
#define HELP_FONT_STYLE_OPTION      611
#define HELP_FONT_SIZE              612
#define HELP_COORDINATES            613
#define HELP_TEXT_EFFECT            614
#define HELP_SCROLLTEXT             615
#define HELP_COLOR_EFFECT           616
#define HELP_VERSION                617


const char version[] =
"gfmessage 0.1\n"
"Copyright (c) 2008 Nebil Reyhani \n"
"This is free software; see the source for copying conditions. There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n";

const char usage[] =
                 "[MESSAGE] [-t MESSAGE] [-f FILE] [-a ALIGNMENT]\n"
"                 [-d TIMEOUT VALUE] [-b|-c|-o] [-v|-?] [INPUT OPTIONS...]\n"
"                 [FORMAT OPTIONS...] [TEXT EFFECT OPTIONS...]\n\n"
"Gtk2 based on screen message displayer. Prints formatted text on screen.\n";


const char help_text_full[] =
" Input Options:\n"
"    -t MESSAGE               Display MESSAGE on screen.\n"
"    -f FILE                  Display message in FILE on screen.\n"
"    --markup-text=MESSAGE    Set message text as formatted in PANGO markup\n"
"                             language and display it on screen.\n"
"    --markup-text=file FILE  Set message text in FILE as formatted in PANGO\n"
"                             markup language and display it on screen.\n"
" Exit options:\n"
"    -d VALUE, --exit-modus=timeout VALUE\n"
"                             Exit after the number of seconds specified in\n"
"                             VALUE. The program will finish its job without\n"
"                             interaction.\n"
"    -c , --exit-modus=mouseclick\n"
"                             Exit after mouse click on window. There is no\n"
"                             button for interaction. The only way to exit is\n"
"                             to click somewhere on the window.\n"
"    -o , --exit-modus=onmouseover\n"
"                             Exit on mouse over. There is no button for\n"
"                             interaction. The only way to exit is to move\n"
"                             mouse pointer on somewhere over the window.\n"
"    -b , --exit-modus=confirmation\n"
"                             Exit after confirmation. Only if this option is\n"
"                             specified a button will be attached to the\n"
"                             message window for user interaction. The only\n"
"                             way to exit is then to click on the confirmation\n"
"                             button.\n"
" Window position:\n"
"    -a ALIGNMENT             Align window on screen. Possible values are:\n"
"                             top_left, top_right, bottom_left, bottom_right,\n"
"                             center\n"
"    --coordinates=x:y        Place window on screen coordinates x:y\n"
" Color options:\n"
"    --bgcolor=COLOR          Set background color. COLOR can be a standard\n"
"                             color name such like \"green\" or a hex value\n"
"                             like #FF3333.\n"
"    --fgcolor=COLOR          set foreground color. COLOR can be a standard\n"
"                             color name such like \"green\" or a hex value\n"
"                             like #FF3333.\n"
" Font options:\n"
"    --font=FONT              Set font to FONT. Posible values are font names\n"
"                             such like \"arial\" or font familie names like\n"
"                             \"serif\".\n"
"    --font-size=SIZE         Set font size to SIZE. If message window exceeds\n"
"                             screen size the font will be resized to fit on\n"
"                             screen.\n"
"    --font-style=STYLE       Set font style to STYLE. Possible values:\n"
"                             normal, italic, bold.\n"
" Text alignment options:\n"
"    --text-alignment=ALIGNMENT\n"
"                             Align message text on message window. Possible\n"
"                             values: left, right, center.\n"
" Text effect options:\n"
"    --text-effect=EFFECTGROUP EFFECT \n"
"                             Set text effect. Possible effectgroup values:\n"
"                             scroll, color.\n"
"    --text-effect=scroll EFFECT\n"
"                             Set scroll effect to EFFECT. Possible values:\n"
"                             vertical, horizontal, cross, chaotic, gravity,\n"
"                             news.\n"
"    --text-effect=color EFFECT\n"
"                             Set color effect to EFFECT. Possible values:\n"
"                             change, reverse, slide.\n"
" Info options:\n"
"    -?                       Print short help message.\n"
"    --help                   Print full help message.\n"
"    -v, --version            Print program version.\n\n"
" Default options:\n"
"                             -a bottom_right -d 4 --bgcolor=purple\n"
"                             --fgcolor=yellow --font=serif --font-size=32\n"
"                             --font-style=italic --text-alignment=right\n";


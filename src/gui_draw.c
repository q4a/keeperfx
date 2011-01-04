/******************************************************************************/
// Free implementation of Bullfrog's Dungeon Keeper strategy game.
/******************************************************************************/
/** @file gui_draw.c
 *     GUI elements drawing functions.
 * @par Purpose:
 *     On-screen drawing of GUI elements, like buttons, menus and panels.
 * @par Comment:
 *     None.
 * @author   Tomasz Lis
 * @date     20 Jan 2009 - 30 Jan 2009
 * @par  Copying and copyrights:
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 */
/******************************************************************************/
#include "gui_draw.h"

#include "globals.h"
#include "bflib_basics.h"
#include "bflib_memory.h"
#include "bflib_video.h"
#include "bflib_sprite.h"
#include "bflib_vidraw.h"
#include "bflib_sprfnt.h"
#include "bflib_guibtns.h"

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
char gui_textbuf[TEXT_BUFFER_LENGTH];
/******************************************************************************/
DLLIMPORT void _DK_draw_button_string(struct GuiButton *gbtn, const char *text);
DLLIMPORT int _DK_draw_text_box(char *text);
DLLIMPORT void _DK_draw_slab64k(long pos_x, long pos_y, long width, long height);
DLLIMPORT void _DK_draw_ornate_slab64k(long pos_x, long pos_y, long width, long height);
/******************************************************************************/

/******************************************************************************/

void draw_bar64k(long pos_x, long pos_y, long width)
{
  long body_end;
  long x;
  if (width < 72)
  {
    ERRORLOG("Bar is too small");
    return;
  }
  // Button opening sprite
  LbSpriteDraw(pos_x/pixel_size, pos_y/pixel_size, &button_sprite[1]);
  // Button body
  body_end = pos_x + width - 64;
  for (x = pos_x+32; x<body_end; x+=32)
  {
      LbSpriteDraw(x/pixel_size, pos_y/pixel_size, &button_sprite[2]);
  }
  LbSpriteDraw(body_end/pixel_size, pos_y/pixel_size, &button_sprite[2]);
  // Button ending sprite
  LbSpriteDraw((pos_x + width - 32)/pixel_size, pos_y/pixel_size, &button_sprite[3]);
}

void draw_lit_bar64k(long pos_x, long pos_y, long width)
{
  long body_end;
  long x;
  if (width < 32)
  {
    ERRORLOG("Bar is too small");
    return;
  }
  // opening sprite
  LbSpriteDraw(pos_x/pixel_size, pos_y/pixel_size, &button_sprite[7]);
  // body
  body_end = pos_x+width-64;
  for (x = pos_x+32; x<body_end; x+=32)
  {
      LbSpriteDraw(x/pixel_size, pos_y/pixel_size, &button_sprite[8]);
  }
  LbSpriteDraw(body_end/pixel_size, pos_y/pixel_size, &button_sprite[8]);
  // ending sprite
  LbSpriteDraw((pos_x+width-32)/pixel_size, pos_y/pixel_size, &button_sprite[9]);
}

void draw_slab64k(long pos_x, long pos_y, long width, long height)
{
  _DK_draw_slab64k(pos_x, pos_y, width, height);
}

void draw_ornate_slab64k(long pos_x, long pos_y, long width, long height)
{
  _DK_draw_ornate_slab64k(pos_x, pos_y, width, height);
}

/** Draws a string on GUI button.
 *  Note that the source text buffer may be damaged by this function.
 * @param gbtn Button to draw text on.
 * @param text Text to be displayed. The buffer may be changed by this function.
 *     It should have at least TEXT_BUFFER_LENGTH in size.
 */
void draw_button_string(struct GuiButton *gbtn, char *text)
{
    unsigned long flgmem;
    static unsigned char cursor_type = 0;
    //_DK_draw_button_string(gbtn, text);
    flgmem = lbDisplay.DrawFlags;
    if ((gbtn->gbtype == 5) && (gbtn == input_button))
    {
        const char *cursor_str;
        cursor_type++;
        if ((cursor_type & 0x02) != 0)
          cursor_str = " ";
        else
          cursor_str = "_";
        LbStringConcat(text,cursor_str,TEXT_BUFFER_LENGTH);
    }
    LbTextSetJustifyWindow(gbtn->scr_pos_x/pixel_size, gbtn->scr_pos_y/pixel_size, gbtn->width/pixel_size);
    LbTextSetClipWindow(gbtn->scr_pos_x/pixel_size, gbtn->scr_pos_y/pixel_size,
        gbtn->width/pixel_size, gbtn->height/pixel_size);
    lbDisplay.DrawFlags = 0x0100;
    LbTextDraw(4/pixel_size, ((gbtn->height - text_string_height(text))/2 - 4)/pixel_size, text);
    LbTextSetJustifyWindow(0/pixel_size, 0/pixel_size, 640/pixel_size);
    LbTextSetClipWindow(0/pixel_size, 0/pixel_size, MyScreenWidth/pixel_size, MyScreenHeight/pixel_size);
    LbTextSetWindow(0/pixel_size, 0/pixel_size, MyScreenWidth/pixel_size, MyScreenHeight/pixel_size);
    lbDisplay.DrawFlags = flgmem;
}

int draw_text_box(char *text)
{
  return _DK_draw_text_box(text);
}

void draw_gui_panel_sprite_left(long x, long y, long spridx)
{
  struct TbSprite *spr;
  if ((spridx <= 0) || (spridx > GUI_PANEL_SPRITES_COUNT))
    return;
  spr = &gui_panel_sprites[spridx];
  LbSpriteDraw(x/pixel_size, y/pixel_size, spr);
}

void draw_gui_panel_sprite_rmleft(long x, long y, long spridx, unsigned long remap)
{
  struct TbSprite *spr;
  if ((spridx <= 0) || (spridx > GUI_PANEL_SPRITES_COUNT))
    return;
  spr = &gui_panel_sprites[spridx];
  LbSpriteDrawRemap(x/pixel_size, y/pixel_size, spr, &pixmap.fade_tables[remap]);
}

void draw_gui_panel_sprite_ocleft(long x, long y, long spridx, TbPixel color)
{
  struct TbSprite *spr;
  if ((spridx <= 0) || (spridx > GUI_PANEL_SPRITES_COUNT))
    return;
  spr = &gui_panel_sprites[spridx];
  LbSpriteDrawOneColour(x/pixel_size, y/pixel_size, spr, color);
}

void draw_gui_panel_sprite_centered(long x, long y, long spridx)
{
  struct TbSprite *spr;
  if ((spridx <= 0) || (spridx > GUI_PANEL_SPRITES_COUNT))
    return;
  spr = &gui_panel_sprites[spridx];
  x -= ((spr->SWidth*(long)pixel_size) >> 1);
  y -= ((spr->SHeight*(long)pixel_size) >> 1);
  LbSpriteDraw(x/pixel_size, y/pixel_size, spr);
}

void draw_gui_panel_sprite_occentered(long x, long y, long spridx, TbPixel color)
{
  struct TbSprite *spr;
  if ((spridx <= 0) || (spridx > GUI_PANEL_SPRITES_COUNT))
    return;
  spr = &gui_panel_sprites[spridx];
  x -= ((spr->SWidth*(long)pixel_size) >> 1);
  y -= ((spr->SHeight*(long)pixel_size) >> 1);
  LbSpriteDrawOneColour(x/pixel_size, y/pixel_size, spr, color);
}

/******************************************************************************/
#ifdef __cplusplus
}
#endif

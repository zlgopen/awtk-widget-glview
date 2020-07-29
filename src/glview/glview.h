/**
 * File:   glview.h
 * Author: AWTK Develop Team
 * Brief:  glview
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-05-21 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#ifndef TK_GLVIEW_H
#define TK_GLVIEW_H

#include "base/widget.h"
#include "common/awtk_glx.h"

BEGIN_C_DECLS

/**
 * @class glview_t
 * @parent widget_t
 * @annotation ["scriptable","design","widget"]
 * GL View控件。
 *
 * 用TinyGL实现的软件OpenGL视图。
 * glview_t是[widget\_t](widget_t.md)的子类控件，widget\_t的函数均适用于glview_t控件。
 *
 * 在xml中使用"glview"标签创建GL View控件。如：
 *
 * ```xml
 * <glview x="c" y="50" w="24" h="140" value="-128" format="%.4lf" decimal_font_size_scale="0.5"/>
 * ```
 * 在c代码中使用函数glview_create创建GL View控件。如：
 *
 * ```c
 *  widget_t* glview = glview_create(win, 10, 10, 128, 128);
 * ```
 */
typedef struct _glview_t {
  widget_t widget;

  /*private*/
  bitmap_t* bitmap;
  AWTK_GLXContext* ctx;
} glview_t;

/**
 * @method glview_create
 * 创建glview对象
 * @annotation ["constructor", "scriptable"]
 * @param {widget_t*} parent 父控件
 * @param {xy_t} x x坐标
 * @param {xy_t} y y坐标
 * @param {wh_t} w 宽度
 * @param {wh_t} h 高度
 *
 * @return {widget_t*} 对象。
 */
widget_t* glview_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h);

/**
 * @method glview_cast
 * 转换为glview对象(供脚本语言使用)。
 * @annotation ["cast", "scriptable"]
 * @param {widget_t*} widget glview对象。
 *
 * @return {widget_t*} glview对象。
 */
widget_t* glview_cast(widget_t* widget);

#define WIDGET_TYPE_GLVIEW "glview"
#define GLVIEW(widget) ((glview_t*)(glview_cast(WIDGET(widget))))

END_C_DECLS

#endif /*TK_GLVIEW_H*/

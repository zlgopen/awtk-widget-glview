/**
 * File:   glview_register.c
 * Author: AWTK Develop Team
 * Brief:  glview register
 *
 * Copyright (c) 2020 - 2020 Guangzhou ZHIYUAN Electronics Co.,Ltd.
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

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "base/widget_factory.h"
#include "glview_register.h"
#include "glview/glview.h"

ret_t glview_register(void) {
  return widget_factory_register(widget_factory(), WIDGET_TYPE_GLVIEW, glview_create);
}

const char* glview_supported_render_mode(void) {
  return "OpenGL";
}

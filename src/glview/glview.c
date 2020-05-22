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

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "glview/glview.h"
#include "base/widget_vtable.h"

static ret_t glview_get_prop(widget_t* widget, const char* name, value_t* v) {
  glview_t* glview = GLVIEW(widget);
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  return RET_NOT_FOUND;
}

static ret_t glview_set_prop(widget_t* widget, const char* name, const value_t* v) {
  return_value_if_fail(widget != NULL && name != NULL && v != NULL, RET_BAD_PARAMS);

  return RET_NOT_FOUND;
}

static ret_t glview_on_destroy(widget_t* widget) {
  glview_t* glview = GLVIEW(widget);
  return_value_if_fail(widget != NULL && glview != NULL, RET_BAD_PARAMS);
  if (glview->ctx != NULL) {
    tkglDestroyContext(glview->ctx);
  }
  bitmap_destroy(glview->bitmap);

  return RET_OK;
}

static ret_t glview_ensure_context(widget_t* widget, canvas_t* c) {
  glview_t* glview = GLVIEW(widget);

  if (glview->ctx == NULL) {
    glview->ctx = tkglCreateContext(NULL, 0);
  }

  if (glview->bitmap == NULL) {
    bitmap_format_t format = lcd_get_desired_bitmap_format(c->lcd);
    glview->bitmap = bitmap_create_ex(widget->w, widget->h, 0, format);
  }

  if (glview->ctx != NULL) {
    tkglMakeCurrent(glview->bitmap, glview->ctx);
  }

  return (glview->bitmap != NULL && glview->ctx != NULL) ? RET_OK : RET_OOM;
}

static ret_t glview_paint_bitmap(widget_t* widget, canvas_t* c) {
  glview_t* glview = GLVIEW(widget);
  rect_t s = rect_init(0, 0, glview->bitmap->w, glview->bitmap->h);
  rect_t d = rect_init(0, 0, widget->w, widget->h);

  glFlush();
  tkglSwapBuffers(glview->bitmap);

  canvas_draw_image(c, glview->bitmap, &s, &d);

  return RET_OK;
}

static ret_t glview_on_event(widget_t* widget, event_t* e) {
  switch (e->type) {
    case EVT_BEFORE_PAINT: {
      paint_event_t* evt = (paint_event_t*)e;
      glview_ensure_context(widget, evt->c);
      break;
    }
    case EVT_AFTER_PAINT: {
      paint_event_t* evt = (paint_event_t*)e;
      glview_paint_bitmap(widget, evt->c);
      break;
    }
  }
  return RET_OK;
}

static const char* s_glview_properties[] = {NULL};

TK_DECL_VTABLE(glview) = {.size = sizeof(glview_t),
                          .type = WIDGET_TYPE_GLVIEW,
                          .parent = TK_PARENT_VTABLE(widget),
                          .clone_properties = s_glview_properties,
                          .persistent_properties = s_glview_properties,
                          .create = glview_create,
                          .set_prop = glview_set_prop,
                          .get_prop = glview_get_prop,
                          .on_event = glview_on_event,
                          .on_destroy = glview_on_destroy};

widget_t* glview_create(widget_t* parent, xy_t x, xy_t y, wh_t w, wh_t h) {
  glview_t* glview = GLVIEW(widget_create(parent, TK_REF_VTABLE(glview), x, y, w, h));

  return (widget_t*)glview;
}

widget_t* glview_cast(widget_t* widget) {
  return_value_if_fail(widget != NULL && widget->vt != NULL, NULL);

  if (widget->vt == TK_REF_VTABLE(glview)) {
    return widget;
  }

  return NULL;
}

#include "base/widget_factory.h"

ret_t glview_register(void) {
  widget_factory_t* f = widget_factory();
  widget_factory_register(f, WIDGET_TYPE_GLVIEW, glview_create);

  return RET_OK;
}

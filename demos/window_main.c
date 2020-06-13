#include "awtk.h"

extern void graphci_draw(widget_t* widget, int width, int height);

static ret_t on_close(void* ctx, event_t* e) {
  tk_quit();

  return RET_OK;
}

static ret_t on_paint(void* ctx, event_t* e) {
  widget_t* widget = WIDGET(e->target);
  
  graphci_draw(widget, widget->w, widget->h);

  return RET_OK;
}

/**
 * 初始化
 */
ret_t application_init(void) {
  glview_register();

  widget_t* win = window_open("main");
  widget_child_on(win, "glview", EVT_PAINT, on_paint, NULL);
  widget_child_on(win, "close", EVT_CLICK, on_close, NULL);

  return RET_OK;
}

/**
 * 退出
 */
ret_t application_exit(void) {
  log_debug("application_exit\n");
  return RET_OK;
}

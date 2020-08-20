#include "tkc/mem.h"
#include "base/bitmap.h"
#include "blend/image_g2d.h"
#include "base/pixel.h"

#include "awtk_glx.h"
#include "tinygl/zgl.h"

typedef struct {
  int xsize;
  int ysize;
  GLContext* gl_context;
} TinyAWTK_GLXContext;

AWTK_GLXContext tkglCreateContext(AWTK_GLXContext shareList, int flags) {
  TinyAWTK_GLXContext* ctx;

  if (shareList != NULL) {
    gl_fatal_error("No sharing available in TinyGL");
  }
  ctx = gl_malloc(sizeof(TinyAWTK_GLXContext));
  if (!ctx) return NULL;
  ctx->gl_context = NULL;

  return (AWTK_GLXContext)ctx;
}

void tkglDestroyContext(AWTK_GLXContext ctx1) {
  TinyAWTK_GLXContext* ctx = (TinyAWTK_GLXContext*)ctx1;
  if (ctx->gl_context != NULL) {
    glClose();
    gl_set_context(NULL);
  }
  gl_free(ctx);
}

/* resize the glx viewport : we try to use the xsize and ysize
   given. We return the effective size which is guaranted to be smaller */

static int glX_resize_viewport(GLContext* c, int* xsize_ptr, int* ysize_ptr) {
  TinyAWTK_GLXContext* ctx;
  int xsize, ysize;

  ctx = (TinyAWTK_GLXContext*)c->opaque;

  xsize = *xsize_ptr;
  ysize = *ysize_ptr;

  /* we ensure that xsize and ysize are multiples of 2 for the zbuffer. 
     TODO: find a better solution */
  xsize &= ~3;
  ysize &= ~3;

  if (xsize == 0 || ysize == 0) return -1;

  *xsize_ptr = xsize;
  *ysize_ptr = ysize;

  ctx->xsize = xsize;
  ctx->ysize = ysize;

  /* resize the Z buffer */
  ZB_resize(c->zb, NULL, xsize, ysize);
  return 0;
}

/* we assume here that drawable is a window */
int tkglMakeCurrent(AWTK_GLXDrawable drawable, AWTK_GLXContext ctx1) {
  TinyAWTK_GLXContext* ctx = (TinyAWTK_GLXContext*)ctx1;
  int mode = 0;
  int xsize = 0;
  int ysize = 0;
  ZBuffer* zb = NULL;

  if (gl_get_context() == NULL) {
    /* create the TinyGL context */

    xsize = drawable->w;
    ysize = drawable->h;

    /* currently, we only support 16 bit rendering */
    mode = ZB_MODE_5R6G5B;

    zb = ZB_open(xsize, ysize, mode, 0, NULL, NULL, NULL);
    return_value_if_fail(zb != NULL, 0);

    /* initialisation of the TinyGL interpreter */
    glInit(zb);
    ctx->gl_context = gl_get_context();
    ctx->gl_context->opaque = (void*)ctx;
    ctx->gl_context->gl_resize_viewport = glX_resize_viewport;

    /* set the viewport : we force a call to glX_resize_viewport */
    ctx->gl_context->viewport.xsize = -1;
    ctx->gl_context->viewport.ysize = -1;

    glViewport(0, 0, xsize, ysize);
  }

  if (ctx->gl_context != gl_get_context()) {
    ctx->gl_context = gl_get_context();
  }

  return 1;
}

static ret_t zbuffer_to_bitmap_rgb565(bitmap_t* drawable, TinyAWTK_GLXContext* ctx) {
  uint32_t size = tk_min(ctx->xsize * ctx->ysize * 2, drawable->w * drawable->h * 2);
  void* src = (void*)(ctx->gl_context->zb->pbuf);
  void* dst = (void*)bitmap_lock_buffer_for_write(drawable);
  memcpy(dst, src, size);
  bitmap_unlock_buffer(drawable);

  return RET_OK;
}

static ret_t zbuffer_to_bitmap_rgba8888(bitmap_t* drawable, TinyAWTK_GLXContext* ctx) {
  int i = 0;
  int j = 0;
  int w = 0;
  int h = 0;
  rgba_t* dst = (rgba_t*)bitmap_lock_buffer_for_write(drawable);
  pixel_rgb565_t* src = (pixel_rgb565_t*)(ctx->gl_context->zb->pbuf);
  h = tk_min(drawable->h, ctx->ysize);
  w = tk_min(drawable->w, ctx->xsize);

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      uint16_t v = *(uint16_t*)src;

      dst->r = src->r << 3;
      dst->g = src->g << 2;
      dst->b = src->b << 3;
      dst->a = 0xff;
      dst++;
      src++;
    }
  }
  bitmap_unlock_buffer(drawable);

  drawable->flags |= BITMAP_FLAG_CHANGED;

  return RET_OK;
}

void tkglSwapBuffers(AWTK_GLXDrawable drawable) {
  GLContext* gl_context = gl_get_context();
  TinyAWTK_GLXContext* ctx = (TinyAWTK_GLXContext*)gl_context->opaque;

  if (drawable->format == BITMAP_FMT_RGBA8888) {
    zbuffer_to_bitmap_rgba8888(drawable, ctx);
  } else if (drawable->format == BITMAP_FMT_BGR565) {
    zbuffer_to_bitmap_rgb565(drawable, ctx);
  } else {
    assert(!"not support");
  }

  return;
}

#ifndef AWTK_GLX_H
#define AWTK_GLX_H

#include "GL/gl.h"
#include "base/bitmap.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* AWTK_GLXContext;
typedef bitmap_t* AWTK_GLXDrawable;

AWTK_GLXContext tkglCreateContext(AWTK_GLXContext shareList, int flags);

void tkglDestroyContext(AWTK_GLXContext ctx);

int tkglMakeCurrent(AWTK_GLXDrawable drawable, AWTK_GLXContext ctx);

void tkglSwapBuffers(AWTK_GLXDrawable drawable);

#ifdef __cplusplus
}
#endif

#endif

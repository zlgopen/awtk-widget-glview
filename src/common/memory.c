/*
 * Memory allocator for TinyGL
 */
#include "tkc/mem.h"

/* modify these functions so that they suit your needs */

void gl_free(void* p) {
  if (p) {
    TKMEM_FREE(p);
    p = NULL;
  }
}

void* gl_malloc(int size) {
  return TKMEM_ALLOC(size);
}

void* gl_zalloc(int size) {
  return TKMEM_CALLOC(1, size);
}

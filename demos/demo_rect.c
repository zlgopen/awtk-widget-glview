/**
 * File:   main.c
 * Author: AWTK Develop Team
 * Brief:  main window sources
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
 * 2020-05-20 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "glview/glview.h"

static void reshape(int width, int height) {
  const float ar = (float)width / (float)height;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-ar, ar, -1.0, 1.0, 5.0, 100.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void graphci_draw(widget_t* widget, int width, int height) {
  reshape(width, height);

  glClearColor(0, 0.5, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_QUADS);
  glColor3f(1, 0, 0);
  glVertex3f(-1, -1, -10);

  glColor3f(1, 1, 0);
  glVertex3f(1, -1, -10);

  glColor3f(1, 1, 1);
  glVertex3f(1, 1, -10);
  
  glColor3f(0, 1, 1);
  glVertex3f(-1, 1, -10);
  glEnd();

}

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

static GLfloat Xrot, Xstep;
static GLfloat Yrot, Ystep;
static GLfloat Zrot, Zstep;
static GLfloat Step = 5.0;
static GLfloat Scale = 1.0;
static GLuint Object;

static GLuint make_object(void) {
  GLuint list;

  list = glGenLists(1);

  glNewList(list, GL_COMPILE);

  glBegin(GL_LINE_LOOP);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(1.0, 0.5, -0.4);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(1.0, -0.5, -0.4);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-1.0, -0.5, -0.4);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-1.0, 0.5, -0.4);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);

  glBegin(GL_LINE_LOOP);
  glVertex3f(1.0, 0.5, 0.4);
  glVertex3f(1.0, -0.5, 0.4);
  glVertex3f(-1.0, -0.5, 0.4);
  glVertex3f(-1.0, 0.5, 0.4);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(1.0, 0.5, -0.4);
  glVertex3f(1.0, 0.5, 0.4);
  glVertex3f(1.0, -0.5, -0.4);
  glVertex3f(1.0, -0.5, 0.4);
  glVertex3f(-1.0, -0.5, -0.4);
  glVertex3f(-1.0, -0.5, 0.4);
  glVertex3f(-1.0, 0.5, -0.4);
  glVertex3f(-1.0, 0.5, 0.4);
  glEnd();

  glEndList();

  return list;
}

void reshape(int width, int height) {
  glViewport(0, 0, (GLint)width, (GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 15.0);
  glMatrixMode(GL_MODELVIEW);
}

void draw(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();

  glTranslatef(0.0, 0.0, -10.0);
  glScalef(Scale, Scale, Scale);
  if (Xstep) {
    glRotatef(Xrot, 1.0, 0.0, 0.0);
  } else if (Ystep) {
    glRotatef(Yrot, 0.0, 1.0, 0.0);
  } else {
    glRotatef(Zrot, 0.0, 0.0, 1.0);
  }

  glCallList(Object);

  glPopMatrix();

  glFlush();
}

static ret_t on_idle(const idle_info_t* info) {
  Xrot += Xstep;
  Yrot += Ystep;
  Zrot += Zstep;

  if (Xrot >= 360.0) {
    Xrot = Xstep = 0.0;
    Ystep = Step;
  } else if (Yrot >= 360.0) {
    Yrot = Ystep = 0.0;
    Zstep = Step;
  } else if (Zrot >= 360.0) {
    Zrot = Zstep = 0.0;
    Xstep = Step;
  }

  widget_invalidate_force(WIDGET(info->ctx), NULL);

  return RET_REPEAT;
}

void init(void) {
  Object = make_object();
  glCullFace(GL_BACK);
  glDisable(GL_DITHER);
  glShadeModel(GL_FLAT);

  Xrot = Yrot = Zrot = 0.0;
  Xstep = Step;
  Ystep = Zstep = 0.0;
}

void graphci_draw(widget_t* widget, int width, int height) {
  static bool_t s_inited = FALSE;
  if (!s_inited) {
    init();
    s_inited = TRUE;
    reshape(width, height);
    widget_add_idle(widget, on_idle);
  }

  draw();
}

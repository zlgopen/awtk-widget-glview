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

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------
double rotate_y = 0;
double rotate_x = 0;

// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
static void draw_cube() {
  //  Clear screen and Z-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transformations
  glLoadIdentity();

  // Other Transformations
  // glTranslatef( 0.1, 0.0, 0.0 );      // Not included
  // glRotatef( 180, 0.0, 1.0, 0.0 );    // Not included

  // Rotate when user changes rotate_x and rotate_y
  glRotatef(rotate_x, 1.0, 0.0, 0.0);
  glRotatef(rotate_y, 0.0, 1.0, 0.0);

  // Other Transformations
  // glScalef( 2.0, 2.0, 0.0 );          // Not included

  //Multi-colored side - FRONT
  glBegin(GL_POLYGON);

  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5);  // P1 is red
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(0.5, 0.5, -0.5);  // P2 is green
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(-0.5, 0.5, -0.5);  // P3 is blue
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(-0.5, -0.5, -0.5);  // P4 is purple

  glEnd();

  // White side - BACK
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 1.0);
  glVertex3f(0.5, -0.5, 0.5);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(-0.5, 0.5, 0.5);
  glVertex3f(-0.5, -0.5, 0.5);
  glEnd();

  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 1.0);
  glVertex3f(0.5, -0.5, -0.5);
  glVertex3f(0.5, 0.5, -0.5);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(0.5, -0.5, 0.5);
  glEnd();

  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(0.0, 1.0, 0.0);
  glVertex3f(-0.5, -0.5, 0.5);
  glVertex3f(-0.5, 0.5, 0.5);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, -0.5, -0.5);
  glEnd();

  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 1.0);
  glVertex3f(0.5, 0.5, 0.5);
  glVertex3f(0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, -0.5);
  glVertex3f(-0.5, 0.5, 0.5);
  glEnd();

  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(1.0, 0.0, 0.0);
  glVertex3f(0.5, -0.5, -0.5);
  glVertex3f(0.5, -0.5, 0.5);
  glVertex3f(-0.5, -0.5, 0.5);
  glVertex3f(-0.5, -0.5, -0.5);
  glEnd();
}

// ----------------------------------------------------------
// specialKeys() Callback Function
// ----------------------------------------------------------
static ret_t glview_on_key_down(void* ctx, event_t* e) {
  key_event_t* evt = (key_event_t*)e;
  int key = evt->key;
  //  Right arrow - increase rotation by 5 degree
  if (key == TK_KEY_RIGHT) rotate_y += 5;

  //  Left arrow - decrease rotation by 5 degree
  else if (key == TK_KEY_LEFT)
    rotate_y -= 5;

  else if (key == TK_KEY_UP)
    rotate_x += 5;

  else if (key == TK_KEY_DOWN)
    rotate_x -= 5;

  widget_invalidate_force(WIDGET(e->target), NULL);

  return RET_OK;
}

static void reshape(int width, int height) {
  const float ar = (float)width / (float)height;

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, width, height);
}

void graphci_draw(widget_t* widget, int width, int height) {
  static bool_t s_inited = FALSE;
  if (!s_inited) {
    reshape(width, height);
    widget_on(widget, EVT_KEY_DOWN, glview_on_key_down, widget);

    s_inited = TRUE;
  }

  draw_cube();
}

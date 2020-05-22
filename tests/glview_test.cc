#include "glview/glview.h"
#include "gtest/gtest.h"

TEST(NumberLabel, props) {
  widget_t* w = glview_create(NULL, 10, 20, 30, 40);

  
  widget_destroy(w);
}

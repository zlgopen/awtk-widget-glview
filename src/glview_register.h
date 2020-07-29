/**
 * File:   glview_register.h
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

#ifndef TK_GLVIEW_REGISTER_H
#define TK_GLVIEW_REGISTER_H

#include "base/widget.h"

BEGIN_C_DECLS

/**
 * @method  glview_register
 * 注册GL View控件。
 *
 * @annotation ["global"]
 *
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败。
 */
ret_t glview_register(void);

END_C_DECLS

#endif /*TK_GLVIEW_REGISTER_H*/

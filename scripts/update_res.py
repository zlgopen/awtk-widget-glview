﻿#!/usr/bin/python

import os
import sys
import json
import collections

# try add AWTK_ROOT/scripts to system environment
AWTK_ROOT = '../awtk'
if os.path.exists(AWTK_ROOT):
    sys.path.append(AWTK_ROOT + '/scripts')
elif not os.path.isabs(AWTK_ROOT):
    AWTK_ROOT = '../' + AWTK_ROOT
    if os.path.exists(AWTK_ROOT):
        sys.path.append(AWTK_ROOT + '/scripts')

# AWTK_ROOT/scripts/update_res_common.py
import update_res_common as common


APP_ROOT = common.getcwd()
if APP_ROOT.endswith('scripts'):
    APP_ROOT = os.path.dirname(APP_ROOT)

os.chdir(APP_ROOT)

TOOLS_ROOT = None
AWTK_ROOT = common.join_path(APP_ROOT, AWTK_ROOT)
ASSETS_ROOT = common.join_path(APP_ROOT, 'design')
ASSET_C = common.join_path(APP_ROOT, 'res/assets.inc')
OUTPUT_ROOT = common.join_path(APP_ROOT, 'res/assets')
DPI = 'x1'
THEMES = []
IS_GENERATE_INC_RES = True
IS_GENERATE_INC_BITMAP = True
APP_THEME = 'default'

def use_theme_config_from_project_json():
    global DPI
    global THEMES
    global OUTPUT_ROOT
    global IS_GENERATE_INC_RES
    global IS_GENERATE_INC_BITMAP
    global APP_THEME

    project_json = common.join_path(APP_ROOT, 'project.json')
    if not os.path.exists(project_json):
        print('project.json is not exists.')
        return

    content = common.read_file(project_json)
    content = json.loads(content, object_pairs_hook=collections.OrderedDict)

    if not isinstance(content, dict):
        return

    if 'assets' not in content:
        return
    assets = content['assets']

    if 'outputDir' in assets:
        OUTPUT_ROOT = common.to_file_system_coding(assets['outputDir'])
        OUTPUT_ROOT = common.join_path(APP_ROOT, OUTPUT_ROOT+'/assets')

    if 'activedTheme' in assets:
        APP_THEME = assets['activedTheme']

    if 'themes' not in assets:
        return
    
    if len(assets['themes']) == 0:
        return

    if assets['const'] == 'resource_data':
        IS_GENERATE_INC_BITMAP = False
    else:
        IS_GENERATE_INC_RES = False

    if 'screenDPR' in assets:
        DPI = assets['screenDPR']

    for theme_name, theme_setting in assets['themes'].items():
        theme_name = common.to_file_system_coding(theme_name)
        color_format = theme_setting['lcd']['colorFormat']
        color_depth = theme_setting['lcd']['colorDepth']

        if color_format == 'MONO':
          imagegen_options = 'mono'
        elif color_format == 'BGR(A)':
            if color_depth == '16bit':
                imagegen_options = 'bgr565'
            else:
                imagegen_options = 'bgra'
        else:
            if color_depth == '16bit':
                imagegen_options = 'rgb565'
            else:
                imagegen_options = 'rgba'

        if IS_GENERATE_INC_BITMAP:
            font = theme_setting['fonts']
            config_dir = common.join_path(ASSETS_ROOT, theme_name+'/fonts/config')
            common.remove_dir(config_dir)
            common.make_dirs(config_dir)
            for font_name, font_setting in theme_setting['fonts'].items():
                for font_size, text in font_setting.items():
                    if font_size.isdigit():
                        font_name = common.to_file_system_coding(font_name)
                        font_size = common.to_file_system_coding(font_size)
                        filename = common.join_path(config_dir, font_name+'_'+font_size+'.txt')
                        common.write_file(filename, text)

        theme = {'name': theme_name, 'imagegen_options': imagegen_options, 'packaged': theme_setting['packaged']}
        if theme_name == 'default':
            THEMES.insert(0, theme)
        else:
            THEMES.append(theme)


def use_default_theme_config():
    global THEMES

    use_theme_config_from_project_json()

    if len(THEMES) == 0:
        if os.path.isdir(ASSETS_ROOT):
            for file in os.listdir(ASSETS_ROOT):
                if os.path.isdir(common.join_path(ASSETS_ROOT, file)):
                    if file == 'default':
                        THEMES.insert(0, file)
                    else:
                        THEMES.append(file)


use_default_theme_config()

if len(THEMES) == 0:
    print('Not found theme')
else:
    common.init(AWTK_ROOT, ASSETS_ROOT, THEMES, ASSET_C, OUTPUT_ROOT)
    if TOOLS_ROOT != None:
        common.set_tools_dir(TOOLS_ROOT)
    common.set_dpi(DPI)
    common.set_app_theme(APP_THEME)
    common.set_enable_generate_inc_res(IS_GENERATE_INC_RES)
    common.set_enable_generate_inc_bitmap(IS_GENERATE_INC_BITMAP)
    common.update_res()

    if isinstance(THEMES[0], dict):
        action = common.get_action()
        if action != 'clean' and action != 'web' and action != 'json' and action != 'pinyin':
            common.gen_res_c(False)

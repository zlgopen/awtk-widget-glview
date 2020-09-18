import os
import scripts.awtk_locator as locator

def dll_def_processor():
    content = ''
    with open('src/gl.def', 'r') as f:
        content = f.read()
    with open('src/glview.def', 'a') as f:
        f.write(content)

def getAppHelper(ARGUMENTS):
    locator.init(ARGUMENTS)

    from app_helper_base import AppHelperBase
    return AppHelperBase(ARGUMENTS)

helper = getAppHelper(ARGUMENTS)

APP_CPPPATH=[os.path.abspath('./src/tinygl')]
helper.set_dll_def('src/glview.def').set_dll_def_processor(dll_def_processor).set_libs(['glview']).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

SConscriptFiles = ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
SConscript(SConscriptFiles)

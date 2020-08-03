import os
import app_helper as app

def dll_def_processor():
    content = ''
    with open('src/gl.def', 'r') as f:
        content = f.read()
    with open('src/glview.def', 'a') as f:
        f.write(content)

ARGUMENTS['LCD'] = '800_480'
helper = app.Helper(ARGUMENTS);

APP_CPPPATH=[os.path.abspath('./src/tinygl')]
helper.set_dll_def('src/glview.def').set_dll_def_processor(dll_def_processor).set_libs(['glview']).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

CustomWidgetSConscriptFiles = []
SConscriptFiles = CustomWidgetSConscriptFiles + ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
SConscript(SConscriptFiles)

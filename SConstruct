import os
import app_helper as app

ARGUMENTS['LCD'] = '800_480'
helper = app.Helper(ARGUMENTS);

APP_CPPPATH=[os.path.abspath('./src/tinygl')]
helper.set_dll_def('src/glview.def').set_libs(['glview']).add_cpppath(APP_CPPPATH).call(DefaultEnvironment)

CustomWidgetSConscriptFiles = []
SConscriptFiles = CustomWidgetSConscriptFiles + ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
SConscript(SConscriptFiles)

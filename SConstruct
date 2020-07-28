import os
import sys
import platform
import shutil
import json


def getAwtkRoot():
  awtk_root = '../awtk'
  if not os.path.exists(awtk_root):
    dirnames = ['../awtk', '../../awtk', '../../../awtk']
    for dirname in dirnames:
      if os.path.exists(dirname):
        awtk_root = dirname
        break
  return os.path.abspath(awtk_root)


def isBuildShared():
  return 'WITH_AWTK_SO' in os.environ and os.environ['WITH_AWTK_SO'] == 'true' and BUILD_SHARED == 'true'


def copyAwtkSharedLib():
  if awtk.OS_NAME == 'Darwin':
    src = os.path.join(AWTK_ROOT, 'bin/libawtk.dylib')
    dst = os.path.join(APP_BIN_DIR, 'libawtk.dylib')
  elif awtk.OS_NAME == 'Linux':
    src = os.path.join(AWTK_ROOT, 'bin/libawtk.so')
    dst = os.path.join(APP_BIN_DIR, 'libawtk.so')
  elif awtk.OS_NAME == 'Windows':
    src = os.path.join(AWTK_ROOT, 'bin/awtk.dll')
    dst = os.path.join(APP_BIN_DIR, 'awtk.dll')
  else:
    print('not support ' + awtk.OS_NAME)
    return

  if not os.path.exists(src):
    print('Can\'t find ' + src + '. Please build AWTK before!')
  else:
    if not os.path.exists(APP_BIN_DIR):
        os.makedirs(APP_BIN_DIR)
    shutil.copy(src, dst)


def genIdlAndDef():
  idl_gen_tools = os.path.join(AWTK_ROOT, 'tools/idl_gen/index.js')
  dll_def_gen_tools = os.path.join(AWTK_ROOT, 'tools/dll_def_gen/index.js')

  cmd = 'node ' + '"' + idl_gen_tools + '"' + ' idl/idl.json ' + 'src'
  if os.system(cmd) != 0:
    print('exe cmd: ' + cmd + ' failed.')

  cmd = 'node ' + '"' + dll_def_gen_tools + '"'  + ' idl/idl.json ' + 'src/glview.def'
  if os.system(cmd) != 0 :
    print('exe cmd: ' + cmd + ' failed.')
  else:
    content = ''
    with open('src/gl.def', 'r') as f:
      content = f.read()
    with open('src/glview.def', 'a') as f:
      f.write(content)


def saveUsesSdkInfo():
  release_id = ''
  filename = os.path.join(AWTK_ROOT, 'component.json')
  if os.path.exists(filename):
    with open(filename, 'r') as f:
      component_content = f.read()
      if len(component_content) > 0:
        component_json = json.loads(component_content)
        if 'release_id' in component_json:
          release_id = component_json['release_id']
          if sys.version_info < (3, 0):
            release_id = release_id.encode('ascii')

  content  = '{\n' 
  content += '  "compileSDK": {\n'
  content += '    "awtk": {\n'
  content += '      "path": "' + AWTK_ROOT.replace('\\', '/') + '",\n'
  content += '      "release_id": "' + release_id + '",\n'
  content += '      "nanovg_backend": "' + awtk.NANOVG_BACKEND + '"\n'
  content += '    }\n'
  content += '  }\n'
  content += '}'

  if not os.path.exists(APP_BIN_DIR):
    os.makedirs(APP_BIN_DIR)

  filename = os.path.join(APP_BIN_DIR, 'uses_sdk.json')
  if sys.version_info < (3, 0):
    with open(filename, 'w') as f:
      f.write(content)
  else:
    with open(filename, 'w', encoding='utf8') as f:
      f.write(content)


AWTK_ROOT = getAwtkRoot()
sys.path.insert(0, AWTK_ROOT)
import awtk_config as awtk


BUILD_SHARED = 'true'
GEN_IDL_DEF = 'true'
LCD_WIDTH = '320'
LCD_HEIGHT = '480'
APP_DEFAULT_FONT = 'default'
APP_THEME = 'default'
APP_RES_ROOT = '../res'
APP_DEFAULT_LANGUAGE = 'zh'
APP_DEFAULT_COUNTRY = 'CN'

LCD = ARGUMENTS.get('LCD', '')
if len(LCD) > 0:
  wh = LCD.split('_')
  if len(wh) >= 1:
    LCD_WIDTH = wh[0]
  if len(wh) >= 2:
    LCD_HEIGHT = wh[1]

FONT = ARGUMENTS.get('FONT', '')
if len(FONT) > 0:
  APP_DEFAULT_FONT = FONT

THEME = ARGUMENTS.get('THEME', '')
if len(THEME) > 0:
  APP_THEME = THEME

LANGUAGE = ARGUMENTS.get('LANGUAGE', '')
if len(LANGUAGE) > 0:
  lan = LANGUAGE.split('_')
  if len(lan) >= 1:
    APP_DEFAULT_LANGUAGE = lan[0]
  if len(lan) >= 2:
    APP_DEFAULT_COUNTRY = lan[1]

SHARED = ARGUMENTS.get('SHARED', '')
if len(SHARED) > 0:
  if SHARED.lower().startswith('t'):
    BUILD_SHARED = 'true'
  else:
    BUILD_SHARED = 'false'

IDL_DEF = ARGUMENTS.get('IDL_DEF', '')
if len(IDL_DEF) > 0:
  if IDL_DEF.lower().startswith('t'):
    GEN_IDL_DEF = 'true'
  else:
    GEN_IDL_DEF = 'false'

APP_CPPPATH = []
APP_CCFLAGS = ' -DLCD_WIDTH=' + LCD_WIDTH + ' -DLCD_HEIGHT=' + LCD_HEIGHT + ' ' 
APP_CCFLAGS = APP_CCFLAGS + ' -DAPP_DEFAULT_FONT=\\\"' + APP_DEFAULT_FONT + '\\\" '
APP_CCFLAGS = APP_CCFLAGS + ' -DAPP_THEME=\\\"' + APP_THEME + '\\\" ' 
APP_CCFLAGS = APP_CCFLAGS + ' -DAPP_RES_ROOT=\\\"' + APP_RES_ROOT + '\\\" ' 
APP_CCFLAGS = APP_CCFLAGS + ' -DAPP_DEFAULT_LANGUAGE=\\\"' + APP_DEFAULT_LANGUAGE + '\\\" ' 
APP_CCFLAGS = APP_CCFLAGS + ' -DAPP_DEFAULT_COUNTRY=\\\"' + APP_DEFAULT_COUNTRY + '\\\" ' 

APP_ROOT    = os.path.normpath(os.getcwd())
APP_BIN_DIR = os.path.join(APP_ROOT, 'bin')
APP_LIB_DIR = os.path.join(APP_ROOT, 'lib')
APP_SRC     = os.path.join(APP_ROOT, 'src')

os.environ['APP_ROOT'] = APP_ROOT;
os.environ['BIN_DIR'] = APP_BIN_DIR;
os.environ['LIB_DIR'] = APP_LIB_DIR;
os.environ['APP_SRC'] = APP_SRC;
os.environ['BUILD_SHARED'] = str(isBuildShared())

print('BUILD_SHARED: ' + str(isBuildShared()))

APP_LINKFLAGS=''

CUSTOM_WIDGET_LIBS = []
APP_LIBS = CUSTOM_WIDGET_LIBS + ['glview']

CUSTOM_WIDGET_CPPPATH = []
APP_CPPPATH = CUSTOM_WIDGET_CPPPATH + [
  os.path.join(APP_ROOT, 'src'),
  os.path.join(APP_ROOT, 'src/tinygl'),
]

APP_TOOLS = None
if hasattr(awtk, 'TOOLS_NAME') and awtk.TOOLS_NAME != '' :
  APP_TOOLS = [awtk.TOOLS_NAME]

AWTK_CCFLAGS = awtk.CCFLAGS
if not isBuildShared() and hasattr(awtk, 'AWTK_CCFLAGS'):
  AWTK_CCFLAGS = awtk.AWTK_CCFLAGS

APP_LIBPATH = [APP_LIB_DIR]
AWTK_LIBS = awtk.LIBS
if isBuildShared():
  APP_LIBPATH = [APP_BIN_DIR, APP_LIB_DIR]
  AWTK_LIBS = awtk.SHARED_LIBS
  copyAwtkSharedLib()

  if awtk.OS_NAME == 'Linux':
    APP_LINKFLAGS += ' -Wl,-rpath=' + APP_BIN_DIR + ' '

if GEN_IDL_DEF == 'true':
  genIdlAndDef()

saveUsesSdkInfo()

if hasattr(awtk, 'CC'):
  DefaultEnvironment(
    CC=awtk.CC,
    CXX=awtk.CXX,
    LD=awtk.LD,
    AR=awtk.AR,
    STRIP=awtk.STRIP,
    TOOLS     = APP_TOOLS,
    CPPPATH   = awtk.CPPPATH + APP_CPPPATH,
    LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
    LIBS      = APP_LIBS + AWTK_LIBS,
    LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
    CCFLAGS   = APP_CCFLAGS + AWTK_CCFLAGS,
    TARGET_ARCH = awtk.TARGET_ARCH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)
else:
  DefaultEnvironment(
    TOOLS     = APP_TOOLS,
    CPPPATH   = awtk.CPPPATH + APP_CPPPATH,
    LINKFLAGS = awtk.LINKFLAGS + APP_LINKFLAGS,
    LIBS      = APP_LIBS + AWTK_LIBS,
    LIBPATH   = APP_LIBPATH + awtk.LIBPATH,
    CCFLAGS   = APP_CCFLAGS + AWTK_CCFLAGS,
    TARGET_ARCH = awtk.TARGET_ARCH,
    OS_SUBSYSTEM_CONSOLE=awtk.OS_SUBSYSTEM_CONSOLE,
    OS_SUBSYSTEM_WINDOWS=awtk.OS_SUBSYSTEM_WINDOWS)

CustomWidgetSConscriptFiles = []
SConscriptFiles = CustomWidgetSConscriptFiles + ['src/SConscript', 'demos/SConscript', 'tests/SConscript']
SConscript(SConscriptFiles)

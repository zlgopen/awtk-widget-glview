# 工具脚本

## 一、update\_res.py 资源生成工具

```
Usage: ./scripts/update_res.py action[clean|all|font|image|ui|style|string]
Example:
./scripts/update_res.py all
./scripts/update_res.py clean
./scripts/update_res.py style
```

参数action是必须的，其取值如下：

* clean 清除之前生成的资源文件。
* all 重新生成全部资源。
* font 仅生成有变化的字体资源。
* image 仅生成有变化的图像资源。
* ui 仅生成有变化的UI资源。
* style 仅生成有变化的主题资源。
* string 仅生成有变化的字符串资源。

如果需要修改资源生成工具的设置，修改 project.json 即可，设置参数的详细信息如下：

```json
{  
  ......
  "assets": {
    "activedTheme": "default",    // APP运行时的默认主题
    "outputDir": "res",           // 资源生成的输出目录
    "loadFrom": "any",
    "const": "resource_data",     // 资源的常量格式，有2个选项：
                                  //   “resource_data”表示原始数据，“bitmap_data”表示位图数据
    "screenDPR": "x1",            // LCD的设备像素比（DPR），有3个选项：x1，x2，x3
    "defaultLanguage": "zh",
    "defaultCountry": "CN",
    "themes": {                   // 项目的所有主题
      "default": {                // default主题
        "activedSystemBar": "system_bar",
        "activedBottomSystemBar": "system_bar_b",
        "packaged": true,         // 是否生成资源
        "fonts": {                // 主题包含的字体
          "default": {            // default字体
            "text": " !\"#$%&'()*+,-./0123456789:",     // “text”为TTF字体的保留字符，
            "18": " !\"#$%&'()*+,-./0123456789确定取消"  // “18”为Bitmap字体18字号的保留字符
          }
        },
        "lcd": {
          "width": "800",
          "height": "480",
          "colorDepth": "16bit",  // LCD的颜色深度
          "colorFormat": "BGR(A)" // LCD的颜色尺寸
        }
      }
    }
  },
  ......
}
```

> 也可以通过打开 Designer，进入 “项目设置” 页面进行设置。

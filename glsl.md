# GLSL

## 环境准备(基于 VSCode)

> 基本依据于：<https://zhuanlan.zhihu.com/p/151384233>

- Shader languages support for VS Code
- glsl-canvas // 可在 vscode 中跑着色器代码
- WebGL GLSL Editor // 待确认
- glsl linter
  - <https://github.com/KhronosGroup/glslang/releases> 下载相应版本，减压到文件目录
  - 配置：`"glsl-linter.validatorPath": "D:\\document\\Tools\\glslangValidator\\bin\\glslangValidator"`
- 配置代码提示：`User Snippets`，搜索 glsl 并打开 glsl.json 文件
  - <https://gist.github.com/lewislepton>，复制内容至 glsl.json

# VS Code C/C++ 代码格式化

基于 VSC 的插件 clang-foramt。

* 安装 clang-format extension
* `ctrl + shift + p`，打开用户偏好设置，找到 `clang-format`
* 配置 `c_cpp: clang_format_style` 为 `file`，即调用在 `workspace` 中的 `.clang-format`
* `c_cpp: clang_format_fallback Style`，若上面为 `file`，但本工作环境中无 `.clang-format` 文件，按照此规则处理
* 设置 `"clang-format.executable": "C:\\Program Files\\LLVM\\bin\\clang-format.exe"`


在 powershell 中输入
```cmd
clang-format -style=llvm -dump-config > .clang-format
```
以此来生成一个 `.clang-format` 模板，由此自定义自己想要的 `.clang-format` 配置，即自定义如何格式化 c/c++ 代码。将该 `.clang-format` 配置文件复制到对应的 workspace。



## 可能遇到的问题

**注意事项**：
1. 每一个 workspace 都需要一份单独的 `.clang-format` 配置文件，当然也有其他方法实现多个工作环境一个配置文件，但是较为麻烦而且不稳定，因为官方不支持这样做。

**问题解决**：
1. 有时候，代码格式化突然失效。
这是因为 `clang-format.exe` 有时候会更新，此时其名字或者说 clang-format 的执行路径发生了改变。手动更改 clang-format 的执行路径即可。
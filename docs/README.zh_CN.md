# LC2KiCad

![LC2KiCad Logo。此Logo以CC-BY-SA 3.0协议授权。](./LC2KiCad-Logo.svg)

---

## 总览

LC2KiCad 是一个可以把EasyEDA的文档（或又称LCEDA，即立创EDA，因为该软件事实上为LCSC，即立创商城所有）转换为KiCad 5.0版本（或更高）文档的软件。该软件完全免费，它的主要部分在GNU LGPL v3协议授权下分发。

**LC2KiCad的主体目前还处于开发中，它的许多功能目前都不可用。***

---

## 编译本程序

### 依赖库

LC2KiCad需要使用C++的标准库组件。编译过程需要使用GCC和CMake。其他的编译器并未经过测试。如需克隆本仓库，Git也是需要使用的组件之一。

### Linux

```shell
git clone https://github.com/rigoligorlc/lc2kicad.git
cd lc2kicad
mkdir build && cd build
cmake .. && make
```

编译出的二进制文件被存放在 `lc2kicad/build/`

### Windows

您需要让Git，CMake和MinGW正常工作，且确保它们的所在目录都加入了PATH环境变量。编译使用的命令和Linux基本相同。

```
git clone https://github.com/rigoligorlc/lc2kicad.git
cd lc2kicad
mkdir build && cd build
cmake .. && mingw32-make -G "MinGW Makefiles"
```
MSVC编译器和Ninja也可使用。可以用CMakeLists.txt将本项目导入Visual Studio，也可直接使用CMake进行编译。
### macOS

本程序没有在macOS下编译的文档。但操作应该与Linux相似。安装gcc和cmake后可以尝试与Linux类似的方法编译。

---

## 如何使用LC2KiCad

### 重要信息！

- **根据LC2KiCad的设计，本程序只有CLI（命令行界面）可用，且原作者并没有加入GUI的意图。**

- **LC2KiCad目前只是一个半成品，这里列出的操作随时可能变更。本程序也可能无法按照该部分的说明工作。本软件没有任何使用保障。**

  

### 可用命令
- `lc2kicad`  不传递任何参数时，会显示帮助信息。
- `lc2kicad -h` 或 `lc2kicad --help` 显示帮助信息。
- `lc2kicad -V` 或 `lc2kicad --version` 显示该程序的版本号及关于信息。
- `lc2kicad 文件1 [文件2] ...` 转换指定的文件。

### 未实现命令
- `-o 输出目录` 指定转换后输出文件的目录。
- `-f 配置文件` 不使用程序标准位置储存的配置文件而使用用户指定的配置文件。配置文件内含默认输出目录，默认解析器参数以及其他设定。
- `-a 解析器参数` 指定解析器参数；解析器参数可进行兼容性调整、特性开关以及其他对序列化器和去序列化器的设定。

### 计划中的语法
- `--pipe` 从输入流读取文件直到遇到EOF，并将转换结果从输出流输出。
- `-p ... 文件1 文件2 [文件3] ...` 将所有指定文件视作单个项目的所有单独文件。允许多张原理图（互通），但仅文件列表最后一个PCB会被视作与项目关联的电路板。
- `-S ... 文件1 文件2 [文件3] ...` 把所有指定文件看作单个符号的字符号，输出含多个子库的单个符号库文件。

如果LC2KiCad无法打开一个可以写入的新文件，它会将所有的内容写入标准输出流。

**此部分仍待填写完整**

---

## 许可证

LC2KiCad的核心组件以GNU较宽松公共许可证（LGPL）v3授权。

LC2KiCad使用了RapidJSON，其许可证为MIT许可证。

---

### 重要信息！

我们**禁止**您使用该程序的二进制发行版本非法转换他人的文档。

我们**禁止**您在EasyEDA（立创EDA）用户使用协议允许的情形之外使用该程序的二进制发行版本。

---

© Copyright RigoLigoRLC 2020.

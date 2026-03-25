# LeetCode Practice

基于 C 语言的 LeetCode 刷题记录，使用 CMake 构建，支持格式化、静态检查、运行时分析以及单元测试。

使用到的第三方库：

- [Uthash 2.3.0](http://github.com/troydhanson/uthash)
- [GoogleTest 1.17.0](https://github.com/google/googletest)

## 项目结构

```
leetcode-practice/
├── CMakeLists.txt           # CMake 构建配置
├── CMakePresets.json        # CMake 预设配置
├── CPPLINT.cfg              # cpplint 静态检查配置
├── .clang-format            # clang-format 格式化配置
├── .editorconfig            # 编辑器配置
├── cmake/                   # CMake 脚本目录
│   ├── build.cmake          # 构建相关配置
│   ├── deps.cmake           # 第三方依赖管理
│   ├── format.cmake         # 代码格式化脚本
│   ├── lint.cmake         	 # 静态检查脚本
│   ├── runtime_check.cmake  # 运行时检查脚本
│   ├── export_install.cmake # 安装导出配置
│   ├── config/              # 配置文件
│   └── modules/             # CMake 模块
├── src/                     # 源代码目录
│   └── include/             # 头文件目录
├── test/                    # 单元测试目录
└── out/                     # 构建输出目录
    ├── build/               # CMake 构建中间文件
    ├── install/             # 安装输出
    └── dist/                # 分发包
```

## 格式化支持（可选）

若要支持代码和 CMake 脚本的格式化，请先安装 clang-format 和 cmake-format。如果不需要可以在 `CMakeLists.txt` 中关闭 `ENABLE_FORMAT` 选项。

```cmake
option(ENABLE_FORMAT OFF)
```

## 快速开始

1. 配置

   ```shell
   cmake --preset=debug
   ```

2. 构建

   ```shell
   cmake --build --preset=debug
   ```

3. 测试

   ```shell
   ctest --preset=debug
   ```

4. 打包

   ```shell
   cpack --preset=debug
   ```

> [!NOTE]
>
> 若需要配置特定于本机的配置，可以创建 `CMakeUserPresets.json` 文件来继承 `CMakePresets.json` 中的配置，这个文件不会被 Git 跟踪。例如配置指定的编译器路径：
>
> ```json
> {
>   "version": 8,
>   "configurePresets": [
>     {
>       "name": "only-your-system",
>       "inherits": "debug",  // 继承自 CMakePresets.json
>       "cacheVariables": {
>         "CMAKE_C_COMPILER": "/path/to/your/c/compiler",
>         "CMAKE_CXX_COMPILER": "/path/to/your/cxx/compiler"
>       }
>     }
>   ]
> }
> ```

## 代码模版快速生成

若要快速创建一个题目，例如 LeetCode 第一题 TwoSum，可以在命令行中执行 CMake 脚本：

```shell
cmake -DTEMPLATE=two_sum -P cmake/template_generator.cmake
```

这将在指定的位置中生成文件：

```
├── test/
│   └── two_sum_test.cpp      # 测试文件
└── src/
    ├── two_sum.c             # 源文件
    └── include/
        └── leetcode/
            └── two_sum.h     # 头文件
```


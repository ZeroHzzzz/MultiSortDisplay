# MultiSortDisplay

## Description

数据结构课设：排序算法的控制台可视化程序

# Usage

1. 克隆本仓库：

    ```bash
    git clone https://github.com/ZeroHzzzz/MultiSortDisplay.git
    cd MultiSortDisplay
    ```

2. 创建构建目录：

    为了保持源代码目录的整洁，建议在项目根目录下创建一个单独的构建目录：

    ```bash
    mkdir build
    cd build
    ```

3. 运行 CMake 配置项目：

    在构建目录中，使用 CMake 配置项目：

    ```bash
    cmake ..
    ```

    如果你有特殊的构建选项或要设置编译器，可以使用 `-D` 标志传递参数。例如：

    ```bash
    cmake -DCMAKE_BUILD_TYPE=Release ..
    ```

4. 构建项目：

    配置完成后，运行以下命令构建项目：

    ```bash
    make
    ```

    或者，如果你使用的是多核系统，可以使用 `-j` 参数加速构建过程：

    ```bash
    make -j$(nproc)
    ```

5. 安装项目（可选）：

    如果项目需要安装，可以使用以下命令：

    ```bash
    sudo make install
    ```

### 清理构建

如果你想清理构建目录，可以使用以下命令：

```bash
make clean
```

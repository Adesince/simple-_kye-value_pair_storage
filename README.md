# 简易键值对存储
## 一、实验目的
1. 熟悉C/C++语法
2. 熟悉GNU/Linux系统下C/C++编程，编译与链接过程
3. 熟悉CMake/Makefile构建方式
4. 使用GDB进行Debug
## 二、实验内容
1. 使用getopt解析Unix / POSIX样式的命令行选项
2. 使用readline实现具有命令行界面的交互
3. 程序可以存储与查询键值对
4. 程序可以使用命令行参数读取文本文件中的键值对
5. 程序可以在命令行交互界面中增加与查询键值对，参考：mysql
6. 程序可以使用命令行参数实现交互界面中相同的功能
7. 使用CMake或者Makefile构建
8. 需要有存储与查询的测试
9. 使用Github Action完成测试（可选）
## 四、 实验要求：
1. 时间：一周
2. 产出：源码，测试程序或者脚本
3. 报告：无pre，需要演示
## 五、计划
1. 使用getopt解析参数实现键值对的增删改查
    - -a add a key-value
    - -d delete a key-value
    - -f choose a file to storage key-value
    - -c change a key-value
    - -q query a key-value
2. 使用readline进行命令行交互
    - add add a key-value
    - query query a key-value
    - chage change a key-value
    - del delete a key-value
3. 使用Makefile构建项目
4. 使用Github Action 完成测试
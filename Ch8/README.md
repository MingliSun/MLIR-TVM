# MLIR+TVM project

本项目为融合MLIR和TVM的一个简单demo，前端采用[MLIR教程](https://github.com/tensorflow/mlir/blob/master/g3doc/Tutorials/Toy/Ch-1.md)的Toy语言(命名是一件很难的事)，将Toy进行词法分析、语法分析（递归下降）、语义检查，生成MLIR。MLIR中使用了Dialect概念，在上一步生成的MLIR是Toy Dialect。然后同一Dialect中进行优化，包括基于语言本身的优化，Shape Inference,inlining,DeadFunctionElimination,CSE等。接下来我们利用已经优化的Toy Dialect转化成Relay Dialect。在这里Toy Dialect和Relay Dialect 抽象程度几乎一致，所以看上去是一个平行转换。得到Relay Dialect后写一个分析pass 来实现Relay Dialect到 Relay API的转化（不像教程中从LLVM Dialect到LLVM IR的转化）。

## 如何build

本项目基于MLIR项目，生成的python代码需要TVM环境，同时安装LLVM和cuda，cudnn

此demo基于Ubuntu开发，Window 也可使用。以下以Ubuntu为例介绍build 方法

* clone MLIR源码并将该demo复制到mlir文件夹下.../mlir/examplees/toy

  ``` sh
  git clone https://github.com/llvm/llvm-project.git
  git clone https://github.com/tensorflow/mlir llvm-project\llvm\projects\mlir
  git clone
  gedit llvm-project\llvm\projects\mlir\test\CMakeLists.txt #Then add "toyc-ch8" in the proper position
  mkdir llvm-project\build
  cd llvm-project\build
  cmake ..\llvm -G "Visual Studio 15 2017 Win64" -DLLVM_BUILD_EXAMPLES=ON -DLLVM_TARGETS_TO_BUILD="host" -DCMAKE_BUILD_TYPE=Release -Thost=x64
  cmake --build . --target check-mlir
  ```

* 您可以直接使用 Linux下的[执行文件]()

* TVM环境的安装请自行寻找教程

  ## 如何使用

  -   生成AST

    ``./toyc-ch8 test/codegen.toy -emit=ast``

  -  生成MLIR

    `./toyc-ch8 test/codegen.toy -emit=mlir `

  - 生成优化后的MLIR

    `./toyc-ch8 test/codegen.toy -emit=mlir -opt`

  - 转化为Relay Dialect

    `./toyc-ch8 test/codegen.toy -emit=mlir-relay `

  -  转化为 Relay API

    `./toyc-ch8 test/codegen.toy -emit=relay `

  -  对上一步重定向生成的python文件

    `python3 relay.py`
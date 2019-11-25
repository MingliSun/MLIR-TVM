

module {
  func @multiply_transpose(%arg0: tensor<*xf64>, %arg1: tensor<*xf64>) -> tensor<*xf64> {
    %0 = "toy.transpose"(%arg0) : (tensor<*xf64>) -> tensor<*xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":5:10)
    %1 = "toy.transpose"(%arg1) : (tensor<*xf64>) -> tensor<*xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":5:25)
    %2 = "toy.mul"(%0, %1) : (tensor<*xf64>, tensor<*xf64>) -> tensor<*xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":5:25)
    "toy.return"(%2) : (tensor<*xf64>) -> () loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":5:3)
  } loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":4:1)
  func @main() {
    %0 = "toy.constant"() {value = dense<[[1.000000e+00, 2.000000e+00, 3.000000e+00], [4.000000e+00, 5.000000e+00, 6.000000e+00]]> : tensor<2x3xf64>} : () -> tensor<2x3xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":9:17)
    %1 = "toy.reshape"(%0) : (tensor<2x3xf64>) -> tensor<2x3xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":9:3)
    %2 = "toy.constant"() {value = dense<[1.000000e+00, 2.000000e+00, 3.000000e+00, 4.000000e+00, 5.000000e+00, 6.000000e+00]> : tensor<6xf64>} : () -> tensor<6xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":10:17)
    %3 = "toy.reshape"(%2) : (tensor<6xf64>) -> tensor<2x3xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":10:3)
    %4 = "toy.generic_call"(%1, %3) {callee = @multiply_transpose} : (tensor<2x3xf64>, tensor<2x3xf64>) -> tensor<*xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":11:11)
    %5 = "toy.generic_call"(%3, %1) {callee = @multiply_transpose} : (tensor<2x3xf64>, tensor<2x3xf64>) -> tensor<*xf64> loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":12:11)
    "toy.print"(%5) : (tensor<*xf64>) -> () loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":13:3)
    "toy.return"() : () -> () loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":8:1)
  } loc("/home/sun/llvm-project/llvm/projects/mlir/test/Examples/Toy/Ch2/codegen.toy":8:1)
} loc(unknown)

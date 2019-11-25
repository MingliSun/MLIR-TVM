add_subdirectory(include)

set(LLVM_LINK_COMPONENTS
  Core
  Support
  )

set(LLVM_TARGET_DEFINITIONS mlir/ToyCombine.td)
mlir_tablegen(ToyCombine.inc -gen-rewriters "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
add_public_tablegen_target(ToyCh8CombineIncGen)

add_toy_chapter(toyc-ch8
  toyc.cpp
  parser/AST.cpp
  mlir/MLIRGen.cpp
  mlir/Dialect.cpp
  mlir/RelayDialect.cpp
  mlir/DeadFunctionEliminationPass.cpp
  mlir/LowerToLLVM.cpp
  mlir/LowerToRelay.cpp
  mlir/ShapeInferencePass.cpp
  mlir/ToyCombine.cpp
  mlir/translateModuleToRelayIR.cpp
  )

add_dependencies(toyc-ch8 ToyCh8ShapeInferenceInterfaceIncGen)
add_dependencies(toyc-ch8 ToyCh8OpsIncGen)
add_dependencies(toyc-ch8 ToyCh8RelayOpsIncGen)
add_dependencies(toyc-ch8 ToyCh8CombineIncGen)
add_dependencies(toyc-ch8 MLIRCallOpInterfacesIncGen)
include_directories(include/)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include/)
target_link_libraries(toyc-ch8
  PRIVATE
    MLIRAffineOps
    MLIRAnalysis
    MLIRExecutionEngine
    MLIRIR
    MLIRLLVMIR
    MLIRLoopToStandard
    MLIRParser
    MLIRPass
    MLIRStandardOps
    MLIRStandardToLLVM
    MLIRTargetLLVMIR
    MLIRTransforms
    )

whole_archive_link(toyc-ch8
  MLIRAffineOps
  MLIRLLVMIR
  MLIRStandardOps
  )

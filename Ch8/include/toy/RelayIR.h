
#ifndef MLIR_TARGET_RELAYIR_H
#define MLIR_TARGET_RELAYIR_H

#include <memory>

// Forward-declare LLVM classes.


namespace mlir {

class ModuleOp;
class Pass;

/// Convert the given MLIR module into LLVM IR.  The LLVM context is extracted
/// from the registered LLVM IR dialect.  In case of error, report it
/// to the error handler registered with the MLIR context, if any (obtained from
/// the MLIR module), and return `nullptr`.
int translateModuleToRelayIR(ModuleOp m);

namespace relay{
    std::unique_ptr<mlir::Pass> createRelayAPIPass();
}

} // namespace mlir

#endif // MLIR_TARGET_LLVMIR_H
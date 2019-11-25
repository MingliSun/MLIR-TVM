//====- LowerToAffineLoops.cpp - Partial lowering from Toy to Affine+Std --===//
//
// Copyright 2019 The MLIR Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================
//
// This file implements a partial lowering of Toy operations to a combination of
// affine loops and standard operations. This lowering expects that all calls
// have been inlined, and all shapes have been resolved.
//
//===----------------------------------------------------------------------===//
#include<stdio.h>

#include "toy/Dialect.h"
#include "toy/Passes.h"
#include "toy/RelayDialect.h"

// #include "mlir/Dialect/AffineOps/AffineOps.h"
// #include "mlir/Dialect/StandardOps/Ops.h"
#include "mlir/Dialect/AffineOps/AffineOps.h"
#include "mlir/Dialect/StandardOps/Ops.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/Sequence.h"

using namespace mlir;

//===----------------------------------------------------------------------===//
// ToyToAffine RewritePatterns
//===----------------------------------------------------------------------===//

/// Convert the given TensorType into the corresponding MemRefType.


/// This defines the function type used to process an iteration of a lowered
/// loop. It takes as input a rewriter, an array of memRefOperands corresponding
/// to the operands of the input operation, and the set of loop induction
/// variables for the iteration. It returns a value to store at the current
/// index of the iteration.
using RelayFn = function_ref<Value *(PatternRewriter &rewriter,
                                             ArrayRef<Value *> TensorOperands)>;

  // Generate a call to the processing function with the rewriter, the memref
  // operands, and the loop induction variables. This function will return the
  // value to store at the current index.


namespace {
//===----------------------------------------------------------------------===//
// ToyToAffine RewritePatterns: Binary operations
//===----------------------------------------------------------------------===//

template <typename BinaryOp, typename LoweredBinaryOp>
struct BinaryOpLowering : public ConversionPattern {
  BinaryOpLowering(MLIRContext *ctx)
      : ConversionPattern(BinaryOp::getOperationName(), 1, ctx) {}

  PatternMatchResult
  matchAndRewrite(Operation *op, ArrayRef<Value *> operands,
                  ConversionPatternRewriter &rewriter) const final {
    auto loc = op->getLoc();
    auto type = op->getResult(0)->getType();
  auto binaryopRelay = rewriter.create<LoweredBinaryOp>(loc, type,operands[0],operands[1]);
      rewriter.replaceOp(op, {binaryopRelay});
      //rewriter.eraseOp(op);
    return matchSuccess();
  }
};
using AddOpLowering = BinaryOpLowering<toy::AddOp, relay::AddOp>;
using MulOpLowering = BinaryOpLowering<toy::MulOp, relay::MulOp>;

//===----------------------------------------------------------------------===//
// ToyToAffine RewritePatterns: Constant operations
//===----------------------------------------------------------------------===//

struct ConstantOpLowering : public OpRewritePattern<toy::ConstantOp> {
  using OpRewritePattern<toy::ConstantOp>::OpRewritePattern;

  PatternMatchResult matchAndRewrite(toy::ConstantOp op,
                                     PatternRewriter &rewriter) const final {
    DenseElementsAttr constantValue = op.value();
    Location loc = op.getLoc();    
   auto constantRelay  = rewriter.create<relay::ConstantOp>(loc,constantValue.getType(),constantValue);
   rewriter.replaceOp(op,{constantRelay});
    return matchSuccess();
//     Location loc = op.getLoc();
//                                       //auto type = op.getType();
//                                       std::vector<double> data;
//                                       data.push_back(1);
//                                       data.push_back(1);
//                                       data.push_back(1);
//                                       data.push_back(2);
//                                       data.push_back(2);
//                                       data.push_back(2);
//                                       Operation * oop = op;
//                                       auto tensorType = (*oop->result_type_begin()).cast<TensorType>();
//                                       auto shape = tensorType.getShape();
//                                        mlir::Type elementType = rewriter.getF64Type();
//                                       auto dataType = mlir::RankedTensorType::get(shape, elementType);
//                                       auto dataAttribute =
//         mlir::DenseElementsAttr::get(dataType, llvm::makeArrayRef(data));
// auto constantRelay = rewriter.create<relay::ConstantOp>(loc, dataAttribute.getType(),dataAttribute);
//  rewriter.replaceOp(op,{constantRelay});
//     return matchSuccess();
  }
};
//===----------------------------------------------------------------------===//
// ToyToAffine RewritePatterns: Return operations
//===----------------------------------------------------------------------===//

struct ReturnOpLowering : public OpRewritePattern<toy::ReturnOp> {
  using OpRewritePattern<toy::ReturnOp>::OpRewritePattern;

  PatternMatchResult matchAndRewrite(toy::ReturnOp op,
                                     PatternRewriter &rewriter) const final {
    // During this lowering, we expect that all function calls have been
    // inlined.
    if (op.hasOperand())
      return matchFailure();

    // We lower "toy.return" directly to "std.return".
    rewriter.replaceOpWithNewOp<relay::ReturnOp>(op);
    //rewriter.eraseOp(op);
    return matchSuccess();
  }
};

//===----------------------------------------------------------------------===//
// ToyToAffine RewritePatterns: Transpose operations
//===----------------------------------------------------------------------===//

struct TransposeOpLowering : public ConversionPattern {
  TransposeOpLowering(MLIRContext *ctx)
      : ConversionPattern(toy::TransposeOp::getOperationName(), 1, ctx) {}

  PatternMatchResult
  matchAndRewrite(Operation *op, ArrayRef<Value *> operands,
                  ConversionPatternRewriter &rewriter) const final {
                    auto loc = op->getLoc();
                    auto type = op->getResult(0)->getType();
    auto transposeRelay =  rewriter.create<relay::TransposeOp>(loc,type,operands[0]);
     //rewriter.replaceOp(op, {transposeRelay.getOperand()}, {transposeRelay});
     rewriter.replaceOp(op,{transposeRelay});
    return matchSuccess();
  }
};

struct PrintOpLowering : public ConversionPattern {
  PrintOpLowering(MLIRContext *ctx)
      : ConversionPattern(toy::PrintOp::getOperationName(), 1, ctx) {}

  PatternMatchResult
  matchAndRewrite(Operation *op, ArrayRef<Value *> operands,
                  ConversionPatternRewriter &rewriter) const final {
     auto loc = op->getLoc();
    auto printopRelay = rewriter.create<relay::PrintOp>(loc,operands[0]);
    rewriter.eraseOp(op);
   // rewriter.replaceOp(op, {printopRelay.getOperand()}, {printopRelay});

    return matchSuccess();
  }
};

} // end anonymous namespace.

//===----------------------------------------------------------------------===//
// ToyToAffineLoweringPass
//===----------------------------------------------------------------------===//

/// This is a partial lowering to affine loops of the toy operations that are
/// computationally intensive (like matmul for example...) while keeping the
/// rest of the code in the Toy dialect.
namespace {
struct ToyToRelayLoweringPass : public FunctionPass<ToyToRelayLoweringPass> {
  void runOnFunction() final;
};
} // end anonymous namespace.

void ToyToRelayLoweringPass::runOnFunction() {
  auto function = getFunction();

  // We only lower the main function as we expect that all other functions have
  // been inlined.
  if (function.getName() != "main")
    return;

  // Verify that the given main has no inputs and results.
  // if (function.getNumArguments() || function.getType().getNumResults()) {
  //   function.emitError("expected 'main' to have 0 inputs and 0 results");
  //   return signalPassFailure();
  // }

  // The first thing to define is the conversion target. This will define the
  // final target for this lowering.
  ConversionTarget target(getContext());

  // We define the specific operations, or dialects, that are legal targets for
  // this lowering. In our case, we are lowering to a combination of the
  // `Affine` and `Standard` dialects.
  target.addLegalDialect<relay::RelayDialect>();

  // We also define the Toy dialect as Illegal so that the conversion will fail
  // if any of these operations are *not* converted. Given that we actually want
  // a partial lowering, we explicitly mark the Toy operations that don't want
  // to lower, `toy.print`, as `legal`.
  target.addIllegalDialect<toy::ToyDialect>();
  //target.addLegalOp<ModuleOp, ModuleTerminatorOp>();
  target.addLegalOp<FuncOp>();


  // Now that the conversion target has been defined, we just need to provide
  // the set of patterns that will lower the Toy operations.
  OwningRewritePatternList patterns;
  patterns.insert<AddOpLowering, ConstantOpLowering, MulOpLowering,
                  ReturnOpLowering, TransposeOpLowering,PrintOpLowering>(&getContext());

  // With the target and rewrite patterns defined, we can now attempt the
  // conversion. The conversion will signal failure if any of our `illegal`
  // operations were not converted successfully.
  if (failed(applyPartialConversion(getFunction(), target, patterns)))
    signalPassFailure();
}

/// Create a pass for lowering operations in the `Affine` and `Std` dialects,
/// for a subset of the Toy IR (e.g. matmul).
std::unique_ptr<Pass> mlir::toy::createLowerToRelayPass() {
  return std::make_unique<ToyToRelayLoweringPass>();
}

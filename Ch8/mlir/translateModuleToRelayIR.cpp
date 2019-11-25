#include<stdio.h>
#include <algorithm>
#include<iostream>
#include<vector>
#include<string>


#include "mlir/Analysis/Verifier.h"

#include"mlir/IR/Module.h"
#include "mlir/IR/BlockAndValueMapping.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/StandardTypes.h"
#include "mlir/IR/Block.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/FunctionSupport.h"


#include "mlir/Pass/Pass.h"
#include "mlir/Support/LogicalResult.h"

#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringSet.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

#include "mlir/Dialect/AffineOps/AffineOps.h"
#include "mlir/Dialect/StandardOps/Ops.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/DialectConversion.h"
#include "llvm/ADT/Sequence.h"

#include"toy/RelayIR.h"
#include "toy/RelayDialect.h"

#define N 100

// using namespace mlir;
// using namespace relay;

int mlir::translateModuleToRelayIR(ModuleOp module) {
  printf("Hello RelayIR\n");
// auto operation= module.getOperation();
// if(operation==mlir::relay::ReturnOp){
//     printf(" return\n");
// }
  return 0;
}

namespace{
    class RelayAPIPass : public mlir::FunctionPass<RelayAPIPass> {
    public:
    int num=0;
    int tmp_num=0;
    std::vector<mlir::Value *> each_result;
    std::vector<std::string> each_name;

  void runOnFunction() override {
     auto function =getFunction();
     printf("from tvm import relay\nimport tvm\nimport numpy as np\nfrom tvm.contrib import graph_runtime\n");
     printf("if __name__ == \"__main__\":\n");
     for (mlir::Block &block : getFunction()){
      for (mlir::Operation &op : llvm::make_early_inc_range(block)) {
        if (auto constantop =mlir:: dyn_cast<mlir::relay::ConstantOp>(&op)) {
            auto constantValue = constantop.value();
            auto valueIt = constantValue.getValues<double>().begin();
            mlir::Operation * oop = constantop;
             auto tensorType = (*oop->result_type_begin()).cast<mlir::TensorType>();
             auto shape = tensorType.getShape();
            int len = shape.size();
            int dataNum=1;
            std::vector<int> shape_vector;
            printf("    var%d = relay.var(\"var%d\",shape=(",num,num);
            for(int i=0;i<shape.size();i++)
            {
                if(i!=shape.size()-1) printf("%d,",shape[i]);
                else printf("%d),dtype=\"float64\")\n",shape[i]);
                dataNum*= shape[i];
                shape_vector.push_back(shape[i]);
            }
            printf("    data%d=",num);
            std::vector<double> data;            
            for(int i=0;i<dataNum;i++){
                data.push_back(*valueIt++);
            }
            std::vector<std::string> result;
            for(int i=0;i<dataNum;i++){
                result.push_back(std::to_string(data[i]));
            }
            getDenseElement(result,shape_vector,0);
            std::cout<<result[0]<<std::endl;
            // for(int i=0;i<shape[0];i++)
            // {
            //     printf("[");
            //     for(int j=0;j<shape[1];j++){
            //         printf("%lf",*valueIt++);
            //         if(j!=shape[1]-1) printf(",");
            //     }
            //     printf("]");
            //     if(i!=shape[0]-1) printf(",");
            // }
            // printf("]\n");
            each_result.push_back(oop->getResult(0));
            std::string tmp = "var"+std::to_string(num);
            each_name.push_back(tmp);
            num++;

        }
    if(op.getName().getStringRef()=="relay.transpose"){
        printf("    tmp%d = relay.transpose(",tmp_num);
        int len = each_result.size();
        int i;
        for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(0)) break;
        }
        if(i==len) printf("error occured!\n");
        else printf("%s)\n",each_name[i].c_str());
         each_result.push_back(op.getResult(0));
            std::string tmp = "tmp"+std::to_string(tmp_num);
            each_name.push_back(tmp);
        tmp_num++;


    }else if(op.getName().getStringRef()=="relay.mul"){
         printf("    tmp%d = relay.multiply(",tmp_num);
          int len = each_result.size();
        int i;
        for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(0)) break;
        }
        if(i==len) printf("error occured!\n");
        else  printf("%s,",each_name[i].c_str());
         for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(1)) break;
        }
        if(i==len) printf("error occured!\n");
        else  printf("%s)\n",each_name[i].c_str());
         each_result.push_back(op.getResult(0));
            std::string tmp = "tmp"+std::to_string(tmp_num);
            each_name.push_back(tmp);
        tmp_num++;


    }else if(op.getName().getStringRef()=="relay.add"){
         printf("    tmp%d = relay.add(",tmp_num);
          int len = each_result.size();
        int i;
        for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(0)) break;
        }
        if(i==len) printf("error occured!\n");
        else  printf("%s,",each_name[i].c_str());
         for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(1)) break;
        }
        if(i==len) printf("error occured!\n");
        else  printf("%s)\n",each_name[i].c_str());
         each_result.push_back(op.getResult(0));
            std::string tmp = "tmp"+std::to_string(tmp_num);
            each_name.push_back(tmp);
        tmp_num++;

    }else if(op.getName().getStringRef()=="relay.print"){
        printf("    f1 = relay.Function([");
        for(int i=0;i<num;i++)
        {
            printf("var%d",i);
        if(i!=num-1) printf(",");
        else printf("],");
        }
          int len = each_result.size();
        int i;
        for(i=0;i<len;i++){
            if(each_result[i]==op.getOperand(0)) break;
        }
        if(i==len) printf("error occured!\n");
        else  printf("%s)\n",each_name[i].c_str());
        printf("    mod = relay.Module.from_expr(f1)\n");
        printf("    mod = relay.transform.InferType()(mod)\n");
        printf("    opt_level = 3\n");
         printf("    target = tvm.target.cuda()\n");
         printf("    with relay.build_config(opt_level=opt_level):\n");
        printf("        graph, lib, params = relay.build_module.build(mod, target)\n");
        printf("    ctx = tvm.gpu()\n");
        printf("    module = graph_runtime.create(graph, lib, ctx)\n");
        for(int i=0;i<num;i++){
            printf("    module.set_input(\"var%d\",data%d)\n",i,i);
        }
        printf("    module.run()\n");
        printf("    out = module.get_output(0).asnumpy()\n");
        printf("    print(out)\n"); 
    }
        //printf("%s\n",opp.getName().getStringRef());
      }
    }
    // for (auto &region : op->getRegions()) {
    // for (auto &block : region.getBlocks()) {
    //   for (auto &innerOp : block) {
//     function.walk([&](mlir::Operation *op) {
//         if(op->getName().getStringRef()=="relay.constant"){}
//         else if(op->getName().getStringRef()=="relay.transpose"){
//             printf("transpose number of argument is %d\n",op->getNumOperands());
//             //op->getSuccessorOperand()
//             printf("%s\n", op->getOperand(0));
//             op->getResult(0);
           
//         }
//         else if(op->getName().getStringRef()=="relay.mul"){
//             printf("mul number of argument is %d\n",op->getNumOperands());
            
//         }
//   });
  }
  void getDenseElement(std::vector<std::string> &result,std::vector<int> shape,int num){
    if(num==shape.size()) return;
    getDenseElement(result,shape,num+1);
    std::vector<std::string> tmp;
    for(int i=0;i<result.size()/shape[num]+1;i++)
    {
        std::string str="[";
        for(int j=0;j<shape[num];j++)
        {
            int index = shape[num]*i+j;
            if(j!=shape[num]-1) str=str+ result[index]+",";
            else  str=str+ result[index]+"]";
        }
        tmp.push_back(str);
    }
    result.clear();
    result.assign(tmp.begin(),tmp.end());
}
};
}

    


std::unique_ptr<mlir::Pass> mlir::relay::createRelayAPIPass() {
  return std::make_unique<RelayAPIPass>();
}


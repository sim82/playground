#include <cstdint>
#include <climits>
#include <stdexcept>

#define __STDC_LIMIT_MACROS
#define __STDC_CONSTANT_MACROS
#include <iostream>
#include <memory>
#include <llvm/Module.h>
#include <llvm/Function.h>
#include <llvm/PassManager.h>
#include <llvm/CallingConv.h>
#include <llvm/LLVMContext.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/Support/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>



using llvm::BasicBlock;
using llvm::Module;
using llvm::Value;
using llvm::PassManager;
using llvm::ExecutionEngine;
using llvm::Function;
using llvm::EngineBuilder;
using llvm::PrintMessageAction;
using llvm::LLVMContext;
using llvm::IntegerType;
using llvm::Constant;
using llvm::IRBuilder;
using llvm::Instruction;

Module* makeLLVMModule();

int main(int argc, char**argv) {
    llvm::InitializeNativeTarget();
    
    Module * mod = makeLLVMModule();
    
    llvm::verifyModule(*mod, PrintMessageAction);
    
    PassManager PM;
    PM.add(llvm::createPrintModulePass(&llvm::outs()));
    PM.run(*mod);

    ExecutionEngine *ee;
    
    
    
    // Create the JIT.  This takes ownership of the module.
    std::string error_string;
    EngineBuilder builder(mod);
    
//     llvm::TargetOptions opt;
//     opt.PrintMachineCode = true;
    
//     
    
    //builder.setTargetOptions(opt);
//     llvm::PrintMachineCode = true;
    
    ee = builder.setErrorStr(&error_string).setEngineKind(llvm::EngineKind::JIT).create();
    
    if( ee == nullptr ) {
        std::cerr << "LLVM error: " << error_string << "\n";
        throw std::runtime_error("bailing out");
    }
    
    assert( ee != 0 );
    
    Constant *c = mod->getFunction( "mul_add" );

    assert( c != 0 );
    
    
    Function *f = llvm::cast<Function>(c);
    assert( f != 0 );
    
    void *fptr = ee->getPointerToFunction(f);
    assert( fptr != 0 );
    
    
    
    int32_t (*fp)( int32_t, int32_t, int32_t) = (int32_t (*)(int32_t,int32_t,int32_t))(intptr_t)fptr;
    std::cout << "Evaluated to: " << fp( 1,2,3 ) << "\n";
    
    return 0;
}


Module* makeLLVMModule() {
    // Module Construction
    Module* mod = new Module("test", llvm::getGlobalContext());
    
    auto &gctx = llvm::getGlobalContext();
    
    Constant* c = mod->getOrInsertFunction("mul_add",
                                           /*ret type*/                           IntegerType::get(gctx, 32),
                                           /*args*/                               IntegerType::get(gctx, 32),
                                           IntegerType::get(gctx, 32),
                                           IntegerType::get(gctx, 32),
                                           /*varargs terminated with null*/       NULL);
    
    Function* mul_add = llvm::cast<Function>(c);
    mul_add->setCallingConv(llvm::CallingConv::C);
    
    Function::arg_iterator args = mul_add->arg_begin();
    Value* x = args++;
    x->setName("x");
    Value* y = args++;
    y->setName("y");
    Value* z = args++;
    z->setName("z");
    
    BasicBlock* block = BasicBlock::Create(llvm::getGlobalContext(), "entry", mul_add);
    IRBuilder<> builder(block);
    Value* tmp = builder.CreateBinOp(Instruction::Mul,
                                     x, y, "tmp");
    Value* tmp2 = builder.CreateBinOp(Instruction::Add,
                                      tmp, z, "tmp2");
    
    builder.CreateRet(tmp2);
    
    return mod;
}
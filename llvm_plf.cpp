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
using llvm::PHINode;

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
    llvm::PrintMachineCode = !true;
    
    ee = builder.setErrorStr(&error_string).setEngineKind(llvm::EngineKind::JIT).create();
    
    if( ee == nullptr ) {
        std::cerr << "LLVM error: " << error_string << "\n";
        throw std::runtime_error("bailing out");
    }
    
    assert( ee != 0 );
#if 0 
    Constant *c = mod->getFunction( "mul_add" );

    assert( c != 0 );
    
    
    Function *f = llvm::cast<Function>(c);
    assert( f != 0 );
    
    void *fptr = ee->getPointerToFunction(f);
    assert( fptr != 0 );
    
    
    
    int32_t (*fp)( int32_t, int32_t, int32_t) = (int32_t (*)(int32_t,int32_t,int32_t))(intptr_t)fptr;
    std::cout << "Evaluated to: " << fp( 1,2,3 ) << "\n";
#else 
    Constant *c = mod->getFunction( "loop_test" );

    assert( c != 0 );
    
    
    Function *f = llvm::cast<Function>(c);
    assert( f != 0 );
    
    void *fptr = ee->getPointerToFunction(f);
    assert( fptr != 0 );
    
    
    
    int32_t (*fp)( int32_t ) = (int32_t (*)(int32_t))(intptr_t)fptr;
    std::cout << "eval: " << fp(5) << "\n";
    
#endif
    return 0;
}


Module* makeLLVMModule() {
    // Module Construction
    Module* mod = new Module("test", llvm::getGlobalContext());
    
    auto &gctx = llvm::getGlobalContext();
    
    
    {
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
    }
    
    {
        Constant* c = mod->getOrInsertFunction("loop_test",
        /*ret type*/                           IntegerType::get(gctx, 32),
        /*args*/                               IntegerType::get(gctx, 32),
        /*varargs terminated with null*/       NULL);
        
        Function *loop_test = llvm::cast<Function>(c);
        loop_test->setCallingConv(llvm::CallingConv::C);
        Function::arg_iterator args = loop_test->arg_begin();
        Value *a = args++;
        a->setName("a");

//         loop_test->
        
        BasicBlock* bl_outer = BasicBlock::Create(llvm::getGlobalContext(), "entry", loop_test);
        BasicBlock* bl_loop_head = BasicBlock::Create(llvm::getGlobalContext(), "loop_head", loop_test);
        
//         BasicBlock* bl_loop_head = BasicBlock::Create(llvm::getGlobalContext(), "loop_head", loop_test);
//         BasicBlock* bl_end = BasicBlock::Create(llvm::getGlobalContext(), "end1", loop_test);
//         BasicBlock* bl_body = BasicBlock::Create(llvm::getGlobalContext(), "body", loop_test);
        
        IRBuilder<> builder(bl_outer);
        Value *b = llvm::ConstantInt::get( gctx, llvm::APInt(32, 0) );
        
        
        builder.CreateBr(bl_loop_head);
        
        builder.SetInsertPoint(bl_loop_head);
        
        PHINode *variable = builder.CreatePHI(llvm::Type::getInt32Ty(gctx), 2 );
        variable->addIncoming(a, bl_outer);
        
        PHINode *v_b = builder.CreatePHI(llvm::Type::getInt32Ty(gctx), 2 );
        v_b->addIncoming(b, bl_outer);
        
        Value *a_next = builder.CreateBinOp(Instruction::Add, variable, llvm::ConstantInt::get( gctx, llvm::APInt(32, 1) ));        
        Value *b_next = builder.CreateBinOp(Instruction::Add, v_b, llvm::ConstantInt::get( gctx, llvm::APInt(32, 1) ));        
        
        Value *c_ret = builder.CreateICmpEQ( a_next, llvm::ConstantInt::get( gctx, llvm::APInt(32, 0) ));
        
        variable->addIncoming(a_next, bl_loop_head);
        v_b->addIncoming(b_next, bl_loop_head);
        
        BasicBlock *bl_after_loop = BasicBlock::Create(gctx, "after_loop", loop_test);
  
        // Insert the conditional branch into the end of LoopEndBB.
        builder.CreateCondBr(c_ret, bl_after_loop, bl_loop_head);
        
        builder.SetInsertPoint(bl_after_loop);
        PHINode *v_bx = builder.CreatePHI(llvm::Type::getInt32Ty(gctx), 1 );
        v_bx->addIncoming(b_next, bl_loop_head);
        builder.CreateRet(v_bx);
        
//         loop_builder.CreateCondBr( c_ret, loop_block, end_block );
        
        
        
        
    }
    
    
    return mod;
}
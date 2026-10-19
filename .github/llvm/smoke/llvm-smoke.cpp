// Smoke test of an LLVM package: the native target of its headers must be
// the one of the host (a cross-compiled or merged package can get it wrong),
// and a function compiled by the JIT must run and return 42.

#include <cstdio>
#include <memory>
#include <string>

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/TargetParser/Host.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

int main()
{
    // Only the native target is initialized: a wrong LLVM_NATIVE_TARGET in
    // llvm-config.h leaves no target for the host triple.
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    std::string host = sys::getProcessTriple();
    std::string error;
    if (!TargetRegistry::lookupTarget(Triple(host), error)) {
        std::fprintf(stderr, "no native target for %s: %s\n", host.c_str(), error.c_str());
        return 1;
    }

    auto context = std::make_unique<LLVMContext>();
    auto module  = std::make_unique<Module>("smoke", *context);
    auto fun     = Function::Create(FunctionType::get(Type::getInt32Ty(*context), false),
                                    Function::ExternalLinkage, "answer", module.get());
    IRBuilder<> builder(BasicBlock::Create(*context, "entry", fun));
    builder.CreateRet(builder.getInt32(42));

    ExitOnError check("llvm-smoke: ");
    auto        jit = check(orc::LLJITBuilder().create());
    check(jit->addIRModule(orc::ThreadSafeModule(std::move(module), std::move(context))));
    auto answer = check(jit->lookup("answer")).toPtr<int (*)()>();

    int result = answer();
    std::printf("%s (%s): answer() = %d\n", host.c_str(), sys::getHostCPUName().str().c_str(), result);
    return (result == 42) ? 0 : 1;
}

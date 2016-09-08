//===- CallDependence.cpp - Extract data dependence of call instructions from source code ---------------===//
//
//                     SmartLog Logging Tool
//
// Author: Zhouyang Jia, PhD Candidate
// Affiliation: School of Computer Science, National University of Defense Technology
// Email: jiazhouyang@nudt.edu.cn
//
//===----------------------------------------------------------------------===//
//
// This file implements CallDependencePass to extract data dependence of call instructions from source code.
// Command: opt -load /path/to/LLVMCallDependence.dylib -call-dependence file.bc
// The result is written in call_dependence.cvs, and represented as a 7-trupls:
//   <file_name, caller_name, callee_name, call_line, inst_line, arg_id, dep_type>, where:
//     file_nmae is the file where the dep. locates.
//     caller_name and callee_name are the names of caller and callee function, repectively.
//     call_line and inst_line are the line numbers of call and inst, repectively.
//     arg_id means the index of argument which makes the dependence happends.
//       0 means return value, whereas 1,2,... indicate arguments.
//     dep_type has 4 types: flow, anti, output, input.
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/Operator.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/DependenceAnalysis.h"
#include "llvm/Support/raw_ostream.h"

#include <cxxabi.h>

using namespace std;
using namespace llvm;

#define DEBUG_TYPE "calldependence"

// Count for the number of dependence in one file
STATISTIC(InputCounter, "Counts number of input dependence");
STATISTIC(FlowCounter, "Counts number of flow dependence");
STATISTIC(ReturnCounter, "Counts number of return dependence");

namespace {

struct CallDependencePass : public FunctionPass {
    
    // Pass ID
    static char ID;
    
    // Dependent pass
    DependenceAnalysis *DA;
    DominatorTree *DT;
    
    // Record the source infomation of function from dbg.
    StringRef file_name;
    unsigned function_line;
    StringRef function_name;
    
    // Result file
    FILE* out;
    
    CallDependencePass() : FunctionPass(ID), DA(nullptr), DT(nullptr) {}
    
    /// Demangle the function name
    /// Input: mangling name
    /// output: demangling name
    StringRef getOriginalName(StringRef manglingName){
        if(manglingName.empty())
            return manglingName;
        
        if(manglingName.find("\01_") != string::npos){
            manglingName = manglingName.substr(manglingName.find('_') + 1);
        }
        
        StringRef name;
        int status;
        char* realname;
        realname = abi::__cxa_demangle(const_cast<char*>(manglingName.data()), 0, 0, &status);
        if(!realname)
            return manglingName;
        name = realname;
        name = name.substr(0, name.find_first_of('<'));
        name = name.substr(0, name.find_first_of('('));
        
        return name;
    }
    
    /// Print the result 6-truples
    /// Input: call, inst, index of argument, and dep. type
    /// Output: 6-truples
    void printCallDependence(CallInst* call, Instruction* inst, int index, StringRef type){
        
        string result;
        
        StringRef call_name = "";
        DILocation *call_loc = nullptr, *inst_loc = nullptr;
        unsigned call_line = 0, inst_line = 0;
    
        
        // Get callee name
        if(call->getCalledFunction()){
            call_name = getOriginalName(call->getCalledFunction()->getName());
        }
        
        // Get the dbg infomation of call and inst from metedata.
        call_loc = call->getDebugLoc();
        inst_loc = inst->getDebugLoc();
        
        // Get call line
        if(call_loc){
            call_line = call_loc->getLine();
        }
        else{
            //errs()<<"NoCallLoc: ";
            //call->dump();
        }
        
        // Get inst line
        if(inst_loc){
            inst_line = inst_loc->getLine();
        }
        else{
            // In case the inst is parameter, there is no location information, we just let the line number equals to function_line.
            StoreInst* storeInst = dyn_cast<StoreInst>(inst);
            if(storeInst && storeInst->getPointerOperand() && storeInst->getPointerOperand()->getName().find(".addr")){
                inst_line = function_line;
            }
            else{
                inst_line = call_line;
            }
        }
        
        // Print to file
        char str[16];
        
        result.append(file_name);
        result.append(",");
        
        result.append(function_name);
        result.append(",");
        
        result.append(call_name);
        result.append(",");
        
        sprintf(str, "%d", call_line);
        result.append(str);
        result.append(",");
        
        sprintf(str, "%d", inst_line);
        result.append(str);
        result.append(",");
    
        sprintf(str, "%d", index);
        result.append(str);
        result.append(",");
        
        result.append(type);
        result.append("\n");
        
        fputs(result.c_str(), out);
        
        return;
    }
    
    /// Analyze the dep. between call and inst.
    /// Input: call and inst
    /// Output: invoke printCallDependence for printing results
    ///         true: call is flow dependent on parament; (used for smartlog)
    ///         false: otherwise.
    bool getCallDependence(CallInst* call, Instruction* inst){
        
        bool ret = false;
        
        if(!call || !inst)
            return ret;
        
        // We just ingore the case of "call VS call"
        if(dyn_cast<CallInst>(inst))
            return ret;
        
        // Get the line number of call and inst for further comparision.
        DILocation* callloc = call->getDebugLoc();
        DILocation* instloc = inst->getDebugLoc();
        unsigned call_line = 0, inst_line = 0;
        if(callloc){
            call_line = callloc->getLine();
        }
        else{
           //errs()<<"NoCallLoc: ";
           //call->dump();
        }
        if(instloc){
            inst_line = instloc->getLine();
        }
        else{
            inst_line = function_line;
        }

        // For each argument, test its dependence with inst, this dep. will decide the dep. of call.
        // Each call may have multiple dependence since different arguments could be dependent on inst.
        int index = 1;
        for(CallInst::op_iterator i = call->arg_begin(), e = call->arg_end(); i != e; i++, index++){
            Instruction* arg = dyn_cast<Instruction>(i);
            if(!arg)
                continue;
            
            // The arg is a callinst, we just ingore it since been analyzed as a independent callinst.
            if(dyn_cast<CallInst>(arg))
                continue;
            
            // Something unknown arg occurs beyond load/alloc
            if(!dyn_cast<LoadInst>(arg) && !dyn_cast<AllocaInst>(arg)){
                arg->dump();
            }

            // Get the dep. between arg and inst
            if(auto D = DA->depends(arg, inst, true)) {
                
                // Since the arg is always regarged as read op, there is no output/flow dep.
                if(D->isInput()){
                    // both read
                    if(call_line > inst_line){
                        // read(inst) before read(call)
                        printCallDependence(call, inst, index, "Input");
                    }
                    else{
                        // read(call) before read(inst)
                        printCallDependence(call, inst, index, "Input");
                    }
                }
                
                if(D->isAnti()){
                    // call is read, inst is write
                    if(call_line < inst_line){
                        // read(call) before write(inst)
                        printCallDependence(call, inst, index, "Anti");
                    }
                    else{
                        // write(inst) before read(call)
                        printCallDependence(call, inst, index, "Flow");
                        
                        // The callinst is flow dependent on parament, but we do not need long dependence.
                        if(!instloc && (int)call_line - inst_line < 100)
                            ret = true;
                    }
                }
                
                // When arg is pointer type, we regard the read op as write op, since the pointer arg may be updated.
                if(arg->getType() && arg->getType()->isPointerTy()){
                    if(D->isInput()){
                        // call is write, inst is read
                        if(call_line < inst_line){
                            // write(call) before read(inst)
                            printCallDependence(call, inst, index, "Flow");
                        }
                        else{
                            // read(inst) before write(call)
                            printCallDependence(call, inst, index, "Anti");
                        }
                    }
                    
                    if(D->isAnti()){
                        // both write
                        if(call_line < inst_line){
                            //write(call) before write(inst)
                            printCallDependence(call, inst, index, "Output");
                        }
                        else{
                            //write(inst) before write(call)
                            printCallDependence(call, inst, index, "Output");
                        }
                    }
                }
            } // if(auto D = DA->depends(arg, inst, true)) {
        } // for(CallInst::op_iterator i = call->arg_begin(), e = call->arg_end(); i != e; i++, index++){
        
        // Test the dependence between return value and inst
        if(Instruction* next = call->getNextNode()){
            if(StoreInst* store = dyn_cast<StoreInst>(next)){
                if(auto D = DA->depends(store, inst, true)) {
                
                    // Since the storeinst is always write op, there is no input/anti dep.
                    if(D->isFlow()){
                        // call is write, inst is read
                        if(call_line < inst_line){
                            //write(call) before read(inst)
                            printCallDependence(call, inst, 0, "Flow");
                        }
                        else{
                            //read(inst) before write(call)
                            printCallDependence(call, inst, 0, "Anti");
                        }
                    }
                    if(D->isOutput()){
                        // both write
                        if(call_line < inst_line){
                            //write(call) before write(inst)
                            printCallDependence(call, inst, 0, "Output");
                        }
                        else{
                            //write(inst) before write(call)
                            printCallDependence(call, inst, 0, "Output");
                        }
                    }
                }
            }
        }
        
        return ret;
    }
    
    
    void writeDepOnPara(CallInst* call){
        
        FILE* depOnPara;
        if((depOnPara = fopen("dep_on_para.csv","at")) == NULL) {
            depOnPara = fopen("dep_on_para.csv","w");
        }
        
        string result;
        char str[16];
        
        result.append(file_name);
        result.append(",");
        
        result.append(function_name);
        result.append(",");
        
        StringRef call_name;
        if(call->getCalledFunction()){
            call_name = getOriginalName(call->getCalledFunction()->getName());
        }
        result.append(call_name);
        result.append(",");
        
        unsigned call_line = 0;
        DILocation* call_loc = call->getDebugLoc();
        if(call_loc){
            call_line = call_loc->getLine();
        }
        sprintf(str, "%d", call_line);
        result.append(str);
        result.append("\n");
        
        fputs(result.c_str(), depOnPara);
        
        fclose(depOnPara);
    }
    
    
    StringRef getStemName(StringRef name){
        //errs()<<name<<" ";
        StringRef stem_name = name;
        if(stem_name.find('/') != string::npos){
            stem_name = stem_name.substr(stem_name.find_last_of('/') + 1);
        }
        stem_name = stem_name.substr(0, stem_name.find_first_of('.'));
        //errs()<<stem_name<<"\n";
        return stem_name;
    }
    
    
    bool runOnFunction(Function &F) override {
        
        // Get the basic infomation: function name, function line and file name
        function_line = 0;
        function_name = "";
        DISubprogram *f = getDISubprogram(&F);
        if(f){
            function_line = f->getLine();
            function_name = f->getName();
            //errs()<<f->getFilename()<<" "<<file_name
            if(getStemName(f->getFilename()).compare(getStemName(file_name)) && file_name.find("<stdin>") == string::npos)
                return false;
            file_name = getStemName(f->getFilename());
        }
        
        // Get the dependence for SmartLog
        // For each inst
        for(inst_iterator i = inst_begin(F), e = inst_end(F); i != e; ++i) {
            Instruction* I = &*i;
            if(!I)
                continue;
            
            // Find callinst
            if(CallInst* callInst = dyn_cast<CallInst>(I)){
                
                // Ignore function pointer
                if(callInst->getCalledFunction() == nullptr)
                    continue;
                
                // Ingore the llvm callinst such as llvm.memcyp and llvm.dbg.
                if(callInst->getCalledFunction()->getName().find("llvm.") != string::npos)
                    continue;
                
                // Get line number of call
                unsigned int call_line = 0, use_line = 0;
                DILocation* call_loc = callInst->getDebugLoc();
                if(call_loc){
                    call_line = call_loc->getLine();
                }
                else{
                    // I don't know what happened, maybe function pointer, just ignore!
                    continue;
                }
                
                // Check each argument for dependence
                int arg_index = 1;
                for(CallInst::op_iterator i = callInst->arg_begin(), e = callInst->arg_end(); i != e; i++, arg_index++){
                    Instruction* arg = dyn_cast<Instruction>(i);
                    if(!arg)
                        continue;
                    //errs()<<"Debug ";arg->dump();
                    
                    Value* value = dyn_cast<Value>(arg);
                    if(value == nullptr)
                        continue;
                    
                    if(LoadInst* load = dyn_cast<LoadInst>(arg)){
                        if((value = load->getPointerOperand()) != nullptr){
                            //errs()<<"Var ";value->dump();
                            
                            if(GEPOperator* gepo = dyn_cast<GEPOperator>(value)){
                                if(gepo->getNumOperands() >= 1){
                                    value = gepo->getOperand(0);
                                }
                            }
                               
                            if(ConstantExpr* ce = dyn_cast<ConstantExpr>(value)){
                                //errs()<<"CE ";ce->dump();
                                ce = 0; //make the compiler happy
                            }
                            
                            if(BitCastInst* bit = dyn_cast<BitCastInst>(value)){
                                if(bit->llvm::User::getNumOperands() >= 1){
                                    value = bit->getOperand(0);
                                }
                            }
                            
                            if(GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(value)){
                                if(gep->getPointerOperand()){
                                    value = gep->getPointerOperand();
                                }
                            }
                            
                            if(GlobalValue* gb = dyn_cast<GlobalValue>(value)){
                                //errs()<<"Global ";gb->dump();
                                gb = 0; //make the compiler happy
                            }
                        }
                    }
                    
                    
                    for(Value::user_iterator UI = value->user_begin(), E = value->user_end(); UI!=E; ++UI) {
                        Value* u = *UI;
                        //errs()<<"---Use ";u->dump();
                        
                        Instruction* use = dyn_cast<Instruction>(u);
                        if(use == nullptr)
                            continue;
                        
                        // Get line number of use
                        DILocation* use_loc = use->getDebugLoc();
                        if(use_loc){
                            use_line = use_loc->getLine();
                        }
                        else{
                            // I don't know what happened, maybe function pointer, just ignore!
                            continue;
                        }
                        
                        // We don't care about write or assign operation
                        // Code: a = 1; //write
                        // Code: b = a; //assign
                        // We only focus on read operation in expression
                        // Code: if(a)
                        if(dyn_cast<StoreInst>(use)){
                            continue;
                        }
                        
                        // Input dependence: sensitive argument
                        // Ignore the pairs with more than 30 lines distance
                        if(call_line > use_line && call_line - use_line <= 30){
                            printCallDependence(callInst, use, arg_index, "Input");
                            InputCounter++;
                        }
                        // Flow dependence: pointer argument
                        // Ignore the pairs with more than 30 lines distance
                        if(call_line < use_line && use_line - call_line <= 30){
                            // Only pointer argument can write
                            if(arg->getType() && arg->getType()->isPointerTy()){
                                printCallDependence(callInst, use, arg_index, "Flow");
                                FlowCounter++;
                            }
                        }
                    }
                } //for(CallInst::op_iterator
                
                // Check return value for dependence
                Instruction* next = callInst->getNextNode();
                if(next == nullptr)
                    continue;
                
                StoreInst* store = dyn_cast<StoreInst>(next);
                if(store == nullptr)
                    continue;
                
                Value* value = store->getPointerOperand();
                if(value == nullptr)
                    continue;
                if(store->getValueOperand() != callInst){
                    continue;
                }
                
                if(LoadInst* load = dyn_cast<LoadInst>(value)){
                    if((value = load->getPointerOperand()) != nullptr){
                        //errs()<<"Var ";value->dump();
                        
                        if(GEPOperator* gepo = dyn_cast<GEPOperator>(value)){
                            if(gepo->getNumOperands() >= 1){
                                value = gepo->getOperand(0);
                            }
                        }
                        
                        if(ConstantExpr* ce = dyn_cast<ConstantExpr>(value)){
                            //errs()<<"CE ";ce->dump();
                            ce = 0; //make the compiler happy
                        }
                        
                        if(BitCastInst* bit = dyn_cast<BitCastInst>(value)){
                            if(bit->llvm::User::getNumOperands() >= 1){
                                value = bit->getOperand(0);
                            }
                        }
                        
                        if(GetElementPtrInst* gep = dyn_cast<GetElementPtrInst>(value)){
                            if(gep->getPointerOperand()){
                                value = gep->getPointerOperand();
                            }
                        }
                        
                        if(GlobalValue* gb = dyn_cast<GlobalValue>(value)){
                            //errs()<<"Global ";gb->dump();
                            gb = 0; //make the compiler happy
                        }
                    }
                } //if(LoadInst*
                
                
                for(Value::user_iterator UI = value->user_begin(), E = value->user_end(); UI!=E; ++UI) {
                    Value* u = *UI;
                    //errs()<<"---Use ";u->dump();
                    
                    Instruction* use = dyn_cast<Instruction>(u);
                    if(use == nullptr)
                        continue;
                    
                    // Get line number of use
                    DILocation* use_loc = use->getDebugLoc();
                    if(use_loc){
                        use_line = use_loc->getLine();
                    }
                    else{
                        // I don't know what happened, maybe function pointer, just ignore!
                        continue;
                    }
                    
                    // Flow dependence: return value
                    // Ignore the pairs with more than 30 lines distance
                    if(call_line < use_line && use_line - call_line <= 30){
                        printCallDependence(callInst, use, 0, "Flow");
                        ReturnCounter++;
                    }
                } //for(Value::user_iterator
            } //if(CallInst* callInst
        } //for(inst_iterator
        
        
        // We just want the result for SmartLog, so return
        return false;
        // The following code provides a complete call dependence analysis
        
        
        // Get the dependence analysis instance
        DA = &getAnalysis<DependenceAnalysis>();
        auto *DTWP = getAnalysisIfAvailable<DominatorTreeWrapperPass>();
        DT = DTWP ? &DTWP->getDomTree() : nullptr;
        
        // Record all callinsts
        typedef SmallVector<Value *, 16> ValueVector;
        ValueVector callInstr;
        
        // For each inst
        for(inst_iterator i = inst_begin(F), e = inst_end(F); i != e; ++i) {
            Instruction* I = &*i;
            if(!I)
                continue;
            
            // Find callinst
            if(CallInst* callInst = dyn_cast<CallInst>(I)){
                
                // Ingore the llvm callinst such as llvm.memcyp and llvm.dbg.
                if(callInst->getCalledFunction())
                    if(!callInst->getCalledFunction()->getName().find("llvm."))
                        continue;
                
                // Check the arguments.
                for(CallInst::op_iterator i = callInst->arg_begin(), e = callInst->arg_end(); i != e; i++){
                    Instruction* arg = dyn_cast<Instruction>(i);
                    if(!arg)
                        continue;
                    //arg->dump();
                }
                
                //callInst->dump();
                
                callInstr.push_back(callInst);
            }
        }
        
        //errs() << "Found " << callInstr.size() << " Calls to analyze\n";
        
        // Calc. the call dependence
        // For each callinst
        for(ValueVector::iterator J = callInstr.begin(), JE = callInstr.end(); J != JE; ++J) {
            // For each inst
            for(inst_iterator i = inst_begin(F), e = inst_end(F); i != e; ++i) {
            
                Instruction* inst = &*i;
                CallInst* call = dyn_cast<CallInst>(*J);
                
                if(inst == call)
                    continue;
                
                // Get the line number of call and inst
                DILocation* callloc = call->getDebugLoc();
                DILocation* instloc = inst->getDebugLoc();
                unsigned call_line = 0, inst_line = 0;
                if(callloc){
                    call_line = callloc->getLine();
                }
                else{
                    //errs()<<"NoCallLoc: ";
                    //call->dump();
                }
                if(instloc)
                    inst_line = instloc->getLine();
                else{
                    inst_line = function_line;
                }
                
                // Ingore the long dependence (more than 20 lines)
                if(int(inst_line - call_line) > 20)
                    break;
                if(int(call_line - inst_line) > 20)
                    continue;
                
                // FIXME getCallDependence fails when 'bitcast' occurs, what happened:(
                // Get call dependence
                if(getCallDependence(call, inst)){
                    writeDepOnPara(call);
                }
            }
        }
        return false;
    }
    
    
    bool doInitialization(Module &M) override {
        // Open the file where print result
        if((out = fopen("call_dependence.csv","at")) == NULL) {
            out = fopen("call_dependence.csv","w");
        }
        file_name = M.getName();
        return false;
    }
    
    
    bool doFinalization(Module &M) override {
        //errs()<<"The number of input dependence is "<<InputCounter<<"\n";
        //errs()<<"The number of flow dependence is "<<FlowCounter<<"\n";
        //errs()<<"The number of return dependence is "<<ReturnCounter<<"\n";
        fclose(out);
        return false;
    }
    
    
    void getAnalysisUsage(AnalysisUsage &AU) const override {
        AU.addRequired<DependenceAnalysis>();
        AU.addRequired<DominatorTreeWrapperPass>();
        AU.setPreservesAll();
    }
};

} //namespace

char CallDependencePass::ID = 0;
static RegisterPass<CallDependencePass> X("call-dependence", "Extract call dependence");

# CallDependence
Analyze data dependence of call expression.

---

### Introduction
This project is supposed to analyze data dependence of call expression, e.g., input, flow, anti and output dependence. Existing date-dependence analysis pass in LLVM is hard to analyze the dependence between call expression (e.g., *foo(a)*) and variables (e.g., *b*) . To help this situation, *CallDependence* converts the dependence between call and variables to dependence between arguments (of the call, e.g., *a*) and variable, and then infers the call dependence.


### Usage

##### Compile
- Change directory to LLVM lib transform directory.
```sh
cd path/to/llvm-source-tree/lib/Transforms
```
- Download source code.
```sh
git clone https://github.com/ZhouyangJia/CallDependence.git
```
- Add *add_subdirectory(CallDependence)* to CMakeList.txt.
```sh
echo "add_subdirectory(CallDependence)" >> CMakeLists.txt
```
- [Recompile LLVM](http://llvm.org/docs/CMake.html) and try following command to test.
```sh
ls path/to/llvm-build/Release/lib/*CallDependence*
```

##### Analyze log information
- Generate *compile_commands.json*. More information about [compile_commands.json](http://clang.llvm.org/docs/JSONCompilationDatabase.html).
```sh
cd test/
tar zxvf bftpd-3.2.tar
cd bftpd/
./configure
bear make
```
- Generate *build_ir.sh*, This file is used to build LLVM IR for each file.
```sh
../../script/extract_command.pl compile_commands.json
```
- Build LLVM IR.
```sh
./build_ir.sh
```
- Get analysis result.
```sh
../../script/all_call_dependence.sh
```
The result is written in call_dependence.cvs, and represented as a 7-tuples:

< file_name, caller_name, callee_name, call_line, inst_line, arg_id, dep_type >, where:

**file_name** is the file where the dep. locates.

**caller_name** and **callee_name** are the names of caller and callee function, repectively.

**call_line** and **inst_line** are the line numbers of call and inst, respectively.

**arg_id** means the index of argument which makes the dependence happens. 0 means return value, whereas 1,2,... indicate arguments.

**dep_type** has 4 types: flow, anti, output, input.

#!/bin/bash



###This bash script is automatically produced by "extract_command.pl compile_commands.json", DO NOT CHANGE!###

total=0;
succ=0;
check(){
	if [ $? -eq 0 ]
	then
		succ=`expr $succ + 1`;
	fi
	total=`expr $total + 1`;
}

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c.bc
check
echo "1 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c.bc
check
echo "2 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c.bc
check
echo "3 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c.bc
check
echo "4 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c.bc
check
echo "5 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c.bc
check
echo "6 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c.bc
check
echo "7 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c.bc
check
echo "8 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c.bc
check
echo "9 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c.bc
check
echo "10 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c.bc
check
echo "11 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -c /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c.bc
check
echo "12 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c to bc" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c.ll
echo "1 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/bftpdutmp.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c.ll
echo "2 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c.ll
echo "3 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/commands_admin.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c.ll
echo "4 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/cwd.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c.ll
echo "5 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/dirlist.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c.ll
echo "6 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/list.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c.ll
echo "7 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/login.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c.ll
echo "8 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/logging.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c.ll
echo "9 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/main.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c.ll
echo "10 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/mystring.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c.ll
echo "11 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/options.c to ll" >&2

cd /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd 
clang -g -emit-llvm -DHAVE_CONFIG_H -I/Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd -DVERSION=\"3.2\" -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -S /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c -o /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c.ll
echo "12 /Users/zhouyangjia/llvm-3.8.0.src/tools/clang/tools/clang-loggrad/test/bftpd/md5.c to ll" >&2
echo "Total ir $total" >&2
echo "Succ ir $succ" >&2

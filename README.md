# Requirements

  * g++ 7.5.0 or newer
  * cmake 3.8 or newer

# Compilation

From the root folder execute the following sequence:
  * `mkdir build`
  * `cd build`
  * `cmake ..`
  * `make`

The static library is generated in build/pipeline
Example Binary is generated in build/src

If compiling the code manually, include the following flags:

```
-std=c++14 -fpermissive -Wno-deprecated-declarations -m64 -fexceptions -g -fPIC -g 
-Wall -Wno-long-long -Wconversion -Wwrite-strings -Wsign-compare -D_GLIBCXX_DEBUG
```

# Sample Execution

The example binary is available in build/src/program_test

```
ldd program_test
        linux-vdso.so.1 (0x00007ffffc5e9000)
        libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f691bac0000)
        libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f691baa0000)
        libpthread.so.0 => /lib/x86_64-linux-gnu/libpthread.so.0 (0x00007f691ba7d000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f691b880000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f691bcf8000)
        libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f691b731000)

 ./program_test             runs program, for more details view example code in main.cpp
```
 

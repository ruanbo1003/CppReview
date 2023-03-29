## hiredis 
* download and install
  * https://github.com/redis/hiredis
      ```shell
      wget https://github.com/redis/hiredis/archive/refs/tags/v1.1.0.zip
      ```
  * make
    ```shell
    [~/Downloads/hiredis-1.1.0] $make
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic alloc.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic net.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic hiredis.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic sds.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic async.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic read.c
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic sockcompat.c
    cc -dynamiclib -Wl,-install_name,/usr/local/lib/libhiredis.1.1.0.dylib -o libhiredis.dylib  -o libhiredis.dylib alloc.o net.o hiredis.o sds.o async.o read.o sockcompat.o
    ar rcs libhiredis.a alloc.o net.o hiredis.o sds.o async.o read.o sockcompat.o
    /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib: file: libhiredis.a(sockcompat.o) has no symbols
    cc -std=c99 -c -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic test.c
    cc -o hiredis-test -O3 -fPIC   -Wall -W -Wstrict-prototypes -Wwrite-strings -Wno-missing-field-initializers -g -ggdb  -pedantic -I. test.o libhiredis.a
    Generating hiredis.pc for pkgconfig...
    ```
  * make install
    ```shell
    [~/Downloads/hiredis-1.1.0] $make install
    mkdir -p /usr/local/include/hiredis /usr/local/include/hiredis/adapters /usr/local/lib
    cp -pPR hiredis.h async.h read.h sds.h alloc.h sockcompat.h /usr/local/include/hiredis
    cp -pPR adapters/*.h /usr/local/include/hiredis/adapters
    cp -pPR libhiredis.dylib /usr/local/lib/libhiredis.1.1.0.dylib
    cd /usr/local/lib && ln -sf libhiredis.1.1.0.dylib libhiredis.dylib
    cp -pPR libhiredis.a /usr/local/lib
    mkdir -p /usr/local/lib/pkgconfig
    cp -pPR hiredis.pc /usr/local/lib/pkgconfig
    ```
  * add header file path and lib path
  ```
    include_directories("/usr/local/include/")
    target_link_libraries(CppReview /usr/local/lib/libhiredis.dylib)
  ```
  

    

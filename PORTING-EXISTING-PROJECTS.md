Porting Existing Projects
=========================

Porting existing projects is possible, but not without its pitfalls. You can also use this
to create an Alljoyn OpenFrameworks project from the OpenFrameworks `emptyExample`.

XCode Build Settings
--------------------
The project will need the following build settings in order to compile and link with Alljoyn:

* Architecture: 32 bit
* Other Linker Flags: `$ALLJOYN_LDFLAGS`
* Header Search Paths: `$ALLJOYN_CORE_HEADERS`
* Library Search Paths: `$ALLJOYN_CORE_LIBS`
* Enable C++ Exceptions: Yes (default)
* Enable C++ Runtime Types: Yes (default)
* Other C++ Flags: `-D__MACOSX_CORE__ -lpthread -mtune-native -DQCC_OS_GROUP_POSIX -DQCC_OS_DARWIN`
User-defined settings:
*  ALLJOYN_CORE_HEADERS: `$ALLJOYN_ROOT/common/inc $ALLJOYN_CORE_ROOT/build/darwin/x86/debug/dist/cpp/inc $ALLJOYN_CORE_ROOT/build/darwin/x86/debug/dist/cpp/inc/alljoyn $ALLJOYN_CORE_ROOT/src $ALLJOYN_CORE_ROOT/daemon/posix $ALLJOYN_CORE_ROOT/daemon $ALLJOYN_CORE_ROOT/daemon/ice`
*  ALLJOYN_CORE_LIBS: `$ALLJOYN_CORE_ROOT/build/darwin/x86/debug/dist/cpp/lib $ALLJOYN_ROOT/common/crypto/openssl/openssl-1.01/build/Debug`
*  ALLJOYN_CORE_ROOT: $ALLJOYN_ROOT/alljoyn_core
*  ALLJOYN_LDFLAGS: `-lalljoyn -lajdaemon -lBundledDaemon.o -lssl -lcrypto`
*  ALLJOYN_ROOT: `~/alljoyn`

On any file that implements BusObject (or when built complains about lacking the
symbol typeinfo) go to the Target's Build Phases tab and in the Compile
Sources menu add `-fno-rtti` to its Compiler Flag

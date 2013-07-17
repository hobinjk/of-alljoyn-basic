Installation
============

For now only installation on Mac OS X is supported. To install, you will
need access to the internet.

Downloading OpenFrameworks
==========================
Download the OpenFrameworks source bundle from [their website](http://openframeworks.cc "OpenFrameworks").
The bundle can be unzipped anywhere, the important part is that you lay out the directory structure as
described below.

Directory Structure
-------------------

The of-alljoyn-basic folder (this repository) into should be placed in the
`apps` folder of the OpenFrameworks source. Otherwise, the relative paths
expected by the OpenFrameworks configuration will be incorrect and everything
will explode in a shower of header-missing errors.

Downloading and Building AllJoyn
================================
Follow Qualcomm's [build instructions](https://www.alljoyn.org/docs-and-downloads/build-environment/configuring-build-environment-ios-and-osx-rev).
**Note:** it is important to use their recommended root directory (`~/alljoyn`) for this one.
Their *XCode Build* should work. If not, open Terminal to manually build the source with the following commands:
    cd ~/alljoyn/alljoyn_core
    CONFIGURATION=debug scons -u OS=darwin WS=off VARIANT=debug
You should now have files in `~/alljoyn/alljoyn_core/build/darwin/x86/debug/dist/cpp/`. If you don't, try running
the manual build.

Running the Examples
====================

You should now be able to run the examples by opening their XCode Project files in XCode. The fail-safe way to run
them is on the same computer.

Debugging Common Errors
=======================

ofMain.h Not Found
------------------
Make sure that of-alljoyn-basic is in the `apps` directory of OpenFrameworks. On my computer, this
looks like `of_v0.7.4_osx_release/apps/of-alljoyn-basic`.

qcc/Platform.h Or alljoyn/BusAttachment.h Not Found
---------------------------------------------------
Make sure that AllJoyn is installed in your home directory. If you really do not want it to be there,
adjust the variable ALLJOYN_ROOT in the XCode project's build settings.

Linker Missing Symbols or Library not found for -lalljoyn
---------------------------------------------------------
Make sure that AllJoyn Core built without errors. If it built without errors,
`~/alljoyn/alljoyn_core/build/darwin/x86/debug/dist/cpp/` should have at least the `lib`, `bin`,
and `inc` folders present.

Undefined symbol: `typeinfo`
----------------------------
Go to the alljoynBasicServer or alljoynBasicClient project's Target. The Target should have a Build Phases
tab which in turn should have a Compile Sources menu. In this menu, add the `-fno-rtti` flag to any file
involving `<alljoyn/BusObject.h>`. Note that any file with this flag set can not use OpenFrameworks functions.



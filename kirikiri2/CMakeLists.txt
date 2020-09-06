# from 2.8.5 support complation database
cmake_minimum_required(VERSION 2.8.5)

project(kirikiri2)

# to debug cmake: --trace / --trace-expand
set(CMAKE_VERBOSE_MAKEFILE true)

# compliation database
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Options: None / Debug / Release / RelWithDebInfo / MinSizeRel
set(CMAKE_BUILD_TYPE Debug)

# Default value can be seen by: cmake --trace
# CMAKE_C_FLAGS_DEBUG = -g
# CMAKE_C_FLAGS_REALEASE = -O3 -DNDEBUG
# to add OpemMP support: -fopemmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Run make in subdir
# add_custom_target(
#    extern_lib
#    COMMAND make
#    WORKING_DIRECTORY full_path to where Makefile is located
# )
# add_executable(myexecutable myexcutable.c)
# target_link_libraries(myexecutable full_path_to_generated_library)
# add_dependencies(myexecutable extern_lib)


# path to store executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

# options for executable:
#   target_include_directories
#   target_link_libraries
#   target_compile_definitions
#   target_compile_options


# set(TARGET krkr.exe)
# add_executable("${TARGET}" "src/core/environ/win32/tvpwin32.cpp")
# target_include_directories("${TARGET}" PUBLIC "src/core/base")
# target_include_directories("${TARGET}" PUBLIC "src/core/base/win32")
# target_include_directories("${TARGET}" PUBLIC "src/core/environ")
# target_include_directories("${TARGET}" PUBLIC "src/core/msg")
# target_include_directories("${TARGET}" PUBLIC "src/core/msg/win32")
# target_include_directories("${TARGET}" PUBLIC "src/core/sound")
# target_include_directories("${TARGET}" PUBLIC "src/core/tjs2")
# target_include_directories("${TARGET}" PUBLIC "src/core/utils")
# target_include_directories("${TARGET}" PUBLIC "src/core/visual")
# target_include_directories("${TARGET}" PUBLIC "src/bcbfake")
# target_compile_definitions("${TARGET}" PUBLIC "__WIN32__")



set(TARGET hack)
add_executable("${TARGET}" 
    "src/hack/hack.cpp"

    "src/core/tjs2/tjs.cpp"
    "src/core/tjs2/tjs.tab.cpp"
    "src/core/tjs2/tjsArray.cpp"
    "src/core/tjs2/tjsConfig.cpp"
    "src/core/tjs2/tjsObject.cpp"
    "src/core/tjs2/tjsNative.cpp"
    "src/core/tjs2/tjsVariant.cpp"
    "src/core/tjs2/tjsVariantString.cpp"
    "src/core/tjs2/tjsString.cpp"
    "src/core/tjs2/tjsScriptBlock.cpp"
    "src/core/tjs2/tjsInterface.cpp"
    "src/core/tjs2/tjsInterCodeExec.cpp"
    "src/core/tjs2/tjsDictionary.cpp"
    "src/core/tjs2/tjsScriptCache.cpp"
    # "src/core/tjs2/tjsRegExp.cpp"
    "src/core/tjs2/tjsInterCodeGen.cpp"
    "src/core/tjs2/tjsGlobalStringMap.cpp"
    "src/core/tjs2/tjsLex.cpp"
    "src/core/tjs2/tjsCompileControl.cpp"
    "src/core/tjs2/tjspp.tab.cpp"
    "src/core/tjs2/tjsNamespace.cpp"
    "src/core/tjs2/tjsError.cpp"
    "src/core/tjs2/tjsUtils.cpp"
    "src/core/tjs2/tjsMath.cpp"
    "src/core/tjs2/tjsRandomGenerator.cpp"
    "src/core/tjs2/tjsMT19937ar-cok.cpp"
    "src/core/tjs2/tjsDate.cpp"
    "src/core/tjs2/tjsDateParser.cpp"
    "src/core/tjs2/tjsdate.tab.cpp"
    "src/core/tjs2/tjsException.cpp"
    "src/core/tjs2/tjsMessage.cpp"
    "src/core/tjs2/tjsDisassemble.cpp"
    "src/core/tjs2/tjsDebug.cpp"
    "src/core/tjs2/tjsConstArrayData.cpp"
    "src/core/tjs2/tjsByteCodeLoader.cpp"
    "src/core/tjs2/tjsBinarySerializer.cpp"

    # "src/core/base/XP3Archive.cpp"
    # "src/core/base/TextStream.cpp"
    # "src/core/base/UtilStreams.cpp"

    # "src/core/utils/DebugIntf.cpp"
    # "src/core/utils/win32/DebugImpl.cpp"
    # "src/core/msg/MsgIntf.cpp"
    # "src/core/msg/win32/MsgImpl.cpp"
    # "src/core/base/StorageIntf.cpp"
    # "src/core/base/win32/StorageImpl.cpp"
    # "src/core/base/SysInitIntf.cpp"
    # "src/core/base/win32/SysInitImpl.cpp"

    # "src/core/base/win32/ScriptMgnImpl.cpp"
    # "src/core/base/EventIntf.cpp"
    # "src/core/base/win32/EventImpl.cpp"
    # "src/core/base/SystemIntf.cpp"
    # "src/core/base/win32/SystemImpl.cpp"
    # "src/core/base/PluginIntf.cpp"
    # "src/core/base/win32/PluginImpl.cpp"

    # "src/core/environ/win32/WideNativeFuncs.cpp"
    # "src/core/environ/win32/DetectCPU.cpp"
    # "src/core/environ/win32/EmergencyExit.cpp"
    # "src/core/environ/win32/HintWindow.cpp"
    # "src/core/visual/LayerBitmapIntf.cpp"
    # "src/core/visual/win32/LayerBitmapImpl.cpp"
    # "src/core/visual/LayerIntf.cpp"
    # "src/core/visual/LayerManager.cpp"
    # "src/core/visual/win32/LayerImpl.cpp"
    # "src/core/visual/win32/DInputMgn.cpp"
    # "src/core/visual/WindowIntf.cpp"
    # "src/core/visual/win32/WindowImpl.cpp"
    # "src/core/visual/GraphicsLoaderIntf.cpp"
    # "src/core/visual/LoadTLG.cpp"
    # "src/core/visual/win32/GraphicsLoaderImpl.cpp"
    # "src/core/visual/MenuItemIntf.cpp"
    # "src/core/visual/win32/MenuItemImpl.cpp"
    # "src/core/visual/ComplexRect.cpp"
    # "src/core/visual/TransIntf.cpp"
    # "src/core/visual/win32/TransImpl.cpp"
    # "src/core/visual/VideoOvlIntf.cpp"
    # "src/core/visual/win32/VideoOvlImpl.cpp"
    # "src/core/visual/Resampler.cpp"
    # "src/core/visual/tvpgl.c"
    # "src/core/visual/IA32/tvpgl_ia32_intf.c"
    # "src/core/visual/win32/PassThroughDrawDevice.cpp"
    # "src/core/visual/win32/DrawDevice.cpp"
    # "src/core/utils/PadIntf.cpp"
    # "src/core/utils/win32/PadImpl.cpp"
    # "src/core/utils/TimerIntf.cpp"
    # "src/core/utils/win32/TimerImpl.cpp"
    # "src/core/utils/win32/TickCount.cpp"
    # "src/core/utils/KAGParser.cpp"
    # "src/core/utils/Random.cpp"
    # "src/core/utils/md5.c"
    # "src/core/utils/ThreadIntf.cpp"
    # "src/core/utils/win32/ThreadImpl.cpp"
    # "src/core/utils/ClipboardIntf.cpp"
    # "src/core/utils/win32/ClipboardImpl.cpp"
    # "src/core/base/win32/FileSelector.cpp"
    # "src/core/base/win32/SusieArchive.cpp"
    # "src/core/sound/SoundBufferBaseIntf.cpp"
    # "src/core/sound/win32/SoundBufferBaseImpl.cpp"
    # "src/core/sound/CDDAIntf.cpp"
    # "src/core/sound/win32/CDDAImpl.cpp"
    # "src/core/sound/MIDIIntf.cpp"
    # "src/core/sound/win32/MIDIImpl.cpp"
    # "src/core/sound/WaveIntf.cpp"
    # "src/core/sound/win32/WaveImpl.cpp"
    # "src/core/sound/win32/tvpsnd.c"
    # "src/core/sound/WaveLoopManager.cpp"
    # "src/core/sound/PhaseVocoderDSP.cpp"
    # "src/core/sound/PhaseVocoderFilter.cpp"
    # "src/core/sound/WaveSegmentQueue.cpp"
    # "src/core/utils/win32/TLogViewer.cpp"
    # "src/core/base/ScriptMgnIntf.cpp"
    # "src/core/base/win32/FuncStubs.cpp"
    # "src/core/msg/win32/OptionsDesc.cpp"
    # "src/tools/win32/krdevui/ConfSettingsUnit.cpp"
    # "src/core/base/CharacterSet.cpp"
    # "src/core/base/BinaryStream.cpp")
)
# USELIB("../../visual/IA32/tvpgl_ia32.lib")
# USEOBJ("../../sound/cpu/pv_sse.obj")
# USEOBJ("../../sound/cpu/pv_def.obj")
# USEFORM("HaltWarnFormUnit.cpp", TVPHaltWarnForm)
# USEFORM("../../utils/win32/ConsoleFormUnit.cpp", TVPConsoleForm)
# USEFORM("../../utils/win32/PadFormUnit.cpp", TVPPadForm)
# USEFORM("MainFormUnit.cpp", TVPMainForm)
# USEFORM("WatchFormUnit.cpp", TVPWatchForm)
# USEFORM("../../visual/win32/WindowFormUnit.cpp", TVPWindowForm)
# USEFORM("../../visual/win32/MenuContainerFormUnit.cpp", TVPMenuContainerForm)
# USEFORM("../../visual/win32/FontSelectFormUnit.cpp", TVPFontSelectForm)
# USEFORM("VersionFormUnit.cpp", TVPVersionForm)
# USE("../../base/common.h", File)
# USE("../../utils/ObjectList.h", File)
# USEFORM("../../../tools/win32/krdevui/ConfMainFrameUnit.cpp", ConfMainFrame); /* TFrame: File Type */

target_include_directories("${TARGET}" PUBLIC "src/core/base")
target_include_directories("${TARGET}" PUBLIC "src/core/base/win32")
target_include_directories("${TARGET}" PUBLIC "src/core/environ")
target_include_directories("${TARGET}" PUBLIC "src/core/environ/win32")
target_include_directories("${TARGET}" PUBLIC "src/core/msg")
target_include_directories("${TARGET}" PUBLIC "src/core/msg/win32")
target_include_directories("${TARGET}" PUBLIC "src/core/sound")
target_include_directories("${TARGET}" PUBLIC "src/core/sound/win32/")
target_include_directories("${TARGET}" PUBLIC "src/core/tjs2")
target_include_directories("${TARGET}" PUBLIC "src/core/utils")
target_include_directories("${TARGET}" PUBLIC "src/core/utils/win32")
target_include_directories("${TARGET}" PUBLIC "src/core/visual")
target_include_directories("${TARGET}" PUBLIC "src/core/visual/win32")
target_include_directories("${TARGET}" PUBLIC "src/environ")
target_include_directories("${TARGET}" PUBLIC "src/environ/win32")
target_include_directories("${TARGET}" PUBLIC "src/plugins")
target_include_directories("${TARGET}" PUBLIC "src/plugins/win32")
target_include_directories("${TARGET}" PUBLIC "src/hack")
# target_include_directories("${TARGET}" PUBLIC "src/core/environ/win32/bcb2007/include")

# target_link_directories("${TARGET}" PUBLIC "src/core/environ/win32/bcb2007/lib")
# target_link_libraries("${TARGET}" PUBLIC "boost_regex_bcb6_mss")

target_compile_definitions("${TARGET}" PUBLIC "__WIN32__")
target_compile_definitions("${TARGET}" PUBLIC "_WIN32")
target_compile_definitions("${TARGET}" PUBLIC "TJS_NO_REGEXP")

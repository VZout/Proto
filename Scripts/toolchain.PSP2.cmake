set(CMAKE_SYSTEM_NAME        Generic)
set(CMAKE_SYSTEM_VERSION     1)
set(CMAKE_VS_PLATFORM_NAME   PSVita)
set(CMAKE_GENERATOR_PLATFORM PSVita)

set(SCE_PSP2_SDK_DIR $ENV{SCE_PSP2_SDK_DIR})
if(NOT EXISTS ${SCE_PSP2_SDK_DIR})
	message(FATAL_ERROR "${SCE_PSP2_SDK_DIR} does not exist! Is Playstation Vita SDK installed? You should check SDK Manager whether everything is set correctly.")
endif()

# specify the cross compiler
set(CMAKE_C_COMPILER   ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/psp2snc.exe  CACHE PATH "c compiler")
set(CMAKE_CXX_COMPILER ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/psp2snc.exe  CACHE PATH "c++ compiler")
set(CMAKE_AS           ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/psp2as.exe   CACHE PATH "archive")
set(CMAKE_LINKER       ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/psp2ld.exe   CACHE PATH "linker")
set(CMAKE_NM           ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/psp2name.exe CACHE PATH "nm")

#set(CMAKE_AR           ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/orbis-ar.exe      CACHE PATH "archive")
#set(CMAKE_OBJCOPY      ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/orbis-objcopy.exe CACHE PATH "objcopy")
#set(CMAKE_OBJDUMP      ${SCE_PSP2_SDK_DIR}/host_tools/build/bin/orbis-objdump.exe CACHE PATH "objdump")

#TODO
#target extension not set!

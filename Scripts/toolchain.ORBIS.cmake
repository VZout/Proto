set(CMAKE_SYSTEM_NAME        Generic)
set(CMAKE_SYSTEM_VERSION     1)
set(CMAKE_VS_PLATFORM_NAME   ORBIS)
set(CMAKE_GENERATOR_PLATFORM ORBIS)

set(SCE_ORBIS_SDK_DIR $ENV{SCE_ORBIS_SDK_DIR})
if(NOT EXISTS ${SCE_ORBIS_SDK_DIR})
	message(FATAL_ERROR "${SCE_ORBIS_SDK_DIR} does not exist! Is Playstation 4 SDK installed? You should check SDK Manager whether everything is set correctly.")
endif()

# specify the cross compiler
set(CMAKE_C_COMPILER   ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-clang.exe   CACHE PATH "c compiler")
set(CMAKE_CXX_COMPILER ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-clang++.exe CACHE PATH "c++ compiler")
set(CMAKE_AS           ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-as.exe      CACHE PATH "archive")
set(CMAKE_AR           ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-ar.exe      CACHE PATH "archive")
set(CMAKE_LINKER       ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-ld.exe      CACHE PATH "linker")
set(CMAKE_NM           ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-nm.exe      CACHE PATH "nm")
set(CMAKE_OBJCOPY      ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-objcopy.exe CACHE PATH "objcopy")
set(CMAKE_OBJDUMP      ${SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-objdump.exe CACHE PATH "objdump")

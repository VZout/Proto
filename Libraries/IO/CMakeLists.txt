cmake_minimum_required(VERSION 3.9.2)

set(TARGETNAME IO)
project(${TARGETNAME} LANGUAGES CXX)

include_directories(${MAIN_INCLUDE_FOLDER}IO)
include_directories(${MAIN_INCLUDE_FOLDER}IO/Controller)
include_directories(${MAIN_INCLUDE_FOLDER}IO/File)

#header files
set(${TARGETNAME}_CORE_HEADERS
	../../Code/include/IO/IInputHandler.h
	../../Code/include/IO/IKeyboardInputHandler.h
	../../Code/include/IO/IMouseInputHandler.h)

source_group("Header Files" FILES ${${TARGETNAME}_CORE_HEADERS})

set(${TARGETNAME}_CONTROLLER_HEADERS
	../../Code/Include/IO/Controller/ControllerBase.h
	../../Code/Include/IO/Controller/ControllerState.h
	../../Code/Include/IO/Controller/CreateController.h
	../../Code/Include/IO/Controller/EButton.h
	../../Code/Include/IO/Controller/EController.h
	../../Code/Include/IO/Controller/EThumbStick.h
	../../Code/Include/IO/Controller/ETrigger.h
	../../Code/Include/IO/Controller/IController.h
	../../Code/Include/IO/Controller/XBoxController.h)

source_group("Header Files\\Controller" FILES ${${TARGETNAME}_CONTROLLER_HEADERS})

set(${TARGETNAME}_DATABASE_HEADERS
	../../Code/Include/IO/Database/BsonBlob.h
	../../Code/Include/IO/Database/Connection.h
	../../Code/Include/IO/Database/Helpers/BsonIncludes.h
	../../Code/Include/IO/Database/Helpers/MongoIncludes.h)

source_group("Header Files\\Database" FILES ${${TARGETNAME}_DATABASE_HEADERS})

set(${TARGETNAME}_FILE_HEADERS
	../../Code/Include/IO/File/BaseFile.h
	../../Code/Include/IO/File/CreateDir.h
	../../Code/Include/IO/File/DirExists.h
	../../Code/Include/IO/File/EFilePos.h
	../../Code/Include/IO/File/File.h
	../../Code/Include/IO/File/FileExists.h
	../../Code/Include/IO/File/GetCurrentDir.h
	../../Code/Include/IO/File/GetExtensionFromFilename.h
	../../Code/Include/IO/File/GetFileLastChangeTime.h
	../../Code/Include/IO/File/GetFilenameNoExt.h
	../../Code/Include/IO/File/GetPathFromFilename.h
	../../Code/Include/IO/File/GetPathSeparator.h
	../../Code/Include/IO/File/IFile.h
	../../Code/Include/IO/File/MemFile.h
	../../Code/Include/IO/File/SetCurrentDir.h)

source_group("Header Files\\File" FILES ${${TARGETNAME}_FILE_HEADERS})

set(${TARGETNAME}_IPC_HEADERS
	../../Code/Include/IO/IPC/AnonymousPipe.h
	../../Code/Include/IO/IPC/NamedPipe.h
	../../Code/Include/IO/IPC/Pipe.h
	../../Code/Include/IO/IPC/PipeClient.h
	../../Code/Include/IO/IPC/PipeConstants.h
	../../Code/Include/IO/IPC/PipeCreateParameters.h
	../../Code/Include/IO/IPC/PipeServer.h
	../../Code/Include/IO/IPC/WriteToNamedPipe.h)

source_group("Header Files\\IPC" FILES ${${TARGETNAME}_IPC_HEADERS})

set(${TARGETNAME}_AGGREGATE_HEADERS
	${${TARGETNAME}_CORE_HEADERS}
	${${TARGETNAME}_CONTROLLER_HEADERS}
	${${TARGETNAME}_DATABASE_HEADERS}
	${${TARGETNAME}_FILE_HEADERS}
	${${TARGETNAME}_IPC_HEADERS})

# source files
set(${TARGETNAME}_CONTROLLER_SOURCES
	../../Code/source/IO/Controller/ControllerBase.cpp
	../../Code/source/IO/Controller/CreateController.cpp
	../../Code/source/IO/Controller/XBoxController.cpp)

source_group("Source Files\\Controller" FILES ${${TARGETNAME}_CONTROLLER_SOURCES})

set(${TARGETNAME}_FILE_SOURCES
	../../Code/source/IO/File/GetExtensionFromFilename.cpp
	../../Code/source/IO/File/GetPathSeparator.cpp)

source_group("Source Files\\File" FILES ${${TARGETNAME}_FILE_SOURCES})

set(${TARGETNAME}_AGGREGATE_SOURCES
	${${TARGETNAME}_CONTROLLER_SOURCES}
	${${TARGETNAME}_FILE_SOURCES})

# setup target
add_library(${TARGETNAME} STATIC ${${TARGETNAME}_AGGREGATE_HEADERS} ${${TARGETNAME}_AGGREGATE_SOURCES})

set_target_properties(${TARGETNAME} PROPERTIES FOLDER "Libraries")

install(TARGETS ${TARGETNAME} DESTINATION lib)

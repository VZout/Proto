cmake_minimum_required(VERSION 3.9.2)

project(io)

include_directories(${MAIN_INCLUDE_FOLDER}IO)
include_directories(${MAIN_INCLUDE_FOLDER}IO/Controller)

#header files
set(IO_CORE_HEADERS
	../../Code/include/IO/IInputHandler.h
	../../Code/include/IO/IKeyboardInputHandler.h
	../../Code/include/IO/IMouseInputHandler.h)

source_group("Header Files" FILES ${IO_CORE_HEADERS})

set(IO_CONTROLLER_HEADERS
	../../Code/Include/IO/Controller/ControllerBase.h
	../../Code/Include/IO/Controller/ControllerState.h
	../../Code/Include/IO/Controller/CreateController.h
	../../Code/Include/IO/Controller/EButton.h
	../../Code/Include/IO/Controller/EController.h
	../../Code/Include/IO/Controller/EThumbStick.h
	../../Code/Include/IO/Controller/ETrigger.h
	../../Code/Include/IO/Controller/IController.h
	../../Code/Include/IO/Controller/XBoxController.h)

source_group("Header Files\\Controller" FILES ${IO_CONTROLLER_HEADERS})

set(IO_DATABASE_HEADERS
	../../Code/Include/IO/Database/BsonBlob.h
	../../Code/Include/IO/Database/Connection.h
	../../Code/Include/IO/Database/Helpers/BsonIncludes.h
	../../Code/Include/IO/Database/Helpers/MongoIncludes.h)

source_group("Header Files\\Database" FILES ${IO_DATABASE_HEADERS})

set(IO_FILE_HEADERS
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

source_group("Header Files\\File" FILES ${IO_FILE_HEADERS})

set(IO_IPC_HEADERS
	../../Code/Include/IO/IPC/AnonymousPipe.h
	../../Code/Include/IO/IPC/NamedPipe.h
	../../Code/Include/IO/IPC/Pipe.h
	../../Code/Include/IO/IPC/PipeClient.h
	../../Code/Include/IO/IPC/PipeConstants.h
	../../Code/Include/IO/IPC/PipeCreateParameters.h
	../../Code/Include/IO/IPC/PipeServer.h
	../../Code/Include/IO/IPC/WriteToNamedPipe.h)

source_group("Header Files\\IPC" FILES ${IO_IPC_HEADERS})

set(IO_AGGREGATE_HEADERS
	${IO_CORE_HEADERS}
	${IO_CONTROLLER_HEADERS}
	${IO_DATABASE_HEADERS}
	${IO_FILE_HEADERS}
	${IO_IPC_HEADERS})

# source files
set(IO_CONTROLLER_SOURCES
	../../Code/source/IO/Controller/ControllerBase.cpp
	../../Code/source/IO/Controller/CreateController.cpp
	../../Code/source/IO/Controller/XBoxController.cpp)

source_group("Source Files\\Controller" FILES ${IO_CONTROLLER_SOURCES})

set(IO_AGGREGATE_SOURCES
	${IO_CONTROLLER_SOURCES})

# setup target
add_library(IO STATIC ${IO_AGGREGATE_HEADERS} ${IO_AGGREGATE_SOURCES})

set_target_properties(IO PROPERTIES FOLDER "Libraries")

install(TARGETS IO DESTINATION lib)

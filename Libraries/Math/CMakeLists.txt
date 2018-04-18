cmake_minimum_required(VERSION 3.9.2)

project(math)

include_directories(${MAIN_INCLUDE_FOLDER}Math)
include_directories(${MAIN_INCLUDE_FOLDER}Math/Helpers)
include_directories(${MAIN_INCLUDE_FOLDER}Math/RNG)
include_directories(${MAIN_INCLUDE_FOLDER}Math/ThirdParty)

include_directories(${THIRD_PARTY_FOLDER}glm-0.9.8.5)

#header files
set(Math_CORE_HEADERS
	../../Code/include/Math/AABB.h
	../../Code/include/Math/Arccos.h
	../../Code/include/Math/ASin.h
	../../Code/include/Math/Atan2.h
	../../Code/include/Math/Clamp.h
	../../Code/include/Math/Color.h
	../../Code/include/Math/Constants.h
	../../Code/include/Math/Cos.h
	../../Code/include/Math/DegToRad.h
	../../Code/include/Math/Dimension.h
	../../Code/include/Math/EHandedness.h
	../../Code/include/Math/ERotationMultiplicationOrder.h
	../../Code/include/Math/ESpace.h
	../../Code/include/Math/EUnit.h
	../../Code/include/Math/IInterpolator.h
	../../Code/include/Math/Matrix4.h
	../../Code/include/Math/Max.h
	../../Code/include/Math/Min.h
	../../Code/include/Math/Quaternion.h
	../../Code/include/Math/RadToDeg.h
	../../Code/include/Math/Sin.h
	../../Code/include/Math/TanH.h
	../../Code/include/Math/Trigonometry.h
	../../Code/include/Math/Vector2.h
	../../Code/include/Math/Vector3.h
	../../Code/include/Math/Vector4.h
	../../Code/include/Math/Wrap.h)

source_group("Header Files" FILES ${Math_CORE_HEADERS})

set(Math_HELPERS_HEADERS
	../../Code/include/Math/Helpers/GLMIncludes.h
	../../Code/include/Math/Helpers/IsPowerOfTwo.h
	../../Code/include/Math/Helpers/RunningAverage.h)

source_group("Header Files\\Helpers" FILES ${Math_HELPERS_HEADERS})

set(Math_INTERPOLATION_HEADERS
	../../Code/include/Math/Interpolation/Cosine.h
	../../Code/include/Math/Interpolation/Lerp.h
	../../Code/include/Math/Interpolation/SCurve.h)

source_group("Header Files\\Math\\Interpolation" FILES ${Math_INTERPOLATION_HEADERS})

set(Math_RNG_HEADERS
	../../Code/include/Math/RNG/CreateRandomNumberGenerator.h
	../../Code/include/Math/RNG/IRandomNumberGenerator.h
	../../Code/include/Math/RNG/MersenneTwister.h)

source_group("Header Files\\RNG" FILES ${Math_RNG_HEADERS})

set(Math_THIRDPARTY_HEADERS
	../../Code/include/Math/ThirdParty/mtrand.h)

source_group("Header Files\\ThirdParty" FILES ${Math_THIRDPARTY_HEADERS})

set(Math_AGGREGATE_HEADERS
	${Math_CORE_HEADERS}
	${Math_HELPERS_HEADERS}
	${Math_INTERPOLATION_HEADERS}
	${Math_RNG_HEADERS}
	${Math_THIRDPARTY_HEADERS})

# source files
set(Math_CORE_SOURCES
	../../Code/source/Math/Color.cpp
	../../Code/source/Math/DegToRad.cpp
	../../Code/source/Math/Matrix4.cpp
	../../Code/source/Math/Quaternion.cpp
	../../Code/source/Math/RadToDeg.cpp
	../../Code/source/Math/Vector2.cpp
	../../Code/source/Math/Vector3.cpp
	../../Code/source/Math/Vector4.cpp
	../../Code/source/Math/Wrap.cpp)

source_group("Source Files" FILES ${Math_CORE_SOURCES})

set(Math_HELPERS_SOURCES
	../../Code/source/Math/Helpers/IsPowerOfTwo.cpp)

source_group("Source Files\\Helpers" FILES ${Math_HELPERS_SOURCES})

set(Math_RNG_SOURCES
	../../Code/source/Math/RNG/CreateRandomNumberGenerator.cpp
	../../Code/source/Math/RNG/MersenneTwister.cpp)

source_group("Source Files\\RNG" FILES ${Math_RNG_SOURCES})

set(Math_THIRDPARTY_SOURCES
	../../Code/source/Math/ThirdParty/mtrand.cpp)

source_group("Source Files\\ThirdParty" FILES ${Math_THIRDPARTY_SOURCES})

set(Math_AGGREGATE_SOURCES
	${Math_CORE_SOURCES}
	${Math_HELPERS_SOURCES}
	${Math_RNG_SOURCES}
	${Math_THIRDPARTY_SOURCES})

# setup target
add_library(Math STATIC ${Math_AGGREGATE_HEADERS} ${Math_AGGREGATE_SOURCES})

set_target_properties(Math PROPERTIES FOLDER "Libraries")

install(TARGETS Math DESTINATION lib)

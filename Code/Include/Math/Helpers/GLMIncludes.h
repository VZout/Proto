#pragma once

#if defined(PROTO_GLM_ENABLED)

#pragma warning(push)
#pragma warning(disable : 4201)
#pragma warning(disable : 4701)

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma warning(pop)

#endif

#include "OpenGLShaderReflection.h"

#include <assert.h>

#if defined(GFX_API_OPENGL)

void InspectShaderItems(GLuint a_ShaderProgram, GLenum a_ProgramInterface, uint32_t *a_NumItems, OpenGLInterfaceItem **a_Items)
{
	GLint numItems = 0;
	glGetProgramInterfaceiv(a_ShaderProgram, a_ProgramInterface, GL_ACTIVE_RESOURCES, &numItems);
	OpenGLInterfaceItem* items = (OpenGLInterfaceItem*)malloc(sizeof(OpenGLInterfaceItem) * numItems);
	*a_NumItems = (uint32_t)numItems;

	const GLenum properties[3] = { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION };
	int32_t item = 0;
	for (item = 0; item < numItems; ++item)
	{
		GLint values[3];
		glGetProgramResourceiv(a_ShaderProgram, a_ProgramInterface, item, 3, properties, 3, NULL, values);

		items[item].m_Type = values[0];
		items[item].m_Name = (char*)malloc(values[1] + 1);
		glGetProgramResourceName(a_ShaderProgram, a_ProgramInterface, item, values[1], 0, items[item].m_Name);
		items[item].m_Location = values[2];
	}
	*a_Items = items;
}

void InspectShaderProgram(OpenGLAPI *a_API, OpenGLShader *a_Shader)
{
	GFX_UNUSED(a_API);
	GFX_UNUSED(a_Shader);
// 	if (GLEW_ARB_program_interface_query || (a_API->m_Parameters.m_MajorVersion >= 4 && a_API->m_Parameters.m_MinorVersion >= 3))
// 	{
// 		const GLuint shaderProgram = a_Shader->m_ProgramID;
// 		InspectShaderItems(shaderProgram, GL_PROGRAM_INPUT, &a_Shader->m_NumAttributes, &a_Shader->m_Attributes);
// 		InspectShaderItems(shaderProgram, GL_UNIFORM, &a_Shader->m_NumUniforms, &a_Shader->m_Uniforms);		
// 	}
// 	else
// 	{
// 		assert(false);
// 	}
}

#endif

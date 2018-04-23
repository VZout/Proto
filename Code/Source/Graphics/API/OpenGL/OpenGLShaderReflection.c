#include "OpenGLShaderReflection.h"

#include <assert.h>

void InspectShaderProgram(OpenGLAPI *a_API, GLuint a_ShaderProgram)
{
	if (GLEW_ARB_program_interface_query || (a_API->m_Parameters.m_MajorVersion >= 4 && a_API->m_Parameters.m_MinorVersion >= 3))
	{
		GLint numAttributes = 0;
		glGetProgramInterfaceiv(a_ShaderProgram, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &numAttributes);
		const GLenum properties[3] = { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION };

		int32_t attribute = 0;
		for (attribute = 0; attribute < numAttributes; ++attribute)
		{
			GLint values[3];
			glGetProgramResourceiv(a_ShaderProgram, GL_PROGRAM_INPUT, attribute, 3, properties, 3, NULL, values);
			//if (-1 == values[0])
			{
				char *name = (char*)malloc(values[1] + 1);
				glGetProgramResourceName(a_ShaderProgram, GL_PROGRAM_INPUT, attribute, values[1], 0, name);
				name[values[1]] = '\0';
			}
		}

		GLint numUniforms = 0;
		glGetProgramInterfaceiv(a_ShaderProgram, GL_UNIFORM, GL_ACTIVE_RESOURCES, &numUniforms);

		int32_t uniform = 0;
		for (uniform = 0; uniform < numUniforms; ++uniform)
		{
			GLint values[4];
			glGetProgramResourceiv(a_ShaderProgram, GL_UNIFORM, uniform, 3, properties, 3, NULL, values);
			if (-1 == values[0])
			{
				char *name = (char*)malloc(values[1] + 1);
				glGetProgramResourceName(a_ShaderProgram, GL_UNIFORM, uniform, values[1], 0, name);
				name[values[1]] = '\0';
			}
		}
	}
	else
	{
		assert(false);
	}
}
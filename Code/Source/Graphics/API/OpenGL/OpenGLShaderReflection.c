#include "OpenGLShaderReflection.h"

#include <assert.h>

#if defined(GFX_API_OPENGL)

int compare(const void *a_Lhs, const void *a_Rhs)
{
	const OpenGLInterfaceItem *lhs = (const OpenGLInterfaceItem*)a_Lhs;
	const OpenGLInterfaceItem *rhs = (const OpenGLInterfaceItem*)a_Rhs;
	return (lhs->m_Location - rhs->m_Location);
}
void InspectShaderItems(GLuint a_ShaderProgram, GLenum a_ProgramInterface, uint32_t *a_NumItems, OpenGLInterfaceItem **a_Items)
{
	GLint numItems = 0;
	glGetProgramInterfaceiv(a_ShaderProgram, a_ProgramInterface, GL_ACTIVE_RESOURCES, &numItems);
	*a_Items = (OpenGLInterfaceItem*)malloc(sizeof(OpenGLInterfaceItem) * numItems);
	*a_NumItems = (uint32_t)numItems;

	const GLenum properties[4] = { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION, GL_ARRAY_SIZE };
	int32_t item = 0;
	for (item = 0; item < numItems; ++item)
	{
		GLint values[4];
		glGetProgramResourceiv(a_ShaderProgram, a_ProgramInterface, item, 4, properties, 4, NULL, values);

		(*a_Items)[item].m_Type = values[0];
		(*a_Items)[item].m_Name = (char*)malloc(values[1] + 1);
		glGetProgramResourceName(a_ShaderProgram, a_ProgramInterface, item, values[1], 0, (*a_Items)[item].m_Name);
		(*a_Items)[item].m_Location = values[2];
	}

	qsort((*a_Items), numItems, sizeof(OpenGLInterfaceItem), compare);
}

#endif

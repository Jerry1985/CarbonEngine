#include "OGLShader.h"
#include "OGLInterface.h"
#include "Common\Log\Log.h"
#include "Container\CBitArray.h"

RALShader*	OGLInterface::CreateVertexShader()
{
	return new OGLVertexShader();
}

RALShader*	OGLInterface::CreatePixelShader()
{
	return new OGLPixelShader();
}

OGLShader::OGLShader() :m_shaderId(0)
{
}

OGLShader::~OGLShader()
{
	if (m_shaderId)
		glDeleteShader(m_shaderId);
}

// get ogl shader type
uint32 OGLShader::_getShaderType() const
{
	switch (m_ShaderType)
	{
		case RAL_SHADERTYPE_VERTEXSHADER:
			return GL_VERTEX_SHADER;
		case RAL_SHADERTYPE_PIXELSHADER:
			return GL_FRAGMENT_SHADER;
	}

	return 0;
}

// create shader from byte code
bool OGLShader::CreateShader(const CBitArray& bytecode)
{
	const char* src = (const char*) bytecode.GetData();

	m_shaderId = glCreateShader(_getShaderType());

	glShaderSource(m_shaderId, 1, (const GLchar* const*)&src, NULL);
	glCompileShader(m_shaderId);

	// Check Vertex Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result != GL_TRUE && InfoLogLength > 0){
		char* log = new char[InfoLogLength + 1];
		glGetShaderInfoLog(m_shaderId, InfoLogLength, NULL, log);
		CARBON_LOG(LOG_WARNING, LOG_RENDERER, log);
		delete[] log;

		return false;
	}
	return true;
}

OGLVertexShader::OGLVertexShader()
{
	m_ShaderType = RAL_SHADERTYPE_VERTEXSHADER;
}

OGLVertexShader::~OGLVertexShader()
{
}

OGLPixelShader::OGLPixelShader()
{
	m_ShaderType = RAL_SHADERTYPE_PIXELSHADER;
}

OGLPixelShader::~OGLPixelShader()
{
}
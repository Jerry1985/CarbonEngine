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

OGLVertexShader::OGLVertexShader()
{
	m_ShaderType = RAL_SHADERTYPE_VERTEXSHADER;
}

OGLVertexShader::~OGLVertexShader()
{
}

// create shader from byte code
bool OGLVertexShader::CreateShader(const CBitArray& bytecode)
{
	const GLchar* data = (const GLchar*) bytecode.GetData();
	uint32 len = bytecode.GetSize();

	m_shaderId = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(m_shaderId, 1, (const GLchar* const*)&data, NULL);
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

OGLPixelShader::OGLPixelShader()
{
	m_ShaderType = RAL_SHADERTYPE_PIXELSHADER;
}

OGLPixelShader::~OGLPixelShader()
{
}

// create shader from byte code
bool OGLPixelShader::CreateShader(const CBitArray& bytecode)
{
	const GLchar* const data = (const GLchar*) bytecode.GetData();
	uint32 len = bytecode.GetSize();

	m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_shaderId, 1, (const GLchar* const*)&data, NULL);
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
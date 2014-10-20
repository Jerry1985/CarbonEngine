#include "OGLShader.h"
#include "OGLInterface.h"

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
}

OGLVertexShader::~OGLVertexShader()
{
}

// create shader from byte code
bool OGLVertexShader::CreateShader(void* data, unsigned length)
{
	m_shaderId = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(m_shaderId, 1, (const char* const*)&data, NULL);
	glCompileShader(m_shaderId);

	// Check Vertex Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result != GL_TRUE && InfoLogLength > 0){
		char* log = new char[InfoLogLength + 1];
		glGetShaderInfoLog(m_shaderId, InfoLogLength, NULL, log);
		delete[] log;
		
		return false;
	}
	return true;
}

OGLPixelShader::OGLPixelShader()
{
}

OGLPixelShader::~OGLPixelShader()
{
}

// create shader from byte code
bool OGLPixelShader::CreateShader(void* data, unsigned length)
{
	m_shaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_shaderId, 1, (const char* const*)&data, NULL);
	glCompileShader(m_shaderId);

	// Check Vertex Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (Result != GL_TRUE && InfoLogLength > 0){
		char* log = new char[InfoLogLength + 1];
		glGetShaderInfoLog(m_shaderId, InfoLogLength, NULL, log);

		return false;
	}
	return true;
}
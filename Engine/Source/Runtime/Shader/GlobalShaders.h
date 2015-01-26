#pragma once

// Load Global Shaders
bool	LoadGlobalShaders();

// Initialize Global shaders
void	InitGlobalShaders();

// Get Global Shader with specific type
template< class T >
T&		GetGlobalShader()
{
	static T type;
	if (type.IsInitialized() == false)
		type.Init();

	return type;
}
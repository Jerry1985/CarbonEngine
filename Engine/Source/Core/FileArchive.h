#pragma once

#include "Archive.h"
#include "Common\Platform\PlatformFile.h"
#include "Common\Container\CString.h"
#include "Core\Name.h"

#define FILEARCHIVE_BUFFER_SIZE	4096

class FileArchive : public Archive
{
public:
	FileArchive(const TCHAR* name, bool loading);

	// Close the file archive
	virtual void	CloseFileArchive() = 0;

protected:
	PlatformFileHandle*	m_FileHandle = 0;

	Name	m_FileName;

	int32	m_CurrentBufferPos = 0;
	int32	m_FileSize = 0;
	uint8	m_Buffer[FILEARCHIVE_BUFFER_SIZE];
};

class FileReadArchive : public FileArchive
{
public:
	FileReadArchive(const TCHAR* filename);
	~FileReadArchive();

	// Serialize
	virtual void	Serialize(void* V, uint32 length);

	// Close the file archive
	void	CloseFileArchive();

private:
	int32	m_ValidBufferSize = 0;
};

class FileWriteArchive : public FileArchive
{
public:
	FileWriteArchive(const TCHAR* filename);
	~FileWriteArchive();

	// Close the file archive
	void	CloseFileArchive();

	// Serialize
	virtual void	Serialize(void* V, uint32 length);
};
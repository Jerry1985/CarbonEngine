#include "FileArchive.h"
#include "Utility\UtilityMacro.h"
#include "Common\Misc\Assertion.h"
#include "Common\Math\Math.h"
#include "Common\Log\Log.h"

FileArchive::FileArchive(const TCHAR* name, bool loading) : Archive(loading), m_FileName(name)
{
}

FileReadArchive::FileReadArchive(const TCHAR* filename) : FileArchive(filename,true)
{
	m_FileHandle = PlatformFile::OpenFile(filename, true);

	if (m_FileHandle)
	{
		m_FileSize = m_FileHandle->Size();
		m_ValidBufferSize = 0;
		m_CurrentBufferPos = -1;
	}
}

// Serialize
void FileReadArchive::Serialize(void* V, uint32 length)
{
	if (V == 0 || length == 0)
		return;

	if (!m_FileHandle || m_CurrentBufferPos > m_FileSize)
	{
		CARBON_LOG(LOG_WARNING, LOG_FILE, S("File archive serialization error: ") + m_FileName.ToString());

		memset(V, 0, length);
		return;
	}

	int32 byteToRead = length;
	while (byteToRead > 0)
	{
		if (m_CurrentBufferPos >= m_ValidBufferSize || m_CurrentBufferPos < 0 )
		{
			int32 remainData = m_FileHandle->Size() - m_FileHandle->Tell();
			if (remainData == 0)
			{
				CARBON_LOG(LOG_WARNING, LOG_FILE, S("File archive serialization error: ") + m_FileName.ToString());

				memset((uint8*)V + length - byteToRead, 0, byteToRead);
				return;
			}

			m_ValidBufferSize = Math::Min(FILEARCHIVE_BUFFER_SIZE, remainData);
			m_FileHandle->Read(m_Buffer, m_ValidBufferSize);
			m_CurrentBufferPos = 0;
		}

		int32 toRead = Math::Min(byteToRead, m_ValidBufferSize - m_CurrentBufferPos);

		memcpy((uint8*)V + length - byteToRead, &m_Buffer[m_CurrentBufferPos], toRead);

		m_CurrentBufferPos += toRead;
		byteToRead -= toRead;
	}
}

// Close the file archive
void FileReadArchive::CloseFileArchive()
{
	CloseFileArchive();
}

FileWriteArchive::FileWriteArchive(const TCHAR* filename) : FileArchive(filename,false)
{
	m_FileHandle = PlatformFile::OpenFile(filename, false);

	if (m_FileHandle)
	{
		m_FileSize = m_FileHandle->Size();
		m_CurrentBufferPos = 0;
	}
}

FileWriteArchive::~FileWriteArchive()
{
	CloseFileArchive();
}

// Serialize
void FileWriteArchive::Serialize(void* V, uint32 length)
{
	if (V == 0 || length == 0)
		return;

	if (!m_FileHandle)
		return;

	int32 byteToWrite = length;
	while (byteToWrite > 0)
	{
		if (m_CurrentBufferPos >= FILEARCHIVE_BUFFER_SIZE)
		{
			m_FileHandle->Write(m_Buffer, m_CurrentBufferPos);
			m_CurrentBufferPos = 0;
		}

		int32 toWrite = Math::Min(byteToWrite, FILEARCHIVE_BUFFER_SIZE - m_CurrentBufferPos);

		memcpy(&m_Buffer[m_CurrentBufferPos], (uint8*)V + length - byteToWrite, toWrite);

		m_CurrentBufferPos += toWrite;
		byteToWrite -= toWrite;
	}
}

// Close the file archive
void FileWriteArchive::CloseFileArchive()
{
	// flush the remain memory
	if (m_CurrentBufferPos > 0 && m_FileHandle)
	{
		m_FileHandle->Write(m_Buffer, m_CurrentBufferPos);
		m_CurrentBufferPos = 0;
	}
	SAFE_DELETE(m_FileHandle);
}
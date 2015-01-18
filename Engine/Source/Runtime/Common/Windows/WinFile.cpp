#include "Platform\PlatformFile.h"
#include "Container\CString.h"
#include <fileapi.h>

WinFileHandle::WinFileHandle(HANDLE handle, const TCHAR* filename) : m_Handle(handle), m_Name(filename)
{
	CASSERT(_isValid());

	// get file size
	_seek(0, FILE_END);
	m_Size = _seek(0, FILE_CURRENT);
	_seek(0, FILE_BEGIN);
}

WinFileHandle::~WinFileHandle()
{
	CASSERT(_isValid());

	CloseHandle(m_Handle);
}

// Read data
bool WinFileHandle::Read(uint8* data, int32 sizeToRead)
{
	CASSERT(_isValid());

	while (sizeToRead>0)
	{
		int32 size = Math::Min(sizeToRead, FILECHUNK_SIZE);

		uint32 readSize = 0;
		BOOL read = ReadFile(m_Handle, data, size, (LPDWORD)&readSize, 0);
		if (!read || readSize != size)
			return false;
	
		data += size;
		sizeToRead -= size;
	}

	return true;
}

// Seek
int32	WinFileHandle::Seek(uint32 pos)
{
	return _seek(pos, FILE_BEGIN);
}

int32	WinFileHandle::SeekEnd(uint32 pos)
{
	return _seek(pos, FILE_END);
}

// Tell the current position
int32	WinFileHandle::Tell() const
{
	return _seek(0, FILE_CURRENT);
}

// Total size of the file
int32	WinFileHandle::Size() const
{
	return m_Size;
}

// Get Filename
const CString& WinFileHandle::GetFileName() const
{
	return m_Name;
}

// Write data
bool WinFileHandle::Write(uint8* data, int32 size)
{
	int32 writeSize;
	BOOL write = WriteFile(m_Handle, data, size, (LPDWORD)&writeSize, 0);
	return write && writeSize == size;
}

bool WinFile::IsFileExist(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(filename, &FindFileData);

	bool exist = (hFind != INVALID_HANDLE_VALUE);
	return exist;
}

int32 WinFile::FileSize(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	int size = 0;
	HANDLE handle = CreateFile(filename, FILE_READ_EA, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (handle != INVALID_HANDLE_VALUE)
	{
		size = GetFileSize(handle, NULL);
		CloseHandle(handle);
	}
	return size;
}

bool WinFile::IsFileReadOnly(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	uint32 attr = GetFileAttributes(filename);
	return !(attr & FILE_ATTRIBUTE_DIRECTORY) && (attr & FILE_ATTRIBUTE_READONLY);
}

// create file
WinFileHandle*	WinFile::OpenFile(const CString& filename, bool read)
{
	CASSERT(!filename.IsEmpty());

	uint32 readFlag = read ? GENERIC_READ : GENERIC_WRITE;
	uint32 openFlag = read ? OPEN_EXISTING : OPEN_ALWAYS;
	HANDLE handle = (HANDLE)CreateFile(filename, readFlag, FILE_SHARE_READ, NULL, openFlag, NULL, NULL);
	if (handle == INVALID_HANDLE_VALUE)
		return 0;
	return new WinFileHandle(handle,filename);
}

// check if the directory exist
bool WinFile::IsDirExist(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	uint32 attr = GetFileAttributes(filename);
	return !!(attr & FILE_ATTRIBUTE_DIRECTORY);
}

// check if the directory is readonly
bool WinFile::IsDirReadOnly(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	uint32 attr = GetFileAttributes(filename);
	return (attr & FILE_ATTRIBUTE_DIRECTORY) && (attr & FILE_ATTRIBUTE_READONLY);
}

// delete the file
void WinFile::DelFile(const CString& filename)
{
	CASSERT(!filename.IsEmpty());

	DeleteFile(filename);
}
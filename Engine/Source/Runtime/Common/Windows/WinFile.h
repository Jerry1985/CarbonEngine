#pragma once

class CString;

#define	FILECHUNK_SIZE	1024*1024*4

class WinFileHandle
{
public:
	WinFileHandle(HANDLE handle);
	~WinFileHandle();

	// Read data
	bool	Read(uint8* data, int32 size);

	// Write data
	bool	Write(uint8* data, int32 size);

	// Total size of the file
	uint32	Size() const;

	// Seek
	uint32	Seek(uint32 pos);
	uint32	SeekEnd(uint32 pos);

	// Tell the current position
	uint32	Tell() const;

private:
	HANDLE	m_Handle;

	uint32	m_Size;

	// check if the handle is a valid one
	FORCE_INLINE bool	_isValid()
	{
		return m_Handle != 0 && m_Handle != INVALID_HANDLE_VALUE;
	}

	// seek
	FORCE_INLINE int32	_seek(uint32 pos, uint32 method) const
	{
		LARGE_INTEGER seekData;
		seekData.QuadPart = pos;
		seekData.LowPart = SetFilePointer(m_Handle, seekData.LowPart, &seekData.HighPart, method);
		if (seekData.LowPart == INVALID_SET_FILE_POINTER && GetLastError() != NO_ERROR)
			seekData.QuadPart = -1;
		return (int32)seekData.QuadPart;
	}
};

class WinFile
{
public:
	WinFile(){}
	~WinFile(){}

	// check if the file exist
	static bool	IsFileExist(const CString& filename);

	// check if the file is readonly
	static bool IsFileReadOnly(const CString& filename);

	// get the size of file in bytes
	static int FileSize(const CString& filename);

	// delete the file
	static void DelFile(const CString& filename);

	// create file
	static WinFileHandle*	OpenFile(const CString& filename, bool read = true);

	// check if the directory exist
	static bool IsDirExist(const CString& filename);

	// check if the directory is readonly
	static bool IsDirReadOnly(const CString& filename);
};

typedef	WinFileHandle	PlatformFileHandle;
typedef	WinFile			PlatformFile;

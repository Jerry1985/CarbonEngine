#include "Platform\PlatformFile.h"
#include "Container\CString.h"
#include <fileapi.h>

bool WinFile::IsFileExist(const CString& filename)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(filename, &FindFileData);

	return hFind != INVALID_HANDLE_VALUE;
}
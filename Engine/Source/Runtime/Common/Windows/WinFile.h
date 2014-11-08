#ifndef CARBON_FILE
#define CARBON_FILE

class CString;

class WinFileHandle
{
public:
	WinFileHandle(){}
	~WinFileHandle(){}
};

class WinFile
{
public:
	WinFile(){}
	~WinFile(){}

	static bool	IsFileExist(const CString& filename);
};

#endif
#include "FileLogContext.h"
#include "Platform\PlatformFile.h"
#include "Utility\PtrProxy.h"

FileLogContext::FileLogContext(const TCHAR* filename):
m_LogFileName(filename)
{
	m_LogInfo.Allocate(MAX_LOG_INMEMORY);

	PlatformFile::DelFile(m_LogFileName);
}

FileLogContext::~FileLogContext()
{
	Flush();
}

// add one log entry
void FileLogContext::AddLog(const CString& message)
{
	if (m_LogInfo.GetCount() == MAX_LOG_INMEMORY)
		Flush();

	m_LogInfo.Add(message);
}

// flush the log
void FileLogContext::Flush()
{
	CArrayIterator<CString>	it(m_LogInfo);
	while (!it.IsEnd())
	{
		PtrProxy<PlatformFileHandle> handle(PlatformFile::OpenFile(m_LogFileName, false));
		handle->SeekEnd(0);
		handle->Write((uint8*)((const TCHAR*)(*it)), (*it).StrSizeInBytes() - sizeof(TCHAR) );

		++it;
	}

	m_LogInfo.Reset();
}
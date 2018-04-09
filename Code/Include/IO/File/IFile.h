#pragma once

#include "EFilePos.h"

BEGIN_NAMESPACE(IO)

class IFile
{
public:
	virtual uint32_t ReadData(void *a_Data, unsigned long a_DataSize) = 0;
	virtual bool IsOpen() const = 0;
	virtual bool Eof() const = 0;
	virtual void Seek(long a_Offset, EFilePos a_Pos = POS_CUR) = 0;
	virtual unsigned long GetSize() = 0;
	virtual operator bool() const = 0;
	virtual void Skip(unsigned long a_DataSize) = 0;
};

END_NAMESPACE(IO)

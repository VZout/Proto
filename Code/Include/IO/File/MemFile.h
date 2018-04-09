#pragma once

#include "IFile.h"
#include "Utility/NoCopy.h"

FORWARD_DECLARE(Memory, class MemoryBuffer)

BEGIN_NAMESPACE(IO)

class MemFile : public IFile, public Utility::NoCopy
{
public:
	MemFile(const Memory::MemoryBuffer &a_MemoryBuffer);
	virtual ~MemFile();

	uint32_t ReadData(void *a_Data, unsigned long a_DataSize) override;

	bool IsOpen() const override;
	bool Eof() const override;
	void Seek(long a_Offset, EFilePos a_Pos = POS_CUR) override;
	unsigned long GetSize() override;
	operator bool() const override;
	void Skip(unsigned long a_DataSize) override;

private:
	const Memory::MemoryBuffer &m_MemoryBuffer;
	uint32_t m_FilePointer = 0;
};

END_NAMESPACE(IO)

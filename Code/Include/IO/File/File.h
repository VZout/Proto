#pragma once

#include "IFile.h"

#include "BaseFile.h"
#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(IO)

class File : public BaseFile<std::fstream>, public IFile
{
public:
	File(const std::string &a_Filename, std::ios::openmode a_Mode = std::ios::in | std::ios::out);
	virtual ~File();

	bool Open(const std::string &a_Filename, std::ios::openmode a_Mode = std::ios::in | std::ios::out);
	void Close();

	void Write(const void *a_Data, uint32_t a_DataSize);
	void WriteLine(const std::string &a_Line);
	void WriteLine(const char *a_Msg, ...);

	template <class T>
	void Write(const T &a_Value)
	{
		Platform::AssertMessage(m_FileOpen, "Attempt to write to a file that is not opened!");
		m_Stream << a_Value;
	}

	uint32_t ReadData(void *a_Data, unsigned long a_DataSize);
	const std::string ReadLine(int a_Size = MAX_LINE_LENGTH, char a_Delimiter = '\n');

	void GetChar(char &a_Char);
	unsigned char GetChar();

	template<typename T>
	void Read(T &a_Value)
	{
		Platform::AssertMessage(m_FileOpen, "Attempt to read from a file that is not opened!");
		m_Stream >> a_Value;
	}

	void Skip(unsigned long a_DataSize);
	bool IsOpen() const override;
	bool Eof() const override;
	void Seek(long a_Offset, EFilePos a_Pos = POS_CUR) override;
	unsigned long GetSize() override;
	operator bool() const override;
};

template<>
inline void File::Read(std::string &a_Value)
{
	a_Value.reserve(GetSize());
	a_Value.assign((std::istreambuf_iterator<char>(m_Stream)), std::istreambuf_iterator<char>());
}

END_NAMESPACE(IO)

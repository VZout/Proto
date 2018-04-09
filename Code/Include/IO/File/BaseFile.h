#pragma  once

#include "Proto.h"

#include "EFilePos.h"
#include "Platform/Debug/AssertMessage.h"
#include "Utility/NoCopy.h"

#include <fstream>
#include <string>

BEGIN_NAMESPACE(IO)

#define MAX_LINE_LENGTH 256

template<typename T>
class BaseFile : public Utility::NoCopy
{
public:
    BaseFile()
	: m_Filename("")
	, m_FileOpen(false)
    {
    }

	BaseFile(const std::string &a_Filename, std::ios::openmode a_Mode = std::ios::in | std::ios::out)
		: m_Filename(a_Filename)
		, m_FileOpen(false)
		, m_Stream(a_Filename, a_Mode)
	{
	}
	
	virtual ~BaseFile()
    {
        if(m_FileOpen)
        {
            m_Stream.close();
            m_FileOpen = false;
        }
    }

    virtual bool Open(const std::string &a_Filename, std::ios::openmode a_Mode) = 0;

    void Close()
    {
        m_Stream.close();
        m_FileOpen = false;
    }

    bool IsOpen() const
	{ 
		return m_FileOpen; 
	}
    
	bool IsClosed() const
	{
		return !m_FileOpen;
	}

    bool GetState() const
	{
		return m_Stream.good();
	}

    bool Fail() const
	{
		return m_Stream.fail();
	}

	operator bool() const
	{
		return !m_Stream.bad();
	}

    bool Eof() const
	{
		return m_Stream.eof();
	}

    bool Bad() const
	{
		return m_Stream.bad();
	}

    const std::string& GetFilename() const
	{
		return m_Filename;
	}

    void Seek(long a_Offset, EFilePos a_Pos = POS_CUR)
    {
        switch(a_Pos)
        {
            case POS_BEG:
                {
                    m_Stream.seekg(static_cast<std::ios::streamoff>(a_Offset), std::ios::beg);
                }
                break;
            case POS_END:
                {
                    m_Stream.seekg(static_cast<std::ios::streamoff>(a_Offset), std::ios::end);
                }
                break;
            case POS_CUR:
                {
                    m_Stream.seekg(static_cast<std::ios::streamoff>(a_Offset), std::ios::cur);
                }
                break;
            default:
                {
                    Platform::AssertMessage("Invalid seek position passed!");
                }
                break;
        }
    }

    void ClearState()
	{ 
		m_Stream.clear();
	}

    unsigned long GetSize()
    {
		unsigned long currentPosition = static_cast<unsigned long>(m_Stream.tellg());
        m_Stream.seekg(0, std::ios::beg);
        unsigned long begin = static_cast<unsigned long>(m_Stream.tellg());
        m_Stream.seekg(0, std::ios::end);
        unsigned long end = static_cast<unsigned long>(m_Stream.tellg());
        m_Stream.seekg(currentPosition, std::ios::beg);
        return end - begin;
    }
    
protected:                    
    std::string m_Filename;
    bool m_FileOpen;
    T m_Stream;
};

END_NAMESPACE(IO)

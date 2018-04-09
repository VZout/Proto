#pragma once

#include "Proto.h"

#include <string>

BEGIN_NAMESPACE(Utility)

enum eHashFunction
{
    kSDBM,  /**< SDBM hash function */
    kDJB2,  /**< DJB2 hash function */
    kCRC32  /**< CRC32 hash function */
};

class HashedString
{
public:
	static const HashedString Empty;
	static const HashedString Invalid;

public:
	explicit HashedString(const char* a_String);
    explicit HashedString(const std::string& a_String = "");
    HashedString(const HashedString& a_Rhs);
	HashedString(unsigned long a_Hash);
    
    ~HashedString();
    
    const unsigned long GetHash() const { return( m_Hash ); }
    
    HashedString& operator = (const std::string& a_Rhs );
	HashedString& operator = (const HashedString& a_Rhs );
	HashedString& operator = (const HashedString&& a_Rhs);
	HashedString& operator = (const unsigned long a_Rhs );

    bool operator == (const HashedString& a_Rhs) const;
    bool operator != (const HashedString& a_Rhs) const;
    bool operator < (const HashedString& a_Rhs) const;
    bool operator > (const HashedString& a_Rhs) const;
    
    operator unsigned long();

#if defined(_DEBUG)
    const std::string GetString() const { return m_String; }
    const char* AsCString() const { return m_String.c_str(); }
#endif

private:
    unsigned long CalculateHash(const char* a_Chars, eHashFunction a_HashFunc = kCRC32);
    unsigned long m_Hash;

#if defined(_DEBUG)
    std::string m_String;
#endif
};

HashedString GenerateRandomHashedString();

END_NAMESPACE(Utility)

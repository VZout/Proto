#include "Utility/HashedString.h"

#include "Utility/AutoPointer.h"
#include "Utility/HashFunctions.h"
#include "Math/RNG/CreateRandomNumberGenerator.h"
#include "Math/RNG/IRandomNumberGenerator.h"

#include <algorithm>
#include <limits>

USING_NAMESPACE(Math)

BEGIN_NAMESPACE(Utility)

BEGIN_UNNAMEDNAMESPACE()

AutoPointer<IRandomNumberGenerator> g_RandomNumberGenerator = CreateRandomNumberGenerator(982451653);	// http://primes.utm.edu/lists/small/millions/

END_UNNAMEDNAMESPACE()

const HashedString HashedString::Empty = HashedString("");
const HashedString HashedString::Invalid = HashedString("__INVALID__");

HashedString::HashedString(const char* a_String)
#if !defined(NDEBUG)
	: m_String(std::string(a_String))
#endif
{
    m_Hash = CalculateHash(a_String);
}

HashedString::HashedString(const std::string &a_String)
#if !defined(NDEBUG)
	: m_String(std::string(a_String))
#endif
{
    m_Hash = CalculateHash(a_String.c_str());
}

HashedString::HashedString(const HashedString& a_HashedString)
#if !defined(NDEBUG)
	: m_String(std::string(a_HashedString.m_String))
#endif
{
    m_Hash = a_HashedString.m_Hash;
}

HashedString::HashedString(unsigned long a_Hash)
: m_Hash(a_Hash)
{
}

HashedString::~HashedString()
{

}

bool HashedString::operator == (const HashedString& a_Rhs) const
{
    return m_Hash == a_Rhs.m_Hash;
}

bool HashedString::operator != (const HashedString& a_Rhs) const
{
    return m_Hash != a_Rhs.m_Hash;
}

HashedString& HashedString::operator = (const HashedString& a_Rhs)
{
    m_Hash = a_Rhs.m_Hash;
#if !defined(NDEBUG)
    m_String = a_Rhs.m_String;
#endif
    return *this;
}

HashedString& HashedString::operator = (const std::string& a_Rhs)
{
#if !defined(NDEBUG)
    m_String = a_Rhs;
#endif
    m_Hash = CalculateHash(a_Rhs.c_str());
    return *this;
}

#if defined(PROTO_CPP11)
HashedString& HashedString::operator = (const HashedString&& a_Rhs)
{
	m_Hash = std::move(a_Rhs.m_Hash);
#if !defined(NDEBUG)
	m_String = std::move(a_Rhs.m_String);
#endif
	return *this;
}
#endif

HashedString& HashedString::operator = (const unsigned long a_Rhs)
{
	m_Hash = a_Rhs;
	return( *this );
}

bool HashedString::operator > (const HashedString& a_Rhs) const
{
    return(m_Hash > a_Rhs.m_Hash);
}

bool HashedString::operator < (const HashedString& a_Rhs) const
{
    return(m_Hash < a_Rhs.m_Hash);
}

HashedString::operator unsigned long()
{ 
	return m_Hash; 
}

unsigned long HashedString::CalculateHash(const char* pChars, eHashFunction hashFunc /*= kCRC32*/)
{
	unsigned long ulHash = static_cast<unsigned long>(-1);

	switch( hashFunc )
	{
	case kCRC32: 
		{ 
			ulHash = Utility::Crc32(pChars);
			break;
		}
	case kDJB2: 
		{ 
			ulHash = Utility::DJB2(pChars); 
			break;
		} 
	case kSDBM: 
		{ 
			ulHash = Utility::SDBM(pChars); 
			break;
		} 
	}

	return ulHash;
}

HashedString GenerateRandomHashedString()
{
	const unsigned long hashValue = static_cast<unsigned long>(g_RandomNumberGenerator->NextUint32(0, std::numeric_limits<uint32_t>::max()));
	return HashedString(hashValue);
}

END_NAMESPACE(Utility)

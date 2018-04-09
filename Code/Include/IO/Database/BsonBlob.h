#pragma once

#include "Resources/Helpers/ProcessBsonData.h"
#include "IO/Database/Helpers/BsonIncludes.h"
#include "Utility/NoCopy.h"

#include <string>

BEGIN_NAMESPACE(IO)

class BsonBlob : public Utility::NoCopy
{
public:
	BsonBlob();
	~BsonBlob();

	//void OutputKeys() const;
	template<typename T>
	T GetValue(const std::string &a_Key)
	{
		bson_iter_t iterator;
		bson_iter_t descendant;
		bson_iter_init(&iterator, m_BsonBlob);
		bson_iter_find_descendant(&iterator, a_Key.c_str(), &descendant);
		const bson_value_t *value = bson_iter_value(&descendant);
		return value->value.v_utf8.str;
	}

private:
	bson_t const *m_BsonBlob = nullptr;

	friend IO::BsonBlob* Resources::ProcessBsonData(const Resources::BsonData &a_SoundData, Memory::IMemoryPool &a_MemoryPool);
};

END_NAMESPACE(IO)

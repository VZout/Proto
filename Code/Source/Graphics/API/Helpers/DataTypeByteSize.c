#include "DataTypeByteSize.h"

#include <assert.h>

uint32_t DataTypeByteSize(GFXDataType a_Type)
{
	uint32_t byteSize = 0;
	switch (a_Type)
	{
	case DataType_Byte:
		{
			byteSize = 1;
			break;
		}
	case DataType_UnsignedByte:
		{
			byteSize = 1;
			break;
		}
	case DataType_Short:
		{
			byteSize = 2;
			break;
		}
	case DataType_UnsignedShort:
		{
			byteSize = 2;
			break;
		}
	case DataType_Int32:
		{
			byteSize = 4;
			break;
		}
	case DataType_UnsignedInt32:
		{
			byteSize = 4;
			break;
		}
	case DataType_Float:
		{
			byteSize = 4;
			break;
		}
	case DataType_Fixed:
		{
			byteSize = 4;
			break;
		}
	case DataType_Invalid:
	default:
		break;
	}
	assert(0 != byteSize);
	return byteSize;
}

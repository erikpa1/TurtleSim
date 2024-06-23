#include "crypto.h"


#include <random>
#include <chrono>

#include "../external/uuid/endianness.h"
#include "../external/uuid/uuid_v4.h"



namespace simstudio {

	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	String Crypto::Uuid_V4()
	{
		return uuidGenerator.getUUID().str();
	}

}


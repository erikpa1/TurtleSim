#include "crypto.h"


#include <random>
#include <chrono>

#include "../external/uuid/uuid_v4.h"




namespace simstudio {


#if IS_WINDOWS_PLATFORM
	UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	String Crypto::Uuid_V4()
	{
		return uuidGenerator.getUUID().str();
	}
#else
	String Crypto::Uuid_V4()
	{
		return UUID::New().String();
	}
#endif

}


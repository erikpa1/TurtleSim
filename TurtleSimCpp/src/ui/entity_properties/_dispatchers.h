#pragma once
#include "../../app/prelude.h"

#include "SimCore/Prelude.h"

namespace simstudio {

	class Source;
	class Buffer;
	class World;

	void DrawSource(Shared<World>& world, Shared<Source>& entity);
	void DrawBuffer(Shared<World>& world, Shared<Buffer>& entity);



}
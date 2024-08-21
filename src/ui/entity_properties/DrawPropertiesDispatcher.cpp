#include "imgui/imgui.h"

#include "DrawPropertiesDispatcher.h"

#include "../../app/prelude.h"

#include "_dispatchers.h"

#include "../uiapp.h"

namespace simstudio {

	void DrawPropertiesDispatcher::Draw()
	{
		if (_app->_activeEntity) {
			auto entity = _app->_activeEntity;

			const auto entity_type = entity->Type();

			if (entity_type == Source::ClassType()) {
				auto as_source = StaticCast<Source>(entity);
				DrawSource(_app->_world, as_source);
			}
			else if (entity_type == Buffer::ClassType()) {
				auto as_buffer = StaticCast<Buffer>(entity);
				DrawBuffer(_app->_world, as_buffer);
			}
			else {
				ImGui::Text(F("Uknown entity props {}", entity_type).c_str());
			}



		}

	}

}


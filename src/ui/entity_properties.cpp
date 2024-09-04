#include "entity_properties.h"

#include "../app/prelude.h"

#include "uiapp.h"


#include "imgui/imgui.h"



namespace simstudio {

	// Helper function to manage input for std::string
	void RenderStringInput(const char* label, String& str)
	{
		// Determine the initial buffer size, adjusting if necessary
		static const int initialBufferSize = 256;
		char buffer[initialBufferSize];

		// Copy the current std::string into the buffer
		strncpy(buffer, str.c_str(), sizeof(buffer));
		buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination

	// Render the label on the left
		ImGui::TextUnformatted(label);
		ImGui::SameLine();

		// Align the input field to the right
		float spacing = ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth();
		if (spacing > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

		// Render the InputText field
		if (ImGui::InputText("##hiddenLabelString", buffer, sizeof(buffer)))
		{
			str = buffer;  // Update the std::string if the input changes
		}
	}


	void RenderLabelValuePair(const char* label, char* inputBuffer, size_t bufferSize)
	{
		// Calculate the width of the label
		ImVec2 labelSize = ImGui::CalcTextSize(label);

		// Render the label on the left side
		ImGui::TextUnformatted(label);
		ImGui::SameLine();

		// Align the input field to the right
		float spacing = ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth();
		if (spacing > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

		// Render the InputText field
		ImGui::InputText("##hiddenLabel", inputBuffer, bufferSize);
	}


	void RenderLabelAndInputFloat(const char* label, float* value)
	{
		// Render the label on the left
		ImGui::TextUnformatted(label);
		ImGui::SameLine();

		// Align the input field to the right
		float spacing = ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth();
		if (spacing > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

		// Render the InputFloat field
		ImGui::InputFloat("##hiddenLabelFloat", value);
	}

	void RenderLabelAndInputInt(const char* label, int* value)
	{
		// Render the label on the left
		ImGui::TextUnformatted(label);
		ImGui::SameLine();

		// Align the input field to the right
		float spacing = ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth();
		if (spacing > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

		// Render the InputInt field
		ImGui::InputInt("##hiddenLabelInt", value);
	}

	void RenderLabelAndInputLong(const char* label, long* value)
	{
		// Render the label on the left
		ImGui::TextUnformatted(label);
		ImGui::SameLine();

		// Align the input field to the right
		float spacing = ImGui::GetContentRegionAvail().x - ImGui::CalcItemWidth();
		if (spacing > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + spacing);

		// Render the InputScalar field for long
		ImGui::InputScalar("##hiddenLabelLong", ImGuiDataType_S32, value);
	}

	float floatValue = 0.0f;
	int intValue = 0;
	long longValue = 0L;

	void EntityPropertiesView::Draw()
	{
		if (_app) {

			auto& entity = _app->_activeEntity;

			if (entity) {

				static char str0[128] = "Hello, world!";
				RenderLabelValuePair("Label 1:", str0, IM_ARRAYSIZE(str0));
				ImGui::Text("Some properties");

				ImGui::Text(entity->_name.c_str());
				ImGui::Text(entity->_uid.c_str());


				RenderStringInput("String Value:", entity->_name);
				RenderLabelAndInputFloat("Float Value:", &floatValue);
				RenderLabelAndInputInt("Int Value:", &intValue);
				RenderLabelAndInputLong("Long Value:", &longValue);


				_dispatcher.Draw();


			}
			else {
				ImGui::Text("No active entity");
			}
		}
		else {
			ImGui::Text("App is invalid");
		}


	}

	void EntityPropertiesView::SetApp(UiApp* app)
	{
		_app = app;
		_dispatcher._app = app;
	}

}
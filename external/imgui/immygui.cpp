
#include "imgui.h"
#include "immygui.h"

namespace ImGui {

	// Helper function to manage input for std::string
	void StringInput(const char* label, std::string& str)
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


	void CstrInput(const char* label, char* inputBuffer, size_t bufferSize)
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


	void FloatInput(const char* label, float* value)
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

	void IntInput(const char* label, int* value)
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

	void LongInput(const char* label, long* value)
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

}
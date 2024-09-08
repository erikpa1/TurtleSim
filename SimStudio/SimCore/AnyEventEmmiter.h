#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <string>
#include <memory>

#include "Prelude.h"


class AnyEventEmitter {
public:


	// Singleton access method
	static AnyEventEmitter& I() {
		static AnyEventEmitter instance;
		return instance;
	}

	// Register a member function and its instance with an event name
	template<typename T>
	void RegisterEvent(const String& eventName, std::shared_ptr<T> instance, void (T::* func)()) {
		// Create a weak_ptr to the instance and bind the member function
		std::weak_ptr<T> weakInstance = instance;
		events[eventName] = [weakInstance, func]() {
			// Check if the instance is still valid
			if (auto inst = weakInstance.lock()) {
				(inst.get()->*func)(); // Call the function on the valid instance
			}
			else {
				//LogE << F("Instance is no longer valid for event: {}", eventName);
			}
		};
	}

	// Emit the event by name
	void EmitEvent(const std::string& eventName) {
		auto it = events.find(eventName);
		if (it != events.end()) {
			it->second(); // Call the stored function
		}
		else {
			//LogE << F("No event found for: {}", eventName);
		}
	}

	// Clear unused (expired) events
	void ClearInvalidEvents() {
		for (auto it = events.begin(); it != events.end(); ) {
			// Check if the stored instance is still valid
			bool isValid = it->second != nullptr;
			if (!isValid) {
				it = events.erase(it); // Remove invalid event
			}
			else {
				++it;
			}
		}
	}

private:
	// Use unordered_map to map event names to the stored functions
	std::unordered_map<std::string, std::function<void()>> events;
};
#pragma once
#include "../prelude.h"

namespace simstudio {

	class ClassFactory {

		using ConstructFunction = std::function<Shared<void>()>;

	public:
		HashMap<ConstructFunction> _constructors;

		static ClassFactory* _instance;

	public:


		static ClassFactory* Instance();


		void RegisterConstructor(String type, ConstructFunction function);

		template<typename T>
		void RegisterClass() {
			RegisterConstructor(T::ClassType(), &T::New);
		}


		template<typename T>
		Shared<T> Construct(String type) {
			auto it = _constructors.find(type);
			if (it != _constructors.end()) {
				Shared<T> tmp = std::static_pointer_cast<T>(it->second());
				return tmp;
			}
			else {
				LogE << "Unable to find constructor of class [" << type << "]";

				for (const auto& iter : _constructors) {
					LogI << "--" << iter.first;
				}

			}
			return Share<T>();
		}

	};

}
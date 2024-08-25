#pragma once
#include "SimCore/Prelude.h"

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
				LogI << "Constructing class of type: [" << tmp->_type << "]";
				return tmp;
			}
			else {
				LogE << "Unable to find constructor of class [" << type << "]";

			}
			return Share<T>();
		}



	};

}
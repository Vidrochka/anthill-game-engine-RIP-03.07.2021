#ifndef at_engine_core
#define at_engine_core

namespace at::core::engine_core
{
	namespace at_interface
	{
		class IEngineCore
		{
		public:
			auto run() -> void;
		protected:
			virtual auto initialize_core() -> void = 0;
			virtual auto initialize_systems() -> void = 0;
			virtual auto initialize_modules() -> void = 0;
			virtual auto run_sycle() -> void = 0;
		};
	}
}

#endif //at_engine_core
#pragma once
#include <string>

namespace mns
{
	enum class log_types
	{
		none = 0, 
		reserved = 0x1, initialization = 0x2, tile_modification = 0x4, world_generation = 0x8, 
		entity_debug = 0x10
	};

	class logger
	{
	private:
		uint64_t l_mask;
	public:
		logger();
		virtual void log(const std::string& message);
		virtual void log(log_types type, const std::string& message);
		void set_mask_flag(log_types flag);
		void reset_mask_flag(log_types flag);
		bool get_mask_flag(log_types flag);
		virtual ~logger();
	};
}


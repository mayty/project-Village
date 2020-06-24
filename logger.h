#pragma once
#include <string>

namespace mns
{
	enum class log_types
	{
		none = 0, low = 0b1, high = 0b10
	};

	class logger
	{
	private:
		uint64_t l_mask;
	public:
		logger();
		logger(log_types max_type);
		virtual void log(const std::string& message);
		virtual void log(log_types type, const std::string& message);
		void set_mask_flag(log_types flag);
		void reset_mask_flag(log_types flag);
		bool get_mask_flag(log_types flag);
		virtual ~logger();
	};
}


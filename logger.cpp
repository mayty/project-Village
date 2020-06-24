#include "logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

#pragma warning(disable : 4996)

mns::logger::logger()
{
	l_mask = ~0ull;
}

mns::logger::logger(log_types max_type)
{
	l_mask = 0;
	uint64_t max = (uint64_t)max_type;
	uint64_t curr = 1;
	while (curr <= max)
	{
		l_mask |= curr;
		curr <<= 1;
	}
}

void mns::logger::log(const std::string& message)
{
	auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string time_str{ ctime(&time) };
	time_str.pop_back();
	std::cout << "[" << time_str << "]: ";
	std::cout << message << std::endl;
}

void mns::logger::log(log_types type, const std::string& message)
{
	if (get_mask_flag(type))
	{
		log(message);
	}
}

void mns::logger::set_mask_flag(log_types flag)
{
	l_mask |= (uint64_t)flag;
}

void mns::logger::reset_mask_flag(log_types flag)
{
	l_mask &= ~(uint64_t)flag;
}

bool mns::logger::get_mask_flag(log_types flag)
{
	return l_mask & (uint64_t)flag;
}

mns::logger::~logger()
{
}

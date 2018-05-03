#ifndef __TIME_H__
#define __TIME_H__

#include <chrono>

using namespace std::chrono_literals;

namespace CDP {

	class Time {

		Time();
		static Time m_instance;

		std::chrono::high_resolution_clock::time_point m_last;
		std::chrono::high_resolution_clock::time_point m_current;
		std::chrono::high_resolution_clock::duration m_delta_time;

	public:
		static Time& Instance();
		Time(const Time&) = delete;
		Time operator= (const Time&) = delete;
		~Time() = default;

		void Update();
		double DeltaTime();

	};

}

#endif

#pragma once

#include <string>
#include <chrono>
#include <set>
using pm_timer = std::chrono::system_clock;
using pm_milli = std::chrono::milliseconds;


namespace pm
{
    class timer final
    {
    public:
        timer();

    public:
        void start();
        void stop();
        std::string get_result();

        //gambiarra, favor ignorar
        template <typename F>
        void measure(int n, F func)
        {
            std::multiset<pm_milli> times;

            for (int i = 0; i < n; ++i) {
                this->start();
                func();
                this->stop();
                times.insert(m_result_milli);
            }

            m_result_milli = median(times);
        }

    private:
        pm_milli median(const std::multiset<pm_milli>& times);

    private:
        pm_timer::time_point m_start_point;
        pm_milli m_result_milli;
    };
}

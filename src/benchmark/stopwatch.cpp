#include "stopwatch.hpp"
#include <sstream>
#include <iomanip>
#include <cmath>


namespace pm
{
    /*---------------------------*/
    timer::timer()
    {

    }

    /*---------------------------*/
    void timer::start()
    {
        m_start_point = pm_timer::now();
    }

    /*---------------------------*/
    void timer::stop()
    {
        auto end_point = pm_timer::now();
        m_result_milli = std::chrono::duration_cast<pm_milli>(end_point - m_start_point);
    }

    /*---------------------------*/
    std::string timer::get_result()
    {
        auto millis = m_result_milli.count();

        auto hours = millis / 3600000;
        millis %= 3600000;
        auto minutes = millis / 60000;
        millis %= 60000;
        auto seconds = millis / 1000;
        auto milliseconds = millis % 1000;

        std::ostringstream os;
        os << std::setw(2) << std::setfill('0') << hours << ":"
           << std::setw(2) << std::setfill('0') << minutes << ":"
           << std::setw(2) << std::setfill('0') << seconds << ":"
           << std::setw(4) << std::setfill('0') << milliseconds;

        return os.str();
    }

    /*---------------------------*/
    pm_milli timer::median(const std::multiset<pm_milli>& times)
    {
        size_t len = times.size();

        if (len == 0)
            return pm_milli { 0 };

        auto it = times.begin();
        std::advance(it,len/2);

        if(len%2 == 0) {
            return *it;
        } else {
            auto it_prev = std::prev(it);
            auto res = (it_prev->count() + it->count()) / 2;
            return pm_milli {res};
        }
    }
}

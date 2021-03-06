#pragma once

#include <vector>

#include "portfolio.hpp"
#include "data.hpp"

namespace swr {

enum class Rebalancing : uint64_t {
    NONE,
    MONTHLY,
    YEARLY,
    THRESHOLD
};

Rebalancing parse_rebalance(const std::string& str);
std::ostream & operator<<(std::ostream& out, const Rebalancing & rebalance);

struct results {
    size_t successes = 0;
    size_t failures  = 0;

    float success_rate = 0.0f;

    float tv_average = 0.0f;
    float tv_minimum = 0.0f;
    float tv_maximum = 0.0f;
    float tv_median  = 0.0f;

    size_t worst_duration       = 0;
    size_t worst_starting_month = 0;
    size_t worst_starting_year  = 0;

    size_t lowest_eff_wr_year        = 0;
    size_t lowest_eff_wr_start_year  = 0;
    size_t lowest_eff_wr_start_month = 0;
    float lowest_eff_wr              = 0.0f;

    size_t highest_eff_wr_year        = 0;
    size_t highest_eff_wr_start_year  = 0;
    size_t highest_eff_wr_start_month = 0;
    float highest_eff_wr              = 0.0f;

    std::string message;
    bool error = false;

    void compute_terminal_values(std::vector<float> & terminal_values);
};

results simulation(const std::vector<swr::allocation>& portfolio, const std::vector<swr::data>& inflation_data, const std::vector<std::vector<swr::data>>& values, size_t years, float wr, size_t start_year, size_t end_year, bool monthly_wr, Rebalancing rebalance = Rebalancing::NONE, float threshold = 0.0f);

size_t simulations_ran();

} // namespace swr

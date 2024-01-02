#include "statistics_calculator.hpp"
#include <fstream>
#include <numeric>
#include <cmath>
#include <algorithm>

statistics::statistics(const std::vector<double> &input_data) : data(input_data)
{
    std::sort(data.begin(), data.end());
}

double statistics::mean() const
{
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

double statistics::median() const
{
    size_t n = data.size();

    if (n % 2 != 0)
    {
        return data[n / 2];
    }
    return (data[(n / 2) - 1] + data[n / 2]) / 2.0;
}

std::vector<double> statistics::mode() const
{
    int max_count = 0;
    std::vector<double> modes;
    double previous = data[0];
    int count = 1;

    for (size_t i = 1; i < data.size(); i++)
    {
        if (data[i] == previous)
        {
            count++;
        }
        else
        {
            if (count > max_count)
            {
                max_count = count;
                modes.clear();
                modes.emplace_back(previous);
            }
            else if (count == max_count)
            {
                modes.emplace_back(previous);
            }
            count = 1;
            previous = data[i];
        }
    }

    if (count > max_count)
    {
        modes.clear();
        modes.emplace_back(previous);
    }
    else if (count == max_count)
    {
        modes.emplace_back(previous);
    }

    return modes;
}

double statistics::variance() const
{
    double mean_value = mean();
    double variance_sum = 0.0;

    for (double num : data)
    {
        variance_sum += (num - mean_value) * (num - mean_value);
    }

    return variance_sum / (data.size() - 1);
}

double statistics::standard_deviation() const
{
    return std::sqrt(variance());
}

void statistics::print_statistics() const
{
    std::cout << *this;

    std::ofstream output_file("output.txt", std::ios::app);

    if (!output_file)
    {
        std::cout << "Error opening the output file. Exiting program." << std::endl;
        exit(1);
    }
    output_file << *this;
    output_file.close();
}

std::ostream &operator<<(std::ostream &os, const statistics &stats)
{
    os << std::fixed << std::setprecision(1);
    os << "-------------------------------------------------" << std::endl;
    os << "Set: {";
    for (size_t i = 0; i < stats.data.size(); i++)
    {
        os << stats.data[i];
        if (i != stats.data.size() - 1)
            os << ", ";
    }
    os << "}" << std::endl;
    os << "Mean: " << stats.mean() << std::endl;
    os << "Median: " << stats.median() << std::endl;

    std::vector<double> modes = stats.mode();

    if (modes.size() == 1)
    {
        os << "Mode: " << modes[0] << std::endl;
    }
    else
    {
        os << "Modes: ";
        for (size_t i = 0; i < modes.size(); i++)
        {
            os << modes[i];
            if (i != modes.size() - 1)
                os << ", ";
        }
        os << std::endl;
    }
    os << "Variance: " << stats.variance() << std::endl;
    os << "Standard Deviation: " << stats.standard_deviation() << std::endl;
    os << "-------------------------------------------------" << std::endl;
    return os;
}
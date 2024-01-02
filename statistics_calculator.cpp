#include "statistics_calculator.hpp"
#include <fstream>
#include <numeric>
#include <cmath>
#include <algorithm>

// Constructor: Initializes the data member and sorts the input data.
statistics::statistics(const std::vector<double> &input_data) : data(input_data)
{
    std::sort(data.begin(), data.end());
}

// Calculate and return the mean of the data.
double statistics::mean() const
{
    return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}

// Calculate and return the median of the data.
double statistics::median() const
{
    size_t n = data.size();
    if (n % 2 != 0)
    {
        return data[n / 2];
    }
    return (data[(n / 2) - 1] + data[n / 2]) / 2.0;
}

// Calculate and return the mode(s) of the data.
std::vector<double> statistics::mode() const
{
    std::vector<double> modes;
    if (data.empty())
        return modes;

    int max_count = 1;
    int current_count = 1;
    double previous = data[0];
    modes.push_back(previous);

    for (size_t i = 1; i < data.size(); i++)
    {
        if (data[i] == previous)
        {
            current_count++;
        }
        else
        {
            if (current_count > max_count)
            {
                max_count = current_count;
                modes.clear();
                modes.push_back(data[i - 1]);
            }
            else if (current_count == max_count)
            {
                modes.push_back(data[i - 1]);
            }
            current_count = 1;
        }
        previous = data[i];
    }

    if (current_count > max_count)
    {
        modes.clear();
        modes.push_back(data.back());
    }
    else if (current_count == max_count)
    {
        modes.push_back(data.back());
    }

    return modes;
}

// Calculate and return the variance of the data.
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

// Calculate and return the standard deviation of the data.
double statistics::standard_deviation() const
{
    return std::sqrt(variance());
}

// Print all statistics to console and to a file named "output.txt".
void statistics::print_statistics() const
{
    std::cout << *this;

    std::ofstream output_file("output.txt", std::ios::app);

    if (!output_file)
    {
        std::cerr << "Error opening the output file. Exiting program." << std::endl;
        exit(1);
    }
    output_file << *this;
    output_file.close();
}

// Overload the << operator to format the printing of statistics.
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

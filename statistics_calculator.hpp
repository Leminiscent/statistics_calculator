#ifndef statistics_calculator_hpp
#define statistics_calculator_hpp

#include <vector>
#include <iostream>
#include <iomanip>

class statistics
{
private:
    std::vector<double> data; // Vector to store the dataset.

public:
    // Constructor that takes a vector of doubles as input.
    statistics(const std::vector<double> &input_data);

    // Methods to calculate various statistics.
    double mean() const;               // Calculate the mean of the data.
    double median() const;             // Calculate the median of the data.
    std::vector<double> mode() const;  // Calculate the mode(s) of the data.
    double variance() const;           // Calculate the variance of the data.
    double standard_deviation() const; // Calculate the standard deviation of the data.

    // Method to print all the statistics.
    void print_statistics() const;

    // Overload the << operator to enable easy printing of statistics.
    friend std::ostream &operator<<(std::ostream &os, const statistics &stats);
};

#endif

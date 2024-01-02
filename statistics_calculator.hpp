#ifndef statistics_calculator_hpp
#define statistics_calculator_hpp

#include <vector>
#include <iostream>
#include <iomanip>

class statistics
{
private:
    std::vector<double> data;

public:
    statistics(const std::vector<double> &input_data);
    double mean() const;
    double median() const;
    std::vector<double> mode() const;
    double variance() const;
    double standard_deviation() const;
    void print_statistics() const;
    friend std::ostream& operator<<(std::ostream& os, const statistics& stats);
};

#endif
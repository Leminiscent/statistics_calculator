#include "statistics_calculator.hpp"
#include <limits>

int main()
{
    char choice;

    do
    {
        int n;

        std::cout << "Please input size of the dataset to be calculated: ";
        while (!(std::cin >> n) || n <= 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a positive integer: ";
        }

        std::vector<double> set;

        set.reserve(n);
        std::cout << "Please input each element of the dataset:" << std::endl;
        for (int i = 0; i < n; ++i)
        {
            double x;
            while (!(std::cin >> x))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input. Please enter a double: ";
            }
            set.emplace_back(x);
        }

        statistics stats(set);
        
        stats.print_statistics();

        std::cout << "Do you want to input another dataset? (Y/N): ";
        std::cin >> choice;
        while (std::toupper(choice) != 'Y' && std::toupper(choice) != 'N')
        {
            std::cerr << "Invalid choice. Enter Y or N: ";
            std::cin >> choice;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (std::toupper(choice) == 'Y');

    return 0;
}
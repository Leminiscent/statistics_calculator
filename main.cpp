#include "statistics_calculator.hpp" // Include the header file for the statistics class.
#include <limits>                    // Include for using numeric limits.

int main()
{
    char choice; // Variable to store the user's choice to continue or not.

    do
    {
        int n; // Variable to store the number of elements in the dataset.

        // Prompt the user for the size of the dataset.
        std::cout << "Please input size of the dataset to be calculated: ";
        // Input validation for a positive integer.
        while (!(std::cin >> n) || n <= 0)
        {
            std::cin.clear();                                                   // Clear the error state of cin.
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
            std::cerr << "Invalid input. Please enter a positive integer: ";    // Error message for invalid input.
        }

        std::vector<double> set; // Vector to store the dataset.

        set.reserve(n); // Reserve space for n elements to improve efficiency.
        std::cout << "Please input each element of the dataset:" << std::endl;
        // Loop to get n elements from the user.
        for (int i = 0; i < n; ++i)
        {
            double x; // Variable to store the current input.
            // Input validation for a double.
            while (!(std::cin >> x))
            {
                std::cin.clear();                                                   // Clear the error state of cin.
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line.
                std::cerr << "Invalid input. Please enter a double: ";              // Error message for invalid input.
            }
            set.emplace_back(x); // Add the input to the dataset.
        }

        statistics stats(set); // Create a statistics object with the dataset.

        stats.print_statistics(); // Calculate and print the statistics.

        // Prompt the user to continue or exit.
        std::cout << "Do you want to input another dataset? (Y/N): ";
        std::cin >> choice;
        // Input validation for Y or N.
        while (std::toupper(choice) != 'Y' && std::toupper(choice) != 'N')
        {
            std::cerr << "Invalid choice. Enter Y or N: "; // Error message for invalid choice.
            std::cin >> choice;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line after the choice.

    } while (std::toupper(choice) == 'Y'); // Continue if the choice is 'Y' or 'y'.

    return 0; // End of the program.
}

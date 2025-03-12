#include <iostream>
#include <stdexcept>
#include <string>
#include "Filesystem.h"
#include <limits>

static void printMenu() {
    std::cout << "\nChoose an option:\n"
              << " 1. List current directory contents (brief)\n"
              << " 2. List current directory contents (long format)\n"
              << " 3. Change directory\n"
              << " 4. Go to root directory\n"
              << " 5. Exit\n"
              << "Enter your choice: ";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filesystem file>\n";
        return 1;
    }

    try {
        // Construct the filesystem from the provided file
        seneca::Filesystem fs(argv[1]);

        bool done = false;
        while (!done) {
            std::cout << "\nCurrent directory: " 
                      << fs.get_current_directory()->path() << "\n";

            // Print the menu of options
            printMenu();

            int choice{};
            if (!(std::cin >> choice)) {
                // Handle invalid input (e.g., non-numeric)
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid input, please try again.\n";
                continue;
            }

            // Clear any trailing input (like newline)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1: {
                    // List current directory contents (brief)
                    fs.get_current_directory()->display(std::cout);
                    break;
                }
                case 2: {
                    // List current directory contents (long format)
                    std::vector<seneca::FormatFlags> flags;
                    flags.push_back(seneca::FormatFlags::LONG);
                    fs.get_current_directory()->display(std::cout, flags);
                    break;
                }
                case 3: {
                    // Change directory
                    std::cout << "Enter directory name (e.g., images/): ";
                    std::string dirname;
                    std::getline(std::cin, dirname);

                    if (dirname.empty()) {
                        std::cerr << "No directory name provided.\n";
                        break;
                    }
                    try {
                        fs.change_directory(dirname);
                    } catch (const std::invalid_argument& ex) {
                        std::cerr << "Error: " << ex.what() << "\n";
                    }
                    break;
                }
                case 4: {
                    // Go to root directory
                    fs.change_directory("");
                    std::cout << "You are now at the root directory.\n";
                    break;
                }
                case 5: {
                    // Exit
                    done = true;
                    break;
                }
                default: {
                    std::cerr << "Unknown option. Please try again.\n";
                    break;
                }
            }
        }
    } 
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }

    std::cout << "Exiting program.\n";
    return 0;
}


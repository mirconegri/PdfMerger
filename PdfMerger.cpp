// FileMerger.cpp
// Merges all regular files in the same folder as the executable into one file.
// Improvements:
// - Clear handling of sort order (ascending / descending)
// - Explicit note: date = last modification time (portable)
// - Cross-platform executable exclusion
// - Safer input validation
// - Deterministic behavior
// Compatible with C++17

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;

// Enum for different sorting options
enum class OrderType {
    NAME = 1,   // Sort by file name
    DATE = 2,   // Sort by last modification date
    SIZE = 3    // Sort by file size
};

int main() {
    const std::string outputFileName = "merged_output.txt"; // Name of the merged output file
    std::vector<fs::directory_entry> files; // Vector to store files to merge

    int orderChoice;     // User choice for sorting order
    int directionChoice; // User choice for ascending/descending

    // Prompt user for sorting order
    std::cout << "Choose merge order:\n";
    std::cout << "1 - By file name\n";
    std::cout << "2 - By last modification date\n";
    std::cout << "3 - By file size\n";
    std::cout << "Selection: ";
    std::cin >> orderChoice;

    // Validate user input for order
    if (orderChoice < 1 || orderChoice > 3) {
        std::cerr << "Invalid order selection.\n";
        return 1;
    }

    // Prompt user for sorting direction
    std::cout << "\nChoose sort direction:\n";
    std::cout << "1 - Ascending\n";
    std::cout << "2 - Descending\n";
    std::cout << "Selection: ";
    std::cin >> directionChoice;

    // Validate user input for direction
    if (directionChoice < 1 || directionChoice > 2) {
        std::cerr << "Invalid direction selection.\n";
        return 1;
    }

    bool ascending = (directionChoice == 1); // true if ascending, false if descending
    OrderType order = static_cast<OrderType>(orderChoice); // Convert input to enum

    fs::path currentDir = fs::current_path();      // Get current directory path
    fs::path executablePath = fs::canonical(fs::path("./")); // Canonical path of executable

    // Iterate through files in the current directory
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (!entry.is_regular_file()) {
            continue; // Skip directories and non-regular files
        }

        fs::path filePath = entry.path();
        std::string fileName = filePath.filename().string();

        // Skip the output file to avoid including itself
        if (fileName == outputFileName) {
            continue;
        }

#ifdef _WIN32
        // Skip the executable file on Windows
        if (filePath.extension() == ".exe") {
            continue;
        }
#else
        // Skip files with execute permission on Unix-based systems
        if ((fs::status(filePath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
            continue;
        }
#endif

        files.push_back(entry); // Add valid file to the list
    }

    // Comparator lambda function for sorting based on user choice
    auto comparator = [&](const fs::directory_entry& a,
                          const fs::directory_entry& b) {
        bool result = false;

        switch (order) {
            case OrderType::NAME:
                result = a.path().filename().string() < b.path().filename().string();
                break;

            case OrderType::DATE:
                // Uses last modification time (portable across platforms)
                result = fs::last_write_time(a) < fs::last_write_time(b);
                break;

            case OrderType::SIZE:
                result = fs::file_size(a) < fs::file_size(b);
                break;
        }

        // Apply ascending or descending order
        return ascending ? result : !result;
    };

    // Sort the files according to the comparator
    std::sort(files.begin(), files.end(), comparator);

    // Open output file in binary mode
    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: cannot create output file.\n";
        return 1;
    }

    // Merge file contents into the output file
    for (const auto& entry : files) {
        fs::path filePath = entry.path();
        std::string fileName = filePath.filename().string();

        std::ifstream inputFile(filePath, std::ios::binary); // Open input file in binary mode
        if (!inputFile) {
            std::cerr << "Warning: cannot open file " << fileName << "\n";
            continue;
        }

        // Add header indicating the start of a file
        outputFile << "\n\n===== BEGIN FILE: " << fileName << " =====\n\n";

        // Write the contents of the file
        outputFile << inputFile.rdbuf();

        // Add footer indicating the end of a file
        outputFile << "\n\n===== END FILE: " << fileName << " =====\n";

        inputFile.close(); // Close input file
    }

    outputFile.close(); // Close output file

    std::cout << "\nFiles successfully merged into " << outputFileName << "\n";
    return 0;
}

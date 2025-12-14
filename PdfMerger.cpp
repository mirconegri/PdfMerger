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

enum class OrderType {
    NAME = 1,
    DATE = 2,
    SIZE = 3
};

int main() {
    const std::string outputFileName = "merged_output.txt";
    std::vector<fs::directory_entry> files;

    int orderChoice;
    int directionChoice;

    std::cout << "Choose merge order:\n";
    std::cout << "1 - By file name\n";
    std::cout << "2 - By last modification date\n";
    std::cout << "3 - By file size\n";
    std::cout << "Selection: ";
    std::cin >> orderChoice;

    if (orderChoice < 1 || orderChoice > 3) {
        std::cerr << "Invalid order selection.\n";
        return 1;
    }

    std::cout << "\nChoose sort direction:\n";
    std::cout << "1 - Ascending\n";
    std::cout << "2 - Descending\n";
    std::cout << "Selection: ";
    std::cin >> directionChoice;

    if (directionChoice < 1 || directionChoice > 2) {
        std::cerr << "Invalid direction selection.\n";
        return 1;
    }

    bool ascending = (directionChoice == 1);
    OrderType order = static_cast<OrderType>(orderChoice);

    fs::path currentDir = fs::current_path();
    fs::path executablePath = fs::canonical(fs::path("./"));

    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        fs::path filePath = entry.path();
        std::string fileName = filePath.filename().string();

        if (fileName == outputFileName) {
            continue;
        }

#ifdef _WIN32
        if (filePath.extension() == ".exe") {
            continue;
        }
#else
        if ((fs::status(filePath).permissions() & fs::perms::owner_exec) != fs::perms::none) {
            continue;
        }
#endif

        files.push_back(entry);
    }

    auto comparator = [&](const fs::directory_entry& a,
                          const fs::directory_entry& b) {
        bool result = false;

        switch (order) {
            case OrderType::NAME:
                result = a.path().filename().string() <
                         b.path().filename().string();
                break;

            case OrderType::DATE:
                // Uses last modification time (portable across platforms)
                result = fs::last_write_time(a) <
                         fs::last_write_time(b);
                break;

            case OrderType::SIZE:
                result = fs::file_size(a) <
                         fs::file_size(b);
                break;
        }

        return ascending ? result : !result;
    };

    std::sort(files.begin(), files.end(), comparator);

    std::ofstream outputFile(outputFileName, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: cannot create output file.\n";
        return 1;
    }

    for (const auto& entry : files) {
        fs::path filePath = entry.path();
        std::string fileName = filePath.filename().string();

        std::ifstream inputFile(filePath, std::ios::binary);
        if (!inputFile) {
            std::cerr << "Warning: cannot open file " << fileName << "\n";
            continue;
        }

        outputFile << "\n\n===== BEGIN FILE: " << fileName << " =====\n\n";
        outputFile << inputFile.rdbuf();
        outputFile << "\n\n===== END FILE: " << fileName << " =====\n";

        inputFile.close();
    }

    outputFile.close();

    std::cout << "\nFiles successfully merged into "
              << outputFileName << "\n";
    return 0;
}

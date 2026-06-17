// PdfMerger.cpp
// Merges all PDF files found in the same folder as the executable into one PDF.
// The user is first asked how to sort the files (by name or by modification date),
// then whether the order should be ascending or descending.
//
// IMPORTANT: PDF files cannot be merged by simply gluing their bytes together
// the way plain text files can. Each PDF stores its own internal cross-reference
// table and trailer, so the actual merge is done with Ghostscript, a free
// command-line tool that understands the PDF format. Ghostscript must be
// installed and available on your PATH: https://ghostscript.com/releases/gsdnld.html
//
// Compatible with C++17

#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cctype>

namespace fs = std::filesystem;

// The two ways the user can choose to sort the files
enum class OrderType {
    NAME = 1,  // Alphabetical order (numeric file names are compared as numbers)
    DATE = 2   // Last modification date
};

// Returns true if a string is made up only of digits, e.g. "12"
bool isNumericName(const std::string& name) {
    if (name.empty()) {
        return false;
    }
    for (char c : name) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

// Returns true if the file has a ".pdf" extension (case insensitive)
bool isPdfFile(const fs::path& filePath) {
    std::string extension = filePath.extension().string();
    for (char& c : extension) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }
    return extension == ".pdf";
}

int main() {
    const std::string outputFileName = "merged_output.pdf";
    std::vector<fs::directory_entry> files;

    int orderChoice;
    int directionChoice;

    // Ask the user how to sort the files
    std::cout << "Choose merge order:\n";
    std::cout << "1 - Alphabetical order (numeric names are sorted correctly too)\n";
    std::cout << "2 - Last modification date\n";
    std::cout << "Selection: ";
    std::cin >> orderChoice;

    if (orderChoice < 1 || orderChoice > 2) {
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

    // Collect every PDF file in the current folder
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        if (!isPdfFile(entry.path())) {
            continue;
        }

        // Skip a previously merged file so it doesn't get merged into itself
        if (entry.path().filename().string() == outputFileName) {
            continue;
        }

        files.push_back(entry);
    }

    if (files.empty()) {
        std::cout << "No PDF files found in this folder.\n";
        return 0;
    }

    // Comparator used to sort the files
    auto comparator = [&](const fs::directory_entry& a, const fs::directory_entry& b) {
        bool result = false;

        if (order == OrderType::NAME) {
            std::string nameA = a.path().stem().string();
            std::string nameB = b.path().stem().string();

            if (isNumericName(nameA) && isNumericName(nameB)) {
                result = std::stoi(nameA) < std::stoi(nameB);
            } else {
                result = nameA < nameB;
            }
        } else {
            result = fs::last_write_time(a) < fs::last_write_time(b);
        }

        return ascending ? result : !result;
    };

    std::sort(files.begin(), files.end(), comparator);

    // Build the Ghostscript command that merges every PDF in the chosen order
#ifdef _WIN32
    std::string command = "gswin64c -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=" + outputFileName;
#else
    std::string command = "gs -dBATCH -dNOPAUSE -q -sDEVICE=pdfwrite -sOutputFile=" + outputFileName;
#endif

    for (const auto& entry : files) {
        command += " \"" + entry.path().filename().string() + "\"";
    }

    std::cout << "\nMerging " << files.size() << " PDF file(s)...\n";
    int exitCode = std::system(command.c_str());

    if (exitCode != 0) {
        std::cerr << "Merge failed. Make sure Ghostscript is installed and on your PATH.\n";
        return 1;
    }

    std::cout << "Files successfully merged into " << outputFileName << "\n";
    return 0;
}

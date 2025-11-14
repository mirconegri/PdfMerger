#include "PdfMerger.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

int main() {
    PdfMerger merger;

    // Get the current working directory (where the executable is running)
    fs::path exePath = fs::current_path();

    vector<string> pdfFiles;

    // Scan all items in the directory and pick only regular PDF files
    for (const auto& entry : fs::directory_iterator(exePath)) {
        // Check: is it a file AND does it have .pdf extension?
        if (entry.is_regular_file() && entry.path().extension() == ".pdf") {
            pdfFiles.push_back(entry.path().string());
        }
    }

    // Sort the PDF filenames alphabetically to determine merge order
    sort(pdfFiles.begin(), pdfFiles.end());

    // If no PDFs were found, stop the program
    if (pdfFiles.empty()) {
        cerr << "⚠️ No PDF files found in the current folder.\n";
        return 1;
    }

    // Display the PDF files found
    cout << "📂 Found " << pdfFiles.size() << " PDF files:\n";
    for (const auto& f : pdfFiles)
        cout << "   " << fs::path(f).filename().string() << endl;

    // Ask the user for the name of the output file
    string outputFile;
    cout << "\n📝 Enter the name for the merged file (press Enter for 'merged.pdf'):\n> ";
    getline(cin, outputFile);

    // If user entered nothing → use default
    if (outputFile.empty())
        outputFile = "merged.pdf";
    // If user did not include .pdf, append it
    else if (!outputFile.ends_with(".pdf"))
        outputFile += ".pdf";

    cout << "\n🔧 Creating merged file: " << outputFile << endl;

    // Add all PDF files to the merger in sorted order
    for (const auto& f : pdfFiles)
        merger.addFile(f);

    // Perform the actual PDF merge
    merger.merge(outputFile);

    cout << "✅ Merge completed successfully! (" << outputFile << ")\n";
    return 0;
}
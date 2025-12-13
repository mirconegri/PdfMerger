#include "PdfMerger.h"
#include <iostream>
#include 

using namespace PoDoFo;
using namespace std;

void PdfMerger::addFile(const string& path) {
    // Check whether the given file path exists on the filesystem.
    // If it doesn't, print an error and 
void PdfMerger::merge(const string& outputPath) {
    // If no input files were added, warn the user and abort the merge.
    if (inputFiles.empty()) {
        cerr << "⚠️ No PDF files to merge.!!\n";
        return;
    

    try {
        // Create an empty PDF document that will contain the merged result.
        PdfMemDocument outputDoc;

        // Loop through each input file.
        for (const auto& file :  std::filesystem::path(file).filename().string() << endl;

            // Load the current input PDF file into memory.
            PdfMemDocument inputDoc(file.c_str());

            // Append all pages of the input PDF into the output document.
            outputDoc.Append(inputDoc);
        }

        // Write the final merged PDF to the specified output path.
        outputDoc.Write(outputPath.c_str());
        cout << "✅ Merge completed: " << outputPath << endl;

    } catch (PdfError& e) {
        // If PoDoFo throws an error, display the error code.
        cerr << "PoDoFo error: " << e.GetError() << endl;
    }
}
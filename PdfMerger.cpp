#include "PdfMerger.h"
#include <iostream>
#include <filesystem>

using namespace PoDoFo;
using namespace std;

void PdfMerger::addFile(const string& path) {
    if (!std::filesystem::exists(path)) {
        cerr << "❌ File not found: " << path << endl;
        return;
    }
    inputFiles.push_back(path);
}

void PdfMerger::merge(const string& outputPath) {
    if (inputFiles.empty()) {
        cerr << "⚠️ No PDF files to merge.!!\n";
        return;
    }

    try {
        PdfMemDocument outputDoc;

        for (const auto& file : inputFiles) {
            cout << "📄 Adding: " << std::filesystem::path(file).filename().string() << endl;
            PdfMemDocument inputDoc(file.c_str());
            outputDoc.Append(inputDoc);
        }

        outputDoc.Write(outputPath.c_str());
        cout << "✅ Merge completed: " << outputPath << endl;

    } catch (PdfError& e) {
        cerr << "PoDoFo error: " << e.GetError() << endl;
    }
}

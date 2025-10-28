#include "PdfMerger.h"
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

int main() {
    PdfMerger merger;

    // Ottiene la cartella corrente (dove si trova l'eseguibile)
    fs::path exePath = fs::current_path();

    vector<string> pdfFiles;

    // Cerca tutti i PDF nella stessa cartella
    for (const auto& entry : fs::directory_iterator(exePath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".pdf") {
            pdfFiles.push_back(entry.path().string());
        }
    }

    // Ordina alfabeticamente
    sort(pdfFiles.begin(), pdfFiles.end());

    if (pdfFiles.empty()) {
        cerr << "⚠️ No PDF files found in the current folder.\n";
        return 1;
    }

    cout << "📂 Found " << pdfFiles.size() << " PDF files:\n";
    for (const auto& f : pdfFiles)
        cout << "   " << fs::path(f).filename().string() << endl;

    // Chiede come nominare il file finale
    string outputFile;
    cout << "\n📝 Enter the name for the merged file (press Enter for 'merged.pdf'):\n> ";
    getline(cin, outputFile);

    if (outputFile.empty())
        outputFile = "merged.pdf";
    else if (!outputFile.ends_with(".pdf"))
        outputFile += ".pdf";

    cout << "\n🔧 Creating merged file: " << outputFile << endl;

    // Aggiunge tutti i PDF in ordine
    for (const auto& f : pdfFiles)
        merger.addFile(f);

    merger.merge(outputFile);

    cout << "✅ Merge completed successfully! (" << outputFile << ")\n";
    return 0;
}

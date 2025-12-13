#include "PdfMerger.h"
#include <iostream>
#include 

using namespace PoDoFo;
using namespace std;

void PdfMerger::addFile(const string& path) {
    // Check whether the given file path exists on the filesystem.
    // If it doesn't, print an error ";
        return;
    

    try {
        // Create an empty PDF document that will contain the merged result.
        PdfMemDocument outputDoc;

        // Loop through each input file.
        for (const auto& file :  

        // Write the final merged 
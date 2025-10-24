# PDF Merger CLI - C++ 📝📚

![PDF Merge](https://img.shields.io/badge/Language-C++17-blue?style=for-the-badge) ![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

A simple **command-line application** to merge multiple PDF files into a single PDF file. The program automatically detects all PDF files in the same folder as the executable, sorts them alphabetically, and merges them. The user only needs to provide the name for the output file. ✅

---

## ✨ Features

- 📂 Automatically detects all PDF files in the same folder as the executable  
- 🔤 Sorts PDF files alphabetically  
- 📑 Merges PDFs into a single output file  
- 💻 Minimal, lightweight command-line interface  
- 🌍 Cross-platform (Windows, Linux, MacOS with minor adjustments)  

---

## ⚙️ Requirements

- 🖥️ **C++17 compatible compiler** (e.g., `g++` via MinGW-w64 on Windows, `g++`/`clang` on Linux/macOS)  
- 🛠️ **CMake** (version ≥ 3.10)  
- 📚 **PoDoFo library** installed for PDF manipulation ([PoDoFo official site](https://podofo.sourceforge.io/))  

---

## 🛠️ Installation

1. Clone the repository:

```
git clone https://github.com/<your-username>/PDFMergerCLI.git
cd PDFMergerCLI
```
2. Ensure PoDoFo is installed on your system.

3. Install C++ compiler:

- Windows: MinGW-w64 or MSYS2

- Linux: sudo apt install g++ cmake libpodofo-dev

- MacOS: brew install gcc cmake podofo

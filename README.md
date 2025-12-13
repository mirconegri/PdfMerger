# PDF Merger - C++ 📝📚


[![PDF Merge](https://img.shields.io/badge/Language-C++-red?style=for-the-badge)](https://cplusplus.com/) [![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE) 

A simple **command-line application** to merge multiple PDF files into a single PDF file. The program automatically detects all PDF files in the same folder as the executable, sorts them alphabetically, and merges them. The user only needs to provide the name for the output file. ✅

---

## ✨ Features

- 📂 Automatically `detects` all PDF files in the same folder as the executable  
- 🔤 `Sorts` PDF files alphabetically  
- 📑 `Merges` PDFs into a single output file  
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
git clone https://github.com/mirconegri/PdfMerger.git
cd PDFMerger
```
2. Ensure PoDoFo is installed on your system.
3. Install C++ compiler:
- Windows:
```
MinGW-w64 or MSYS2
```
- Linux:
```
sudo apt install g++ cmake libpodofo-dev
```
- MacOS:
```
brew install gcc cmake podofo
```

---

## 🏗️ Build Instructions

1. Create a build directory and navigate into it:
```
mkdir build
cd build
```
2. Configure the project with CMake:
```
cmake ..
```
3. Build the executable:
```
cmake --build .
```
The executable (pdfmerge on Linux/macOS or pdfmerge.exe on Windows) will be created inside the build folder. ⚡

---

## 🚀 Usage

How to Use

1. Place the executable in the folder containing the files you want to merge.


2. Run the program:

```./FileMerger```

3. Choose the merge order when prompted:

1 - By file name
2 - By last modification date
3 - By file size

4. Choose the sort direction:

1 - Ascending
2 - Descending

5. The merged result will be saved as:
`merged_output.txt`


---

## 📜 License

MIT License © 2025 `Mirco Negri`
— see [LICENSE](LICENSE) file for details.

---

## 👤 Author

`Mirco Negri`
GitHub: https://github.com/mirconegri
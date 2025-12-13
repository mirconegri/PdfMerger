# File Merger - C++ 🗂️

 

A simple command-line application to merge multiple files into a single output file. The program processes all regular files located in the same folder as the executable, lets the user choose the merge order and direction, and produces a deterministic merged result. ✅


---


## ✨ Features


📂 Automatically detects all regular files in the executable folder

🔀 User-defined merge order:

🔤 File name

🕒 Last modification date

📏 File size


↕️ Ascending or descending order selection

📄 Merges file contents into a single output file

💻 Minimal, lightweight command-line interface

🌍 Cross-platform (Windows, Linux, macOS)



---


## ⚙️ Requirements

- 🖥️ C++17 compatible compiler (g++, clang, or MSVC)

- 📚 Uses only the C++17 standard library (<filesystem>, <fstream>, <algorithm>)

- No external libraries are required.


---


## 🛠️ Installation

1. Clone the repository:

git clone https://github.com/mirconegri/FileMerger.git
cd FileMerger

2. Ensure a C++17 compiler is installed on your system.

---

## 🏗️ Build Instructions

- ### Linux / macOS

g++ -std=c++17 FileMerger.cpp -o FileMerger

- ### Windows (MinGW)

g++ -std=c++17 FileMerger.cpp -o FileMerger.exe

- ### Windows (Visual Studio)

cl /std:c++17 FileMerger.cpp

The executable will be generated in the current directory. ⚡

---

## 🚀 Usage

1. Place the executable in the folder containing the files you want to merge.

2. Run the program:

`./FileMerger`

3. Choose the merge order when prompted:

- By file name  
- By last modification date  
- By file size

4. Choose the sort direction:

- Ascending  
- Descending

5. The merged result will be saved as:

`merged_output.txt`

in the same directory. ✅

---

## 📜 License

MIT License © 2025 `Mirco Negri`  
— see [LICENSE](LICENSE) file for details.

---

## 👤 Author

`Mirco Negri`  
GitHub: https://github.com/mirconegri

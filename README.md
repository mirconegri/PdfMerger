# File Merger - C++ 🗂️

[![C++](https://img.shields.io/badge/Language-C%2B%2B-f34b7d?style=for-the-badge)](https://isocpp.org/) [![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)  


A simple command-line application to merge multiple files into a single output file. The program processes all regular files located in the same folder as the executable, lets the user choose the merge order and direction, and produces a deterministic merged result. ✅

---

## ✨ Features


- 📂 Automatically `detects` all regular files in the executable folder

- 🔀 User-defined merge order:

- 🔤 File name

- 🕒 Last modification date

- 📏 File size

- ↕️ Ascending or descending order selection

- 📄 `Merges` file contents into a single output file

- 💻 Minimal, lightweight command-line interface

- 🌍 Cross-platform (Windows, Linux, macOS)


---


## ⚙️ Requirements

- 🖥️ C++17 compatible compiler (g++, clang, or MSVC)

- 📚 Uses only the C++17 standard library (<filesystem>, <fstream>, <algorithm>)

- No external libraries are required.


---


## 🛠️ Installation

1. Clone the repository:

```
git clone https://github.com/mirconegri/FileMerger.git
cd FileMerger
```

2. Ensure a C++17 compiler is installed on your system.

---

## 🏗️ Build Instructions

- ### Linux / macOS
```
g++ -std=c++17 FileMerger.cpp -o FileMerger
```
- ### Windows (MinGW)
```
g++ -std=c++17 FileMerger.cpp -o FileMerger.exe
```
- ### Windows (Visual Studio)
```
cl /std:c++17 FileMerger.cpp
```
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

5. The merged result will be saved as: `merged_output.txt` in the same directory. ✅

---

### 👤 Author & Connect

**Mirco Negri** — *Computer Science Student @ UniTrento*

[![Portfolio](https://img.shields.io/badge/Portfolio-00599C?style=for-the-badge&logo=globe&logoColor=white)](https://mirconegri.github.io/Portfolio/)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/mirconegri)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mirco-negri-263810225)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:mirconegri06@gmail.com)
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/mirco_negri_?igsh=MWtlbXY0a3R4NTJmNA==)
[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/share/172rhaPCUK/)

### 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
<br>
© 2026 Mirco Negri

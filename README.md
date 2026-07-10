# File Merger (PDF Edition)

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

A command-line C++ tool that merges all PDF files found in its own folder into a single output PDF, with user-defined sort order (by name or by modification date) and direction (ascending or descending), powered by Ghostscript.

> **Note:** despite the repository name, this tool is currently **PDF-specific**, not a generic file merger. It scans the executable's folder for `.pdf` files only and uses Ghostscript's `pdfwrite` device to produce a valid, properly structured merged PDF — not a raw byte concatenation.

## Table of Contents

- [Features](#features)
- [Tech Stack](#tech-stack)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Configuration and Environment](#configuration-and-environment)
- [Contributing](#contributing)
- [License](#license)

## Features

- Automatically detects every regular `.pdf` file in the same folder as the executable
- Two sort criteria, chosen interactively at runtime:
  - **Alphabetical order** by file name — numeric file names (e.g. `1.pdf`, `2.pdf`, `10.pdf`) are compared as integers rather than lexicographically, so `2.pdf` correctly sorts before `10.pdf`
  - **Last modification date**
- Ascending or descending sort direction
- Automatically skips a previously generated `merged_output.pdf` in the same folder, preventing it from being merged into itself on a second run
- Minimal, dependency-free command-line interface (aside from the required Ghostscript installation)
- Cross-platform: Windows, Linux, macOS

## Tech Stack

- **Language:** C++17
- **Standard library:** `<filesystem>`, `<fstream>`, `<algorithm>`
- **External dependency:** [Ghostscript](https://ghostscript.com/releases/gsdnld.html) — required at runtime, invoked via `std::system()` to perform the actual PDF merge (`gs` on Linux/macOS, `gswin64c` on Windows)
- No external C++ libraries are required — only the standard library

## Project Structure

```
FileMerger/
├── PdfMerger.cpp   # Main source file — file discovery, sorting, Ghostscript invocation
├── README.md
└── LICENSE
```

> **Note:** the source file is named `PdfMerger.cpp`. Earlier versions of this README referenced a `FileMerger.cpp` build target that doesn't exist in the repository — the build commands below have been corrected to reference the actual file.

## Getting Started

### Prerequisites

- A C++17-compatible compiler: `g++`, `clang`, or MSVC
- **Ghostscript** installed and available on your system `PATH` — the merge will fail at runtime without it. [Download here](https://ghostscript.com/releases/gsdnld.html)

### Installation

**1. Clone the repository**

```bash
git clone https://github.com/mirconegri/FileMerger.git
cd FileMerger
```

**2. Build**

- **Linux / macOS**

```bash
g++ -std=c++17 PdfMerger.cpp -o FileMerger
```

- **Windows (MinGW)**

```bash
g++ -std=c++17 PdfMerger.cpp -o FileMerger.exe
```

- **Windows (Visual Studio)**

```bash
cl /std:c++17 PdfMerger.cpp
```

The executable will be generated in the current directory.

## Usage

1. Place the executable in the folder containing the PDF files you want to merge
2. Run the program:

```bash
./FileMerger
```

3. Choose the merge order when prompted:

```
Choose merge order:
1 - Alphabetical order (numeric names are sorted correctly too)
2 - Last modification date
Selection:
```

4. Choose the sort direction:

```
Choose sort direction:
1 - Ascending
2 - Descending
Selection:
```

5. The merged result is saved as `merged_output.pdf` in the same directory.

## Configuration and Environment

This tool requires no environment variables or config files. Its only external requirement is having **Ghostscript accessible on the system `PATH`** — if the `gs` (or `gswin64c` on Windows) command isn't found, the merge step will fail with a non-zero exit code and the tool will print an error asking you to verify the Ghostscript installation.

## Contributing

Contributions are welcome! To propose a change:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes with a clear message
4. Open a Pull Request

Found a bug or have a feature idea (e.g. support for non-PDF formats, or a true generic-file merge mode)? Open an [Issue](https://github.com/mirconegri/FileMerger/issues).

### 👤 Author & Connect

**Mirco Negri** — *Computer Science Student @ UniTrento*

[![Portfolio](https://img.shields.io/badge/Portfolio-00599C?style=for-the-badge&logo=globe&logoColor=white)](https://mirconegri.github.io/Portfolio/)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/mirconegri)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mirco-negri-263810225)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:mirconegri06@gmail.com)
[![Instagram](https://img.shields.io/badge/Instagram-E4405F?style=for-the-badge&logo=instagram&logoColor=white)](https://www.instagram.com/mirco_negri_?igsh=MWtlbXY0a3R4NTJmNA==)
[![Facebook](https://img.shields.io/badge/Facebook-1877F2?style=for-the-badge&logo=facebook&logoColor=white)](https://www.facebook.com/share/172rhaPCUK/)

## License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.
<br>
© 2026 Mirco Negri

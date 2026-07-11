# File Merger (PDF Edition)

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)

A command-line C++ tool that merges all PDF files in its working directory into a single output file, with interactive sort order (by name or modification date) and direction (ascending or descending), powered by Ghostscript.

Built to solve a recurring personal pain point: merging scanned lecture notes and university handouts distributed as separate per-topic PDFs, while preserving correct PDF structure — not just concatenating raw bytes.

> **Note:** despite the repository name, this tool is currently PDF-specific. It scans for `.pdf` files only and delegates the actual merge to Ghostscript's `pdfwrite` device, which produces a structurally valid output rather than a naive binary join.

## Table of Contents

- [Features](#features)
- [Tech Stack](#tech-stack)
- [Design Decisions](#design-decisions)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Configuration and Environment](#configuration-and-environment)
- [Contributing](#contributing)
- [License](#license)

## Features

- Automatically detects every `.pdf` file in the same directory as the executable
- Two sort criteria selected interactively at runtime:
  - Alphabetical order by filename — numeric names (e.g. `1.pdf`, `2.pdf`, `10.pdf`) are compared as integers, so `2.pdf` correctly precedes `10.pdf`
  - Last modification date
- Ascending or descending direction for either criterion
- Automatically skips any existing `merged_output.pdf` in the same folder, preventing the output from being merged into itself on a second run
- Cross-platform: Windows, Linux, macOS

## Tech Stack

- **Language:** C++17
- **Standard library:** `<filesystem>`, `<fstream>`, `<algorithm>`
- **External dependency:** [Ghostscript](https://ghostscript.com/releases/gsdnld.html) — invoked at runtime via `std::system()` using the `pdfwrite` device (`gs` on Linux/macOS, `gswin64c` on Windows)

No external C++ libraries are required beyond the standard library.

## Design Decisions

**Why C++ instead of Python?** The core logic — directory scanning, sorting, and shelling out to Ghostscript — is trivial in either language. C++ was chosen to produce a single self-contained executable that non-technical users (e.g. other students sharing the same handout folders) can run without installing a Python interpreter or any packages.

**Why Ghostscript instead of a PDF library?** Ghostscript's `pdfwrite` device re-renders and recompresses each page, producing a structurally valid, linearized output PDF. Pure concatenation approaches (reading raw bytes and joining them) produce files that open in most viewers but fail PDF/A compliance checks and sometimes corrupt internal cross-reference tables. For merging scanned lecture notes that may need to be submitted or printed, output correctness matters.

**Why `std::system()` instead of linking Ghostscript as a library?** Ghostscript ships with a C API (`libgs`), but linking it statically complicates the build significantly and linking it dynamically ties the binary to a specific installed version. Invoking the `gs` executable via `std::system()` keeps the build a single-file compile with no linker flags, at the cost of a slightly slower startup (acceptable for a batch tool).

## Project Structure

```
FileMerger/
├── PdfMerger.cpp   # Main source — file discovery, sort, Ghostscript invocation
├── README.md
└── LICENSE
```

> The source file is named `PdfMerger.cpp`. Earlier versions of this README referenced a `FileMerger.cpp` build target that does not exist — the commands below reflect the actual filename.

## Getting Started

### Prerequisites

- A C++17-compatible compiler: `g++`, `clang++`, or MSVC
- [Ghostscript](https://ghostscript.com/releases/gsdnld.html) installed and available on `PATH`

Verify Ghostscript is accessible before building:

```bash
gs --version          # Linux / macOS
gswin64c --version    # Windows
```

### Installation

```bash
git clone https://github.com/mirconegri/FileMerger.git
cd FileMerger
```

Build:

```bash
# Linux / macOS
g++ -std=c++17 PdfMerger.cpp -o FileMerger

# Windows (MinGW)
g++ -std=c++17 PdfMerger.cpp -o FileMerger.exe

# Windows (MSVC)
cl /std:c++17 PdfMerger.cpp
```

## Usage

1. Place the executable in the folder containing the PDFs to merge
2. Run:

```bash
./FileMerger
```

3. Follow the interactive prompts:

```
Choose merge order:
1 - Alphabetical (numeric names sorted correctly)
2 - Last modification date
Selection: 1

Choose sort direction:
1 - Ascending
2 - Descending
Selection: 1

Merging 5 files...
Done. Output saved as merged_output.pdf.
```

The merged file is written as `merged_output.pdf` in the same directory. Running the tool again will skip the previous output automatically.

## Configuration and Environment

No environment variables or configuration files are required. The only external dependency is Ghostscript on `PATH`. If the `gs` or `gswin64c` command is not found, the merge step exits with a non-zero code and prints an error prompting you to verify the installation.

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/your-feature`)
3. Commit your changes with a clear message
4. Open a Pull Request

Feature ideas welcome — particularly generic (non-PDF) file merge support, or a drag-and-drop GUI wrapper. Open an [Issue](https://github.com/mirconegri/FileMerger/issues) to discuss before implementing.

### Author

**Mirco Negri** — Computer Science @ UniTrento

[![Portfolio](https://img.shields.io/badge/Portfolio-00599C?style=for-the-badge&logo=globe&logoColor=white)](https://mirconegri.github.io/Portfolio/)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github&logoColor=white)](https://github.com/mirconegri)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/mirco-negri-263810225)
[![Gmail](https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white)](mailto:mirconegri06@gmail.com)

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

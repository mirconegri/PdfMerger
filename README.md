# File Merger - C++ 🗂️

[![C++](https://img.shields.io/badge/Language-C%2B%2B-f34b7d?style=for-the-badge)](https://isocpp.org/) [![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)](LICENSE)  


A simple command-line application to merge multiple files into a single output file. The program processes all regular files located in the same folder as the executable, lets the user choose the merge order and direction, and produces a deterministic merged result. ✅











<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Simulatore Shift 8-bit</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f0f2f5;
            color: #333;
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
        }
        .container {
            background-color: white;
            padding: 30px;
            border-radius: 12px;
            box-shadow: 0 8px 16px rgba(0,0,0,0.1);
            width: 100%;
            max-width: 500px;
        }
        h2 { text-align: center; margin-top: 0; color: #1a73e8; }
        .control-group {
            margin-bottom: 15px;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        input[type="number"] {
            padding: 8px;
            border: 1px solid #ccc;
            border-radius: 4px;
            width: 80px;
        }
        .bits-row {
            display: flex;
            justify-content: center;
            gap: 8px;
            margin-bottom: 10px;
        }
        .bit {
            width: 35px;
            height: 35px;
            display: flex;
            justify-content: center;
            align-items: center;
            border: 2px solid #bdc3c7;
            border-radius: 4px;
            font-size: 1.2em;
            font-weight: bold;
            background-color: #ecf0f1;
            transition: all 0.3s ease;
        }
        .bit.new-bit {
            background-color: #f39c12; /* Arancione per evidenziare i nuovi bit */
            color: white;
            border-color: #e67e22;
        }
        .label {
            text-align: center;
            font-size: 0.9em;
            color: #7f8c8d;
            margin-bottom: 5px;
            margin-top: 20px;
        }
        .result-box {
            margin-top: 25px;
            padding: 15px;
            background-color: #e8f0fe;
            border-left: 4px solid #1a73e8;
            border-radius: 4px;
            font-size: 1.1em;
            text-align: center;
        }
        input[type="range"] { flex-grow: 1; margin: 0 15px; }
    </style>
</head>
<body>

<div class="container">
    <h2>Simulatore Shift (8-bit)</h2>

    <div class="control-group">
        <label for="numInput"><strong>Numero Decimale (-128 a 127):</strong></label>
        <input type="number" id="numInput" value="-8" min="-128" max="127">
    </div>

    <div class="control-group">
        <label><strong>Tipo di Shift:</strong></label>
        <div>
            <input type="radio" id="srai" name="shiftType" value="srai" checked>
            <label for="srai">SRAI (Aritmetico)</label>
            <br>
            <input type="radio" id="srli" name="shiftType" value="srli">
            <label for="srli">SRLI (Logico)</label>
        </div>
    </div>

    <div class="control-group">
        <label><strong>Quantità: <span id="shiftVal">2</span></strong></label>
        <input type="range" id="shiftInput" value="2" min="0" max="7">
    </div>

    <div class="label">Valore Originale Binario</div>
    <div class="bits-row" id="origBits"></div>

    <div class="label">Valore Shiftato Binario</div>
    <div class="bits-row" id="shiftedBits"></div>

    <div class="result-box" id="resultText"></div>
</div>

<script>
    function updateSimulator() {
        let num = parseInt(document.getElementById('numInput').value) || 0;
        // Limita ai valori di un byte con segno
        if (num > 127) num = 127;
        if (num < -128) num = -128;

        let shiftAmt = parseInt(document.getElementById('shiftInput').value);
        document.getElementById('shiftVal').innerText = shiftAmt;

        let isArithmetic = document.getElementById('srai').checked;

        // 1. Converti il decimale in binario a 8 bit (Complemento a Due)
        let origBin = (num < 0 ? (0xFF + num + 1) : num).toString(2).padStart(8, '0');

        // 2. Calcola lo shift manipolando la stringa
        let shiftedBin = '';
        // SRAI usa il bit di segno (il primo), SRLI usa sempre '0'
        let newBitsChar = isArithmetic ? origBin[0] : '0';

        if (shiftAmt > 0) {
            shiftedBin = newBitsChar.repeat(shiftAmt) + origBin.substring(0, 8 - shiftAmt);
        } else {
            shiftedBin = origBin;
        }

        // 3. Converti il binario shiftato di nuovo in decimale con segno
        let resultDec = parseInt(shiftedBin, 2);
        if (shiftedBin[0] === '1') {
            resultDec = resultDec - 256; // Gestione del complemento a due per il JS
        }

        // 4. Aggiorna l'interfaccia utente
        renderBitsRow('origBits', origBin, 0);
        renderBitsRow('shiftedBits', shiftedBin, shiftAmt);

        document.getElementById('resultText').innerHTML = 
            `Il risultato decimale è: <strong>${resultDec}</strong>`;
    }

    function renderBitsRow(containerId, binStr, newBitsCount) {
        const container = document.getElementById(containerId);
        container.innerHTML = ''; // Svuota il contenitore
        
        for (let i = 0; i < 8; i++) {
            let div = document.createElement('div');
            div.className = 'bit';
            // Evidenzia i bit appena entrati da sinistra
            if (containerId === 'shiftedBits' && i < newBitsCount) {
                div.classList.add('new-bit');
            }
            div.innerText = binStr[i];
            container.appendChild(div);
        }
    }

    // Aggiungi gli Event Listener per aggiornare in tempo reale
    document.getElementById('numInput').addEventListener('input', updateSimulator);
    document.getElementById('shiftInput').addEventListener('input', updateSimulator);
    document.getElementById('srai').addEventListener('change', updateSimulator);
    document.getElementById('srli').addEventListener('change', updateSimulator);

    // Esegui la prima volta all'avvio
    updateSimulator();
</script>

</body>
</html>





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

## 📜 License

MIT License © 2025 `Mirco Negri` — see [LICENSE](LICENSE) file for details.

---

## 👤 Author

`Mirco Negri` GitHub: https://github.com/mirconegri

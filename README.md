# Rwanda Infrastructure Management System

A C++ console application developed for the **Ministry of Infrastructure of Rwanda** to manage and plan road infrastructure connecting the capital city Kigali to six secondary cities across the country.



---

## Project Overview

Rwanda's administrative structure includes a capital city (Kigali) and six designated secondary cities. This application helps the Ministry of Infrastructure record cities, manage roads between them, track construction budgets, and visualize connectivity using **adjacency matrices** — a core graph data structure.

### Cities Covered

| Index | City |
|-------|------|
| 1 | Kigali *(Capital)* |
| 2 | Huye |
| 3 | Muhanga |
| 4 | Musanze |
| 5 | Nyagatare |
| 6 | Rubavu |
| 7 | Rusizi |

> New secondary cities can be added at runtime and will receive the next available index automatically.

---

## Features

| Menu Option | Feature |
|-------------|---------|
| 1 | Add new city(ies) |
| 2 | Add a road between two cities |
| 3 | Assign a budget to a road |
| 4 | Edit / rename a city |
| 5 | Search for a city by index |
| 6 | Display all recorded cities |
| 7 | Display roads as an adjacency matrix |
| 8 | Display full data (cities + both matrices) and save to files |
| 9 | Exit |

---

## Data Structures Used

- **Array** — stores city names indexed from 1
- **2D Adjacency Matrix (`roads[][]`)** — represents road connections (1 = road exists, 0 = no road)
- **2D Adjacency Matrix (`budgets[][]`)** — stores road budgets in Billion RWF

---

## Getting Started

### Prerequisites

- A C++ compiler: `g++` (GCC), MSVC, or Clang
- C++11 or later

### Compile

```bash
g++ -o rwanda_infrastructure rwanda_infrastructure.cpp -std=c++11
```

### Run

```bash
./rwanda_infrastructure        # Linux / macOS
rwanda_infrastructure.exe      # Windows
```

---

## Output Files

Running **option 8** from the menu generates two text files in the working directory:

**`cities.txt`**
```
Index   City_Name
1       Kigali
2       Huye
...
```

**`roads.txt`**
```
Nbr  Road                      Budget
1.   Kigali-Muhanga            28.60
2.   Kigali-Musanze            28.60
...
```

---

## Sample Road Network

Roads currently planned or under construction (budget in Billion RWF):

| Road | Budget (Billion RWF) |
|------|----------------------|
| Kigali – Muhanga | 28.6 |
| Kigali – Musanze | 28.6 |
| Kigali – Nyagatare | 70.84 |
| Muhanga – Huye | 56.7 |
| Musanze – Rubavu | 33.7 |
| Huye – Rusizi | 80.96 |
| Muhanga – Rusizi | 117.5 |
| Musanze – Nyagatare | 96.14 |
| Muhanga – Musanze | 66.3 |

---

## Validation & Error Handling

- A city cannot be recorded more than once
- A budget cannot be assigned to a road that does not exist
- Empty input is rejected and re-prompted
- Works correctly on both **Windows** (`\r\n`) and **Linux/macOS** (`\n`) line endings
- Invalid menu choices and out-of-range indices are handled gracefully

---

## Project Structure

```
.
├── rwanda_infrastructure.cpp   # Main source file
├── cities.txt                  # Generated on option 8
├── roads.txt                   # Generated on option 8
└── README.md
```

---



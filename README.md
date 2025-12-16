# Programming II Projects: Retro Console Auction

![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white)
![University](https://img.shields.io/badge/University-UDC-blue?style=flat-square)
![Score](https://img.shields.io/badge/Grade-High_Pass-success?style=flat-square)

## 📖 Overview
This repository contains the complete coursework for **Programming II** at **Universidade da Coruña (FIC)**.

The core project is a **Retro Video Game Console Auction Platform**, built progressively using **C**. The main focus was mastering **Abstract Data Types (ADTs)**, modular programming, and manual memory management (pointers vs. arrays).

## 🏆 Performance Record
The coursework was divided into three iterative practices, evolving from basic modularity to complex data structure orchestration.

| Module | Focus Area | Score | Status |
| :--- | :--- | :--- | :--- |
| **P0** | Rational Numbers ADT | **Pass** (0/0) | ✅ Completed |
| **P1** | Console Manager (Lists) | **1.75 / 2.00** | ✅ Distinction |
| **P2** | Auction System (Stacks) | **1.53 / 2.00** | ✅ Passed |
| **Total** | **Final Grade** | **3.28 / 4.00** | **82%** |

## 🛠️ Technical Highlights

### 🟢 P0: Rational Numbers (Introduction)
* **Goal:** Introduction to header files (`.h`) and modular compilation.
* **Implementation:** Developed a `Rational` number ADT with two interchangeable implementations:
    1.  **Struct-based:** Direct value manipulation.
    2.  **Pointer-based:** Heap allocation and reference management.

### 🔵 P1: Console Management System
* **Goal:** Implementation of a **List ADT** to manage a database of retro consoles (Nintendo, Sega).
* **Key Challenge:** Polymorphic behavior. The `main.c` program works seamlessly with two different underlying implementations of the list, swapped at compile time:
    * **Static List:** Array-based implementation (Fixed size).
    * **Dynamic List:** Singly Linked List using pointers (Unlimited size).
* **Operations:** `[N]ew` console, `[D]elete` console, `[B]id` (simple counter), and `[S]tats` generation.

### 🟣 P2: Advanced Auction Platform
* **Goal:** Extending the system with nested ADTs and complex logic.
* **Data Structures:**
    * **Ordered List ADT:** Dynamic linked list, auto-sorted by `ConsoleID`.
    * **Stack ADT (BidStack):** Static array-based stack to track bid history.
* **Architecture:** Implemented a **List of Stacks**. Each node in the console list contains a dedicated stack of bids.
* **Complex Algorithms:**
    * `[A]ward`: Determining the winner from the stack top and cleaning memory.
    * `[I]nvalidateBids`: Statistical filtering to remove bids from hyped consoles (> 2x average).
    * `[R]emove`: Garbage collection of consoles with no activity.

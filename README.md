# SIT — System Information Toolkit

**SIT** is a lightweight, cross-platform **System Information Toolkit** written in C++.
It provides essential system details and real-time usage metrics with a clean and minimal design.

The goal of SIT is to offer **clear visibility into system state** without unnecessary complexity,
making it useful for learning, diagnostics, and future system monitoring extensions.

---

## ✨ Features

### 🖥️ System Information
- Operating System name
- CPU model
- Total RAM size
- Total disk capacity
- System uptime
- Current user information

### 📊 System Usage
- CPU usage percentage
- RAM usage percentage

All usage values are calculated using **native OS APIs**, not estimates.

---

## 🧩 Planned Features

The following features are planned and currently under development:

- [ ] System Health Score indicator  
- [ ] Improved quality and accuracy of usage metrics  
- [ ] Enhanced CLI output and formatting  
- [ ] System problems scanner (errors / weaknesses indicators)  
- [ ] File integrity checker  

These additions are designed to keep SIT **lightweight, transparent, and safe**.

---

## 🛠️ Supported Platforms

- **Windows** (via WinAPI)
- **Linux** (via `/proc` and standard system files)

The codebase uses conditional compilation to keep platform-specific logic isolated.

---

## 🧠 Design Philosophy

- Minimal dependencies
- Native OS APIs only
- Clear and readable C++ code
- No background services or invasive system access
- Easy to extend without refactoring the core

SIT is intentionally built as a **toolkit**, not a full monitoring daemon.

---

## 📦 Build Instructions

### Requirements
- C++17 compatible compiler
- Windows: MinGW / MSVC  
- Linux: GCC or Clang  

### Build (example)
```bash
g++ systemInfo.cpp -o sit

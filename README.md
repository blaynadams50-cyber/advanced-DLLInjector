<div align="center">
  <img src="https://github.com/thesayreh/advanced-DLLInjector/blob/main/src/src.png" alt="DLL Injector" width="300">

  <h1>Advanced DLL Injector</h1>
  <p>Universal interactive DLL injector for Windows (x86/x64), written in modern C++</p>

  <a href="https://github.com/thesayreh/advanced-DLLInjector/releases/tag/v1.0.0">
    <img src="https://img.shields.io/badge/Download-v1.0.0-D5006D?style=for-the-badge&logo=github" alt="Downloads">
  </a>
  <img src="https://img.shields.io/badge/platform-Windows-blue?style=for-the-badge&color=D5006D" alt="Platform">
  <a href="https://github.com/thesayreh/advanced-DLLInjector/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/thesayreh/advanced-DLLInjector?style=for-the-badge&color=D5006D" alt="License">
  </a>
</div>

---

### 📌 Navigation  
<a href="#features"><strong>Features</strong></a> •
<a href="#installation"><strong>Installation</strong></a> •
<a href="#usage"><strong>Usage</strong></a> •
<a href="#technical-overview"><strong>Technical Overview</strong></a> •
<a href="#changelog"><strong>Changelog</strong></a> •
<a href="#troubleshooting"><strong>Troubleshooting</strong></a> •
<a href="#contributing"><strong>Contributing</strong></a>

---

## 🎯 Features

- ✅ Manual PID search by process name (case-insensitive)
- 🔧 Dynamic path input for any DLL
- 💡 Unicode support (`LoadLibraryW`)
- 📦 Clean and portable C++ codebase (MSVC-ready)
- 📜 MIT License — free to use and modify
- 🧠 Good for learning injection & WinAPI basics

---

## 🧪 Installation

1. Clone the repository or [download latest release](https://github.com/thesayreh/advanced-DLLInjector/releases/tag/v1.0.0)
2. Open project in Visual Studio (or other C++ IDE)
3. Build as:
   - `x64` if target process is 64-bit
   - `x86` if target process is 32-bit
4. Make sure your DLL is compiled in the correct architecture to match the target

---

## 🚀 Usage

```bash
> Injector.exe
```

🧾 The injector will prompt you to:

1. Enter **target process name** (e.g. `notepad.exe`)
2. Enter full **DLL path** (absolute, e.g. `C:\MyStuff\hook.dll`)
3. If process and path are valid — injection will occur via `CreateRemoteThread`.

Upon success:  
✅ “DLL Injected successfully!”

---

## ⚙️ Technical Overview

This injector uses the classic and well-documented **LoadLibrary injection technique**, implemented through:

- `CreateToolhelp32Snapshot()` → to iterate through system processes
- `VirtualAllocEx()` → to allocate memory in target process
- `WriteProcessMemory()` → to copy DLL path to remote memory
- `CreateRemoteThread()` → to launch `LoadLibraryW` in target process context

**Architecture-aware:**  
- The injector must match the bitness (x86/x64) of the target process.  
- Will fail silently or crash otherwise.

### ✏️ Unicode vs ANSI
- Uses `LoadLibraryW` for full compatibility with Unicode paths.
- If needed, you can easily switch to `LoadLibraryA`.

---

## 📝 Changelog

> **v1.0.0** — *Initial stable release*

- Added dynamic process lookup by name
- Switched to Unicode-based injection (`LoadLibraryW`)
- Improved input prompts and user experience
- Clean exit and error handling
- Modular and readable source

---

## 🛠 Troubleshooting

- ❌ **"Injection failed" or no output?**
  - Ensure your DLL **exists** and is **compiled for correct architecture**
  - Run injector as **Administrator**
  - Check antivirus or Windows Defender blocking `CreateRemoteThread`

- ❌ **Target process not found?**
  - Use full name including extension (e.g. `chrome.exe`)
  - Process might be running with elevated privileges — run injector as admin

---

## 🤝 Contributing

Contributions, suggestions and forks are welcome.  
If you have an idea to extend this injector (e.g., auto-elevate, manual map, reflective loader, etc.) — open a pull request or issue.

---

## ⚠️ Disclaimer

> This tool is provided **for educational purposes only**.  
> By using this code, **you take full responsibility** for how it is used.  
> The developer is **not responsible** for any misuse, legal consequences or damages.

---

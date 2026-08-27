# 🐚 Minishell

A lightweight, fully functional UNIX shell implementation written in C. This shell parses user input, handles built-in environment and alias management commands, and executes external system binaries cleanly via system process forking (`fork` & `execvp`).

---

## 🚀 Features

- **Process Execution:** Executes external programs located in `PATH` (e.g., `ls`, `grep`, `cat`, `clear`).
- **Alias Engine:** Full support for alias creation (`alias name=value`), listing, deletion (`unalias`), and automatic **Alias Expansion** before execution.
- **Environment Management:** Set and remove environment variables dynamically using `export` and `unset`.
- **Directory Navigation:** Integrated `cd` support with path resolution.
- **Robust Error Handling:** Protected against blank line input (`Enter`), empty tokens, and invalid alias parameters without segmentation faults.

---

## 📑 Built-in Commands & Usage Guide

Below is a detailed breakdown of all built-in commands supported by Minishell.

### 1. `pwd` — Print Working Directory
Displays the current absolute path of your active working directory.

* **Usage:**
  ```bash
  minishell::> pwd
  /home/user/projects/minishell
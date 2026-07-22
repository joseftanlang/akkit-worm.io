# 2. Getting Started: Setting Up Your Workshop

Before a carpenter can build a table, they need to set up their workshop. Similarly, before you can program your AK Kit, you need to set up your computer with the right software tools. 

Because embedded programming requires specific tools, **Linux (specifically Ubuntu) is highly recommended** for this journey. 

---

## 1. Setting Up Your OS (Linux)
If you already use Ubuntu, you are ready to go!
If you use Windows, you have a few options to get a Linux environment:
- **WSL (Windows Subsystem for Linux):** This lets you run Ubuntu directly inside Windows. (Recommended for Windows 10/11 users).
- **Virtual Machine:** Use software like VirtualBox to run Ubuntu in a window.
- **Dual Boot:** Install Ubuntu alongside Windows.

*If you are completely new to Linux, don't panic! You will only need to type a few specific commands, and we will guide you through all of them.*

---

## 2. Installing the Essential Tools
Open your terminal (the black text window in Linux). You are going to tell your computer to download the basic building blocks for programming. Type the following and press Enter:

```bash
sudo apt-get update
sudo apt-get install build-essential git minicom
```
*Note: It may ask for your password. When you type your password, nothing will show on the screen—this is normal! Just type it and press Enter.*

---

## 3. The Compiler (GNU ARM Embedded Toolchain)
Your computer speaks English, but the STM32 microcontroller on your board only speaks "Machine Code" (1s and 0s). We need a translator. 

The **GNU ARM Embedded Toolchain** is that translator. It takes the C/C++ code you write and turns it into a language the board understands.

1. Download the toolchain: [Download Link (Check AK-Flash Repo)](https://github.com/epcbtech/ak-flash)
2. Extract the downloaded file into a clean folder (e.g., `~/Projects/Embedded/`). Do not leave it in your Downloads folder!

---

## 4. The Flasher (AK-Flash)
Once your code is translated, you need a way to physically push it through the USB cable and into the memory of the microcontroller. This process is called "Flashing".

We use a tool called **AK-Flash** to do this.
1. Download AK-Flash: [AK-Flash GitHub](https://github.com/epcbtech/ak-flash)
2. Follow the instructions on their GitHub page to install it on your system.

---

## 5. Configuring and Building Your Code (The Makefile)
Before you can build the code, you need to configure the project. We do this using a `Makefile`.

### How a Makefile Works
Think of a `Makefile` as a recipe book for your code. When you type `make` in the terminal, the computer reads this file to figure out exactly what to do. 
The `Makefile` tells the computer:
1. **Where the Compiler is:** It points to the GNU ARM Toolchain you downloaded in Step 3 so the computer knows *how* to translate the code.
2. **Where the Source Files are:** It lists all the `.cpp` and `.c` files in your project so it knows *what* to translate.
3. **Where to include Headers:** It lists all the folders containing `.h` files so the compiler can find your definitions.
4. **Linking:** It links all the translated files together into a single `.bin` or `.hex` file that can be flashed to the board.

There are **two** `Makefile`s in this project that you need to be aware of:
1. **`application/Makefile`**: The recipe to build your actual game/app code.
2. **`boot/Makefile`**: The recipe to build the bootloader (you usually only need to build this once).

### Updating the Toolchain Path
You must open both of these Makefiles in a text editor and update the toolchain path to match your local computer. Look for a line near the top of the file that points to the compiler (often named `GCC_PATH` or `TOOLCHAIN_DIR`):

```makefile
# Example line you might see:
GCC_PATH = /home/user/Downloads/gcc-arm-none-eabi/bin
```
Change that path to the exact folder where you extracted the toolchain in Step 3!

### Compiling the Application
Let's see if everything works by compiling the application!

1. Open your terminal and navigate to the application folder:
   ```bash
   cd path/to/ak-base-kit-stm32l151/application
   ```
2. Type `make` and press Enter.
   ```bash
   make
   ```
   *The `make` command looks at the `Makefile` you just edited and automatically runs the translator to build your code.*

If the text scrolling on your screen ends without any "Error" messages, congratulations! You have successfully built your first firmware.

---

## 6. Flashing the Firmware to the Board
Now, let's put that code onto the physical board.

1. Plug your AK Kit into your computer using a USB cable.
2. In your terminal, type:
   ```bash
   make flash
   ```
   *(If it fails to find the board, you might need to specify the USB port by typing `make flash dev=/dev/ttyUSB0`)*

If successful, the board will restart and begin running your code!

> **Your Next Step:** Now that you can build and flash code, let's look at what that code actually looks like. Head over to **[3. Firmware Development](3_FIRMWARE_DEVELOPMENT.md)**.

---
<br>

[< Back to 1. Introduction](1_INTRODUCTION.md) | [Next: 3. Firmware Development >](3_FIRMWARE_DEVELOPMENT.md)

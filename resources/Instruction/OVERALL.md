# Getting Started with the AK Kit Development Board (STM32L151)

## Table of Contents

- [About the AK Embedded Base Kit](#about-the-ak-embedded-base-kit)
- [Prerequisites for Beginners](#prerequisites-for-beginners)
- [Setup and Installation](#setup-and-installation)
- [Building the Firmware](#building-the-firmware)
- [Flashing Firmware to the AK Kit Board](#flashing-firmware-to-the-ak-kit-board)
- [Checking the Board Internals](#checking-the-board-internals)
- [Additional Resources](#additional-resources)

---

## About the AK Embedded Base Kit

The **AK Embedded Base Kit** development environment is designed to run on a Linux-based operating system, especially **Ubuntu**. 

For users who are new to Linux, the transition may require some time. Becoming familiar with the Linux command line, file management, and development tools will greatly benefit your future embedded system development work. Linux knowledge is an essential skill for embedded engineers, as many professional workflows rely heavily on Linux-based tools.

If you are unfamiliar with Ubuntu, please refer to online installation guides and spend some time practicing basic Linux commands before starting this tutorial.

---

## Prerequisites for Beginners

If this is your very first time touching embedded systems, don't worry! Here is what you will need to get started:

- **Basic C/C++ Programming:** Embedded systems are heavily reliant on C and C++. You don't need to be an expert, but understanding basic variables, loops (`for`/`while`), conditional statements (`if`/`else`), and functions will be incredibly helpful.
- **A Computer Running Linux:** As mentioned above, this kit is optimized for Linux (Ubuntu is highly recommended). If you are on Windows, you can install Ubuntu via WSL (Windows Subsystem for Linux), use a Virtual Machine (like VirtualBox), or dual-boot your PC.
- **Willingness to Learn the Terminal:** You'll be typing commands into a text window (the terminal) to build and flash your code instead of clicking buttons. We provide all the commands you need in this guide, so you can learn as you go!
- **Patience and Curiosity:** Embedded programming involves interacting closely with physical hardware. Sometimes a small typo or a loose cable can cause issues. Take your time, double-check your steps, and enjoy the process of making hardware come alive!

---

## Setup and Installation

### 1. Install Required Linux Packages

If you are using Ubuntu or another Debian-based Linux distribution, open a terminal and install the required development packages:

```bash
sudo apt-get update
sudo apt-get install build-essential git minicom
```

### 2. Download the GNU ARM Embedded Toolchain

> **Note:** The GNU Toolchain version at the time of writing this article is Version 10.3-2021.10.

- [Download GNU ARM Embedded Toolchain](https://github.com/epcbtech/ak-flash) *(Please check the repository description for exact toolchain links if not hosted there)*

![GNU ARM Embedded Toolchain](https://file.hstatic.net/1000362368/file/download-gnu-arm-embedded-toolchain_e4148ff86f954109b84adb0b3836a7da_grande.jpg)

### 3. Download AK-Flash

AK-Flash is a tool for flashing application firmware onto the kits. Instructions for installation and use are available in the repository description.

- [Download AK-Flash](https://github.com/epcbtech/ak-flash)

> **Important:** For items 2 and 3, after downloading the tools, please extract them and move them to a dedicated project folder for easy management. Do not leave them in your `Downloads` folder.

### 4. Optional: Download STM32CubeProgrammer

This step is optional. If you want to upload code and debug using an ST-LINK/V2, please download the STM32CubeProgrammer software.

- [Download STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html)
- [Download ST-LINK/V2 Drivers](https://www.st.com/en/development-tools/st-link-v2.html)

![STM32CubeProgrammer](https://file.hstatic.net/1000362368/file/link-tai-pham-mem-stm32cubeprogrammer-software-for-all-stm32_0a13a1926bfb491fafd0e87305e6f15d_grande.jpg)

### 5. Download the AK Embedded Base Kit Source Code

Clone or download the source code for the base kit:
- [AK Embedded Base Kit GitHub Repository](https://github.com/ak-embedded-software/ak-base-kit-stm32l151)

---

## Building the Firmware

### 1. Adjust the Build Path

Navigate to the `Makefile` located in the application directory: `ak-base-kit-stm32l151/application/Makefile`.

> **Note:** Remember to open the `Makefile` in a text editor and adjust the toolchain build path to match the directory where you extracted the GNU ARM Embedded Toolchain in Step 2.

![Adjusting Compiler Path](https://file.hstatic.net/1000362368/file/chinh-sua-duong-dan-cua-compiler-ak-embedded-base-kit_515405a60c004e1990c23a4041cfcfe3_grande.jpg)

### 2. Compile the Source Code

Open your terminal and navigate to the application folder of the project:

```bash
cd ak-base-kit-stm32l151/application
```
![Navigate to Folder](https://file.hstatic.net/1000362368/file/vao-thu-muc-ak-base-kit-stm32l151-application_0bbc30aeeb114d328474b6e2eb7141cc_grande.png)

Run the `make` command to compile the code:

```bash
make
```
![Compile Output](https://file.hstatic.net/1000362368/file/bien-dich-source-code-ak-embedded-base-kit-stm32l151_0ebb0b3a19cc42a197ebfa3a09c77aad_grande.png)

If the output resembles the image above, the compilation was successful.

---

## Flashing Firmware to the AK Kit Board

To flash the compiled firmware onto the board and test your application, run the following command while in the `ak-base-kit-stm32l151/application` directory:

```bash
make flash
```

Once you have successfully flashed the firmware, your board setup will look similar to this:

![Board Connected](https://file.hstatic.net/1000362368/file/ket-noi-kit-voi-pc_5d2ca4811655497a9d5133c968de3c26_grande.jpg)

---

## Checking the Board Internals

### 1. Connect the Board

Make sure you connect a Type-C USB cable (preferably a short, data-capable one) from the board to your PC.

### 2. Identify the COM Port and Flash

To explicitly specify the COM port while flashing, use the following command in the `application` folder:

```bash
make flash dev=/dev/ttyUSB0
```

> **Tip:** `/dev/ttyUSB0` is the typical COM port name on Linux. To verify the exact port name on Ubuntu, list the USB devices:

```bash
ls -la /dev/ttyUSB*
```

![Flashing Firmware](https://file.hstatic.net/1000362368/file/nap-application-firmware-vua-build-thanh-cong-len-kit_2a74f9d70a474fca87de0d0d77d0df82_grande.png)

**Memory Map Note:** When flashing the AK Flash application firmware, it is placed at address `0x08003000`. The system's memory map details are illustrated below:

![Memory Map](https://file.hstatic.net/1000362368/file/memory-map_26420b98174749ae8a595ef5a40afe50_large.jpg)

### 3. Demo Firmware

You can view the demo firmware running on the kit after flashing in this video:
- [Demo Firmware Video](https://youtu.be/oozc3VesdUk?si=MZHu4Lh9UEorVIrt)

---

## Additional Resources

You can find other interesting topics about Microcontroller Embedded Programming at **AK Embedded Software**.

Please send your questions or feedback to:

- **Author:** [Ngo Thanh Nha (LinkedIn)](https://www.linkedin.com/in/ngo-thanh-nha-10627b322/)
- **Facebook Group:** [Lập trình vi điều khiển nâng cao](https://www.facebook.com/groups/laptrinhvidieukhiennangcao)
- **Email:** akembeddedsoftware@gmail.com

[< Back to 1. Introduction>](1_INTRODUCTION.md) 
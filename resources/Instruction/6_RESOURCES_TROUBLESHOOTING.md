# 6. Resources & Troubleshooting

Sometimes things don't go as planned. In embedded systems, a missing semicolon or a loose cable can cause a lot of frustration. Don't worry—this happens to everyone!

---

## 1. How to Debug
When your code isn't working, don't just stare at it. Use these debugging techniques:

- **Printf Debugging:** The AK Kit has a built-in console (via UART). You can use `APP_PRINT("Score is %d\n", score);` in your code. Connect your board to the computer, run `make com`, and you will see your print statements appear in the terminal in real-time!
- **LED Debugging:** Turn an LED on when a specific line of code runs. If the LED doesn't turn on, you know the code never reached that line.
- **Hardware Debugging (GDB/ST-Link):** If you have an ST-Link connected, you can run `make debug`. This allows you to pause the microcontroller in real-time, inspect variables, and step through your C++ code line-by-line!

---

## 2. Troubleshooting Guide

### Build Errors (When `make` fails)
- **Missing Semicolon:** Check the code you just wrote. Did you forget a `;` at the end of a line? 
- **Undeclared Function:** If it says a function is not declared, you might be in a file that doesn't include the proper headers. Always check your `#include` statements at the top!
- **Wrong Path:** Make sure you are inside the `application` folder when you type `make`. 

### Flashing Errors (When `make flash` fails)
- **Is it plugged in?** Make sure you are using a data-capable USB cable, not just a charging cable.
- **Wrong COM Port:** On Linux, the board usually shows up as `/dev/ttyUSB0`. If it fails, type `ls -la /dev/ttyUSB*` to see available ports, then use `make flash dev=/dev/ttyUSB1`.
- **Permissions Issue:** If Linux blocks access to the USB port, you may need to run `sudo make flash`.

---

## 3. Frequently Asked Questions (FAQ)

**Q: I created a new `.cpp` file but `make` says it can't find my functions!**
A: Did you add your new file to the `Makefile.mk` in that folder? The compiler only builds files listed in the Makefiles! (See Tutorial 8 in the previous section).

**Q: If I unplug the board, does my code disappear?**
A: No! The code is flashed into non-volatile Flash memory. When you plug it back in, it will immediately start running your code again.

**Q: Can I break the board by writing bad code?**
A: It is extremely difficult to physically break the board just by writing code. The worst that usually happens is the board freezes, and you just need to flash it again with corrected code.

**Q: Where can I find out what other drivers exist?**
A: Look inside the `drivers` folder in your project directory. Opening the `.h` (header) files will show you all the available functions you can call, like `buzzer_on()` or `lcd_clear()`.

---

## 4. The Embedded Mindset: How to Learn
Embedded programming is a mix of software and hardware. Here is how you should approach learning it:
1. **Don't memorize everything:** You don't need to memorize how a memory map works. You just need to know *where* to look when you need it (usually the microcontroller's Datasheet).
2. **Break problems down:** If the screen isn't working, is it the code? Is it the cable? Is the board powered? Test one thing at a time.
3. **Read existing code:** The best way to learn the AK Framework is to read `scr_worm.cpp` or `scr_menu.cpp` and see how the authors wrote it!

---

## 5. Where to go next? (Recommended Resources)

If you are eager to learn more advanced microcontroller programming (like bare-metal C, registers, and RTOS), check out these incredible resources:

### YouTube Channels:
- **FastBit Embedded Brain Academy:** Excellent deep dives into ARM Cortex-M microcontrollers and writing your own drivers from scratch.
- **Phil's Lab:** Great tutorials on mixed-signal hardware design and STM32 firmware development.
- **Digi-Key Electronics:** Look for their "Intro to RTOS" and embedded systems series.

### Author Contact & Community:
- **GitHub:** [joseftanlang](https://github.com/joseftanlang)
- **Email:** tanjosef33@gmail.com
- **LinkedIn:** [Josef Tan](https://www.linkedin.com/in/josef-tan/)

**Happy Coding!**

---
<br>

[< Back to 5. Examples & Tutorials](5_EXAMPLES_TUTORIALS.md) | [Return to Table of Contents>](OVERALL.md)

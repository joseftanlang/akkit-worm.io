# 3. Firmware Development: Understanding the Code

Now that you've successfully flashed the board, it's time to understand exactly *what* you flashed. The code that runs on an embedded system is called **Firmware**. It is "firm" because it usually stays the same until you explicitly replace (flash) it with new code.

---

## The Project Structure
When you look at the files in the `ak-base-kit` folder, it might look overwhelming. Here is a simplified map of what matters:

- **`application/sources/app/`**: This is your playground! This is where the game logic and screen drawings live (e.g., `app.cpp`, `scr_worm.cpp`).
- **`application/sources/driver/`**: Think of this as a library of instruction manuals. It contains pre-written code that tells the microcontroller exactly how to talk to specific hardware (like the LCD or the Buzzer).
- **`application/Makefile`**: The recipe book that tells your computer how to compile everything together.

---

## The Firmware Flow (Event-Driven Tasks)
A normal computer program (like a video game on your PC) opens, you play it, and then you click the 'X' to close it, and the program stops. A microwave, however, never "closes"; it is always waiting for you to press a button.

In this specific AK kit framework, we don't use a simple "infinite loop" that checks everything endlessly. Instead, we use a **Task-based Operating System (AK OS)**.
Think of it like an office where workers (Tasks) sit at their desks waiting for a memo (Message). When a button is pressed, the system sends a memo saying "UP Button Pressed!" to the display task, and the display task acts on it.

### The Startup Journey:
1. **Startup Code:** When power turns on, a small assembly file (`startup_stm32l1xx.s`) organizes memory and wakes up the chip.
2. **`main_app()` in `app.cpp`:** The system jumps to the `main_app()` function. This function initializes the hardware (LCD, Buttons, Buzzer) and sets up all the tasks.
3. **`task_run()`:** At the very end of `app.cpp`, the code calls `task_run()`. This tells the AK OS to take over. From this point on, the system just waits for messages (like timers ticking or buttons being pressed) and routes them to the correct task!

---

## Memory Map
*(You don't need to memorize this, but it's good to know!)*

Your microcontroller has two main types of memory:
1. **Flash Memory:** Like your computer's hard drive. It keeps data even when the power is off. This is where your actual code (the firmware) is stored. (Address `0x08003000`).
2. **RAM:** Like your computer's short-term memory. It loses data when power is off. This is where variables (like a high score counter) are temporarily stored while the board is running.

Here is exactly how the memory is mapped on your AK Kit:

![Memory Map](https://file.hstatic.net/1000362368/file/memory-map_26420b98174749ae8a595ef5a40afe50_large.jpg)

> **Want to go deeper?** If you want an intensive deep-dive into how this memory map is actually configured in the code (using Linker Scripts), check out the **[3A. Memory Map Deep Dive](3a_MEMORY_MAP_DEEP_DIVE.md)** detour!

> **Your Next Step:** Now you understand how the code waits for messages, but how does the code actually control a physical light? Let's dive into **[4. Hardware & Peripherals](4_HARDWARE_PERIPHERALS.md)**!

---
<br>

[< Back to 2. Getting Started](2_GETTING_STARTED.md) | [Next: 3A. Memory Map Deep Dive >](3a_MEMORY_MAP_DEEP_DIVE.md)

# 3A. Advanced Detour: The Memory Map Deep Dive

In embedded systems, you don't have an operating system like Windows to manage memory for you. You must configure exactly where every instruction and variable resides in physical memory.

In this project, this memory architecture is defined by the **Linker Script** (`ak.ld`).

---

## 1. The Physical Memory of the STM32L151
The STM32L151CBT6 microcontroller on your AK kit has two primary memory regions defined by hardware:
- **Flash Memory (128 KB):** Read-only during execution. This stores your actual compiled instructions and constant data. It retains data without power. It begins at hardware address `0x08000000`.
- **SRAM (16 KB):** Read/Write memory. This stores your variables, stack, and heap. It is erased when power is lost. It begins at hardware address `0x20000000`.

---

## 2. Flash Slicing: Bootloader vs. Application
Because this project supports Over-The-Air (OTA) updates, the flash is divided into three critical sectors. We have two separate linker scripts to manage this.

### Sector 1: The Bootloader (8 KB)
- **Origin:** `0x08000000` | **Length:** `8K`
- **Linker File:** `boot/sources/platform/stm32l/ak.ld`
- **How it works:** When the CPU powers on, it reads the very first address (`0x08000000`) to find the **Stack Pointer (SP)** and the second address (`0x08000004`) to find the **Program Counter (PC)**. It begins executing the bootloader. The bootloader checks for updates, and if none exist, it prepares to jump to the Application.

### Sector 2: Boot Share Flash / BSF (4 KB)
- **Origin:** `0x08002000` | **Length:** `4K`
- **How it works:** A shared memory sandbox. Both the Bootloader and Application linker scripts explicitly define this area. The application can write a specific code here, reboot, and the bootloader will read it to know it needs to enter "Update Mode".

### Sector 3: The Application (116 KB)
- **Origin:** `0x08003000` | **Length:** `116K`
- **Linker File:** `application/sources/platform/stm32l/ak.ld`
- **How it works:** The `make flash` command places your compiled code here. The bootloader performs a function pointer jump to `0x08003000`. 
- **The Vector Table (`.isr_vector`):** The very first thing at `0x08003000` is the application's Interrupt Vector Table. The bootloader relocates the CPU's vector table by writing `0x08003000` to the System Control Block register (`SCB->VTOR`). This ensures hardware interrupts (like a timer tick) trigger the *application's* handlers, not the bootloader's handlers!

---

## 3. SRAM Organization (16 KB)
The application linker script (`application/sources/platform/stm32l/ak.ld`) strictly organizes the 16KB of SRAM starting at `0x20000000` into several sections:

1. **`.data`**: Global/Static variables initialized with a value (e.g., `int level = 1;`). Because RAM loses data when powered off, the starting value (`1`) is actually stored in Flash. The `startup.s` code physically copies this data from Flash into the `.data` RAM section before `main()` is called.
2. **`.bss`**: Global/Static variables initialized to zero (e.g., `int score;`). The startup code loops through this memory area and writes `0x00` to every address.
3. **`.heap`**: Used for dynamic memory allocation (`malloc`/`new`). In embedded systems, using the heap is often discouraged due to fragmentation, which is why `HEAP_SIZE = 2K` is kept very small.
4. **`.sstack` (Stack)**: Located at the very end of SRAM (`_estack = ORIGIN(SRAM) + LENGTH(SRAM)`). The stack grows downwards. It holds local variables inside functions. If your stack grows too large, it will crash into your heap/bss, causing a catastrophic "Stack Overflow"!
5. **`.non_clear_ram`**: A clever trick! Normally, a software reboot wipes the `.bss` and `.data` sections. By placing variables in this custom `.non_clear_ram` section, the startup code skips zeroing it out. It is used to persist data (like crash logs) across a soft reboot.

---

## 4. Modifying the Memory Map
If you port this code to a larger STM32 chip (e.g., 256KB Flash / 32KB RAM), you must modify `application/sources/platform/stm32l/ak.ld`:

```ld
MEMORY {
	BSF (rx)	: ORIGIN = 0x08002000, LENGTH = 4K
	FLASH (rx)	: ORIGIN = 0x08003000, LENGTH = 244K  /* Increased from 116K */
	SRAM (rwx)	: ORIGIN = 0x20000000, LENGTH = 32K   /* Increased from 16K */
}
```

By understanding these linker scripts, you now have complete control over where every byte of your firmware goes!

---
<br>

[< Back to 3. Firmware Development](3_FIRMWARE_DEVELOPMENT.md) | [Next: 4. Hardware & Peripherals >](4_HARDWARE_PERIPHERALS.md)

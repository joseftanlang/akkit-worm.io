# 5. Examples & Tutorials: From Zero to Hero

Welcome to the ultimate guide for the AK OS Framework! In the previous sections, we looked at how existing code works. Now, you are going to learn how to create your own features from absolute scratch. 

We will go through **10 essential steps**, taking you from creating a task to writing your own custom driver, playing sound, reading a button, and drawing to a custom LCD screen!

---

## Tutorial 1: Registering a New Task ID
In the AK OS, every "worker" (Task) needs an ID badge so the system can deliver messages to it. 

**Goal:** Create an ID for a new task.
1. Open `application/sources/app/task_list.h`.
2. Look for the `enum` that lists all the tasks (it usually starts with `AC_TASK_TIMER_ID`).
3. Add your new task ID to the list:
```cpp
    // ... existing tasks ...
    AC_TASK_ZIGBEE_ID,
    AC_TASK_MY_NEW_TASK_ID, // <-- You added this!
    /* MAX TASK ID */
    AK_TASK_LIST_LEN,
```

---

## Tutorial 2: Defining Task Signals (Messages)
Now that your task exists, what messages can it receive? We call these "Signals".

**Goal:** Create a signal your task can understand.
1. Still inside `task_list.h`, scroll down to the signal enums.
2. Create a new enum for your task's signals:
```cpp
/* MY NEW TASK SIGNALS */
enum {
    AC_MY_TASK_INIT = 0,
    AC_MY_TASK_BLINK_LED,
    AC_MY_TASK_STOP,
};
```

---

## Tutorial 3: Creating the Task Files
You have an ID and signals, but no actual code to do the work. Let's create the files!

**Goal:** Create the `.cpp` and `.h` files for your task.
1. In `application/sources/app/`, create a new file called `task_my_new_task.cpp`.
2. Add the basic task structure:
```cpp
#include "task_my_new_task.h"
#include "task_list.h"
#include "ak.h"

// This is the function the OS will call when a message arrives!
void task_my_new_task(ak_msg_t *msg) {
    // We will add code here in Tutorial 6!
}
```
3. Create `task_my_new_task.h` and declare your function: `extern void task_my_new_task(ak_msg_t *msg);`

---

## Tutorial 4: Registering the Task in the OS
You wrote the code, but the Operating System doesn't know about it yet. We need to add it to the active task table.

**Goal:** Add your task to the OS table.
1. Open `application/sources/app/task_list.cpp`.
2. Include your new header at the top: `#include "task_my_new_task.h"`
3. Scroll down to `ak_task_t app_task_table[]`.
4. Link your Task ID to your function:
```cpp
    // ... existing tasks ...
    { AC_TASK_MY_NEW_TASK_ID, TASK_PRI_LEVEL_4, task_my_new_task, &task_my_new_task_mailbox, "my_new_task" },
```
*(Make sure to define the mailbox array for it just above the table, similar to how other tasks do it!)*

---

## Tutorial 5: Sending (Posting) Messages
How do you wake your task up? By posting a message to it!

**Goal:** Send a message to your new task when a button is pressed.
1. Open `scr_idle.cpp` (or `scr_worm.cpp`).
2. Inside the button handler (e.g., when the UP button is pressed), send a message:
```cpp
if (msg->sig == 12) { /* UP Pressed */
    // Send a message to our new task!
    task_post_pure_msg(AC_TASK_MY_NEW_TASK_ID, AC_MY_TASK_BLINK_LED);
}
```

---

## Tutorial 6: Handling Messages
Your task received the `AC_MY_TASK_BLINK_LED` message! Now it needs to react.

**Goal:** Write a switch statement to handle incoming signals.
1. Go back to your `task_my_new_task.cpp` file.
2. Write the switch logic:
```cpp
void task_my_new_task(ak_msg_t *msg) {
    switch (msg->sig) {
        case AC_MY_TASK_BLINK_LED:
            BUZZER_PlaySound(BUZZER_SOUND_TICK); // Play sound!
            break;
            
        case AC_MY_TASK_STOP:
            // Stop doing things
            break;
    }
}
```

---

## Tutorial 7: Using Timers
Sometimes you want a task to trigger *itself* every second, rather than waiting for a button. 

**Goal:** Make the task send a message to itself every 500ms.
```cpp
// Inside your switch statement in task_my_new_task.cpp:
case AC_MY_TASK_INIT:
    // Set a timer to send 'AC_MY_TASK_BLINK_LED' to 'AC_TASK_MY_NEW_TASK_ID' every 500ms
    timer_set(AC_TASK_MY_NEW_TASK_ID, AC_MY_TASK_BLINK_LED, 500, TIMER_PERIODIC);
    break;
```

---

## Tutorial 8: Creating a Custom Hardware Driver & Updating Makefiles
Instead of just using the buzzer, let's pretend you wired an LED to a specific pin and want to write a driver for it. When you create new files or folders, you **must update the Makefiles** so the compiler knows they exist!

**Goal:** Create `my_led.c` and add it to the build system.
1. Inside `application/sources/driver/`, create a new folder called `my_led`.
2. Inside that folder, create `my_led.c` and `my_led.h`:
```c
#include "my_led.h"
#include "stm32l1xx_gpio.h" // STM32 Hardware Library

void my_led_init() {
    // Hardware configuration math
}

void my_led_toggle() {
    // Hardware command to flip the pin
}
```
3. **The Crucial Step (Makefile):** Create a file called `Makefile.mk` inside `application/sources/driver/my_led/`:
```makefile
SOURCES += sources/driver/my_led/my_led.c
INCLUDES += -Isources/driver/my_led
```
4. Finally, tell the main driver build system about your folder. Open `application/sources/driver/Makefile.mk` and add:
```makefile
include sources/driver/my_led/Makefile.mk
```
Now the compiler will successfully find and build your new driver!

---

## Tutorial 9: Creating a Custom UI Screen
The AK Kit uses a Screen Manager. You don't just draw randomly; you create a "Screen Object".

**Goal:** Define a new screen.
1. In `application/sources/app/screens/`, create `scr_my_screen.cpp`.
2. Define the view function and the handler:
```cpp
#include "screen_manager.h"

// 1. The View (Drawing)
void view_scr_my_screen() {
    view_render.clear();
    view_render.setCursor(0,0);
    view_render.print("My Custom UI!");
}

// 2. The Screen Object
view_dynamic_t dyn_view_my_screen = {{.item_type = ITEM_TYPE_DYNAMIC}, view_scr_my_screen};
view_screen_t scr_my_screen = {&dyn_view_my_screen, ITEM_NULL, ITEM_NULL, 0};

// 3. The Handler (Buttons)
void scr_my_screen_handle(ak_msg_t *msg) {
    if (msg->sig == SCREEN_ENTRY) {
        view_render_screen(&scr_my_screen); // Draw it when we enter!
    }
}
```

---

## Tutorial 10: Tying It All Together!
Let's look at the incredible embedded system flow you just learned to build:

1. **Initialization:** Inside `app.cpp`, you call `my_led_init()` to set up your hardware pin.
2. **User Input:** The user presses the UP button. The OS posts a message to `scr_menu_handle`.
3. **Screen Transition:** `scr_menu_handle` calls `SCREEN_TRAN(scr_my_screen_handle, &scr_my_screen)` to switch to your custom UI.
4. **Task Trigger:** Inside your new screen, pressing DOWN calls `task_post_pure_msg` to wake up `AC_TASK_MY_NEW_TASK_ID`.
5. **The Timer & Driver:** Your task receives the message, calls `timer_set()` to loop every 500ms, and every 500ms it calls `my_led_toggle()` from your custom driver to blink the LED!

Congratulations! You now understand the full architecture of the AK Embedded OS!

---
<br>

[< Back to 4. Hardware & Peripherals](4_HARDWARE_PERIPHERALS.md) | [Next: 6. Resources & Troubleshooting >](6_RESOURCES_TROUBLESHOOTING.md)

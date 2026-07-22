# 1. Introduction: Welcome to the World of Embedded Systems!

Welcome! If you are reading this, you are about to take your very first step into the fascinating world of embedded systems. 

## What is an Embedded System?
Look around you. Your microwave, your washing machine, the smart thermostat on your wall, and the anti-lock braking system in your car all of these contain tiny computers dedicated to performing very specific tasks. Unlike your laptop or smartphone, which are designed to do everything from browsing the web to playing video games, an **embedded system** is built to do one thing, and do it extremely well.

In this journey, you will learn how to write the "brain" for one of these systems!

---

## What is the AK Embedded Base Kit?
The **AK Embedded Base Kit** is your learning playground. It is a specially designed circuit board loaded with various components (like buttons, LED, and a LCD) that you can program to interact with the real world. 

Think of it as a blank canvas. By writing code, you will tell this board exactly how to behave.

### The Brain: STM32L151 Microcontroller
At the center of your board is a black square chip. This is the **Microcontroller Unit (MCU)**, specifically the **STM32L151**. 
- **Micro** because it's tiny.
- **Controller** because it controls everything else on the board.
- It contains its own memory (to store your code) and processor (to execute your code).

Every piece of code you write will be sent to this chip.

---

## Hardware Features (What's on the board?)
To make learning fun, the AK Kit comes with several built-in "peripherals" (components connected to the brain). Here is what you will be playing with:

1. **LEDs (Lights):** Simple indicators you can turn on, off, or blink to say "Hello World!" visually.
2. **Push Buttons:** Your primary way of sending input to the board. You can program the board to react when a button is pressed.
3. **Buzzer:** A small speaker that can generate tones and beeps.
4. **LCD Screen:** A small display where you can print text, numbers, or simple graphics.
5. **UART Port:** How the board talks to your computer and gets power.
6. **USB Port:** How a computer can access the board chips.

---

## Board Layout Overview
When you hold the board in your hands, take a moment to identify these parts:
- **The Center:** The STM32 Microcontroller.
- **The Edges:** You'll see rows of metal pins. These are used to connect external sensors or motors later in your journey.
- **The Top/Bottom:** The USB port for power and programming.

> **Your Next Step:** Now that you know what you're holding, it's time to set up your computer so it can talk to the board. Head over to **[2. Getting Started](2_GETTING_STARTED.md)** to prepare your tools!

---
<br>

[< Back to Table of Contents](OVERALL.md) | [Next: 2. Getting Started >](2_GETTING_STARTED.md)

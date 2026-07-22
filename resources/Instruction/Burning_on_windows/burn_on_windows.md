# How to successfully burn on windows

## Prerequisites
1) STM32 board (example: STM32L151CBT6)
2) ST-LINK debugger (make sure it is connected correctly to SWD pins)
3) USB cable
4) Board powered and connected
5) Windows 10/11
6) Install VS Code editor
7) Install WSL2 (Ubuntu)
8) Install USBIPD (for connecting ST-LINK from Windows to WSL)

---

## Installation of the GCC
1) Install Linux build tools `wsl --install -d Ubuntu`
2) set up the enviroment:
```
sudo apt update
sudo apt upgrade -y
sudo apt install -y build-essential wget unzip tar usbutils
```
3) Install ARM GCC Toolchain `gcc-arm-none-eabi-10.3-2021.10-x86_64-linux`
4) Install STM32CubeProgrammer Linux version `STM32_Programmer.sh`
5) Install USBIPD `winget install usbipd`

Note, check that all installation are done:
1) WSL extension `wsl.exe --status`
2) Linux build tools `make --version`
3) GCC Version `gcc --version`
4) ARM GCC Toolchain `arm-none-eabi-gcc --version`
5) Check local path for gcc `/home/josef-wsl/Workspace/Tools/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gcc --version`
6) Check local path for STM32CubeProgrammer `/home/josef-wsl/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer.sh --version`
7) Check USB tools `lsusb --version`
8) Check if all make tools are installed:
```
make --version
gcc --version
lsusb --version
usbipd --version
```
9) Run `lsusb` and make sure you see something like "0483:3748 STMicroelectronics ST-LINK"

---

## How to run successfully
1) Clone a project such as this project:
```
git clone https://github.com/joseftanlang/Ak_kit_worm_game.git
```
2) Now from the root folder of this project go to application:
```
cd  application/
```
3) Build successfully:
```
make clean 
make all
```
4) Check in the WSL when run `lsusb` did you see something like: "STMicroelectronics ST-LINK/V2"
5) If you do not see, go to Powershell and run as administrator then do `usbipd attach --wsl --busid 1-1`, once done go back to WSL and run `lsusb` again and now you would be able to see something like: "STMicroelectronics ST-LINK/V2"
6) Flash / Burn successfully:
```
make flash
```

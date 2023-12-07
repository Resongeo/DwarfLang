# HasteLang
Language interpreter written in C++ based on the **Crafting Interpreters** book. It currently only tested on Windows 11.

## Requirements
- Visual Studio 2022
- Python 3.x

## Building
- Clone the repository
``` bash
git clone https://github.com/Resongeo/HasteLang
```
- Run the GenerateProject.py file
``` bash
python .\Tools\GenerateProject.py
```
> You can call this script from anywhere
- If you run this the first time it will prompt you to download the premake binaries. If its present it will run the `premake5.lua` script and generate the `HasteLang.sln` file in the root of the project.

## Usage
If no args given it will print out some info
```bash
> .\HasteLang.exe
> Welcome to the Haste Language!
```
You can interpret code straight from the terminal
```bash
> .\HasteLang.exe "var a = 10; print(a);"
> 10.000000
```
> It is important to put the code between quotes

Of you can provide a file using the `-f` flag
```bash
> .\HasteLang.exe -f .\Test.ht
> 10.000000
```

Test.ht:
```js
var a = 10;
print(a);
```
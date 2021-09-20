# arduFPGA-assembler
Is dependent of "arduFPGA-app-common" library's.

This assembler is intended to run on arduFPGA game console and arduFPGA development board, but with some changes will be able to fit into an ATmega32u4 or similar microcontroller with an external uSD and external RAM/FRAM serial memory to temporary store the edited ASM file, a ssd1306 or similar display and a small keyboard ( a hardware like an ArduBoy with an external serial RAM/FRAM serial memory ).

I will try to implement most of the desktop AVR ASM compiler functionalities together with an file editor being able to handle large ASM projects composed of multiple files.

I will try to create an assembler for ATmega/ATxmega self programing like old Personal Computers like ZX Spectrum and others like it.

There is an emulator developed at the same time for faster development and debugging of the editor/compiler code.

The emulator is done with Qt community edition.

### 2020/09/20
Initial release:

  The file editor is ready in emulator and is able to load, switch between opened files, files are created in a virtual FS.
  The menu is not ready yet.
  The same code is ported on an ATmega32u4 uC project to check the code size and static RAM usage in order to fit the code and optimize it specifically for ATmega core..

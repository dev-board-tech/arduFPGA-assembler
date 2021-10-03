# arduFPGA-assembler
Is dependent of "arduFPGA-app-common" library's.

This assembler is intended to run on arduFPGA game console and arduFPGA development board, but with some changes will be able to fit into an ATmega32u4 or similar microcontroller with an external uSD and external RAM/FRAM serial memory to temporary store the edited ASM file, a ssd1306 or similar display and a small keyboard ( a hardware like an ArduBoy with an external serial RAM/FRAM serial memory ).

I will try to implement most of the desktop AVR ASM compiler functionalities together with an file editor being able to handle large ASM projects composed of multiple files.

I will try to create an assembler for ATmega/ATxmega self programing like old Personal Computers like ZX Spectrum and others like it.

There is an emulator developed at the same time for faster development and debugging of the editor/compiler code.

The emulator is done with Qt community edition.

## Description:

Every project will be placed in it's own directory including one or multiple project files "\*.prj" that contain the relative paths of the dependency files that will be available for editing using cursor saving, the "\*.prj" file need to have a self include line in order to be available for editing this way the "\*.prj" file can have definition directives in order to be able to have multiple project configurations with the same source files.

Only the imported files from project file will be available for editing from file editor with cursor saving, the rest will be edited thru a open file dialog choosing from all imported files from last compilation.

### 2020/10/03

 Add duplicate label check and include files from source file functions.

 Is able to import files from a project file, and files from imported files imported from project file.

### 2020/09/20

Initial release:

  The file editor is ready in emulator and is able to load, switch between opened files, files are created in a virtual FS.

  The menu is not ready yet.

  The same code is ported on an ATmega32u4 uC project to check the code size and static RAM usage in order to fit the code and optimize it specifically for ATmega core.

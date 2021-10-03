#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include <QtDebug>
#include "def.h"
#include "driver/spi.h"
#include "textEditor.h"
#include "avr-asm-compiler.h"

#include "fat_fs/inc/ff.h"

#include DISPLAY_DRIVER_FILE

QGraphicsView *graphicsView_Display;
QGraphicsScene *scene;
extern uint8_t *vram;
box_t box = {0, 128, 0, 64};// For ssd1306 128x64 pixels.
spi_t spi;
char textBuff[256];

FIL prjFil;
FATFS fatFs0;
extern FATFS *FatFs[];
uint8_t workBuff[24576];
uint8_t fsVirtualDisk0[256 * 1024];
textEditor_t fileEditor;

bool drv_connected(void*) {
    return true;
}
DRESULT	drv_r_func0(void *, void* _Buffer, unsigned long _block, unsigned int nblks) {
    memcpy(_Buffer, fsVirtualDisk0 + (_block * 512), nblks * 512);
    return RES_OK;
}
DRESULT	drv_w_func0(void *, void* _Buffer, unsigned long _block, unsigned int nblks) {
    memcpy(fsVirtualDisk0 + (_block * 512), _Buffer, nblks * 512);
    return RES_OK;
}
DRESULT	drv_ioctl_func0(void *, unsigned int  command,  unsigned int *buffer) {
    switch(command) {
        case GET_SECTOR_COUNT:
            *buffer = sizeof(fsVirtualDisk0) / 512;
            break;
        case GET_SECTOR_SIZE:
            *buffer = 512;
            break;
        case CTRL_SYNC :        /* Make sure that no pending write process */
            break;
        default:
            *buffer = 0;
            break;
    }
    return RES_OK;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menubar->setVisible(false);
    ui->statusbar->setVisible(false);

    FatFs[0] = &fatFs0;
    FatFs[0]->drv_rw_func.drv_connected = drv_connected;
    FatFs[0]->drv_rw_func.drv_r_func = drv_r_func0;
    FatFs[0]->drv_rw_func.drv_w_func = drv_w_func0;
    FatFs[0]->drv_rw_func.drv_ioctl_func = drv_ioctl_func0;
    FatFs[0]->drv_rw_func.DriveStruct = (void *)-1;
    qDebug() << sizeof(fileEditor);
    if(f_mkfs((TCHAR *)"0:", FM_ANY, 512, workBuff, sizeof(workBuff)) != FR_OK) {
        qDebug() << "ERROR: Formatting disk 0.";
    } else {
        qDebug() << "OK: Formatting disk 0.";
    }
    /*if(f_chdrive((TCHAR *)"0:") != FR_OK) {
        qDebug() << "ERROR: Changing drive.";
    } else {
        qDebug() << "OK: Changing drive.";
    }*/
    if(f_mkdir((TCHAR *)"/project") != FR_OK) {
        qDebug() << "ERROR: Creating project directory.";
    } else {
        qDebug() << "OK: Creating project directory.";
    }
    if(f_chdir((TCHAR *)"project") != FR_OK) {
        qDebug() << "ERROR: Changing directory.";
    } else {
        qDebug() << "OK: Changing directory.";
    }
    if(f_open(&prjFil, ((TCHAR *)"test.prj"), FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) {
        qDebug() << "ERROR: Creating project file.";
    } else {
        qDebug() << "OK: Creating project file.";
    }
    /***********************************************************/
    if(f_open(&prjFil, (TCHAR *)"main.asm", FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) {
        qDebug() << "ERROR: Creating main.asm file.";
    } else {
        qDebug() << "OK: Creating main.asm file.";
    }
    qDebug() << "WRITTEN: " << f_puts((TCHAR *) "#INCLUDE \"draw.asm\"\n"
                                                "#INCLUDE \"ssd1306.asm\"\n"
                                                "#INCLUDE \"ssd1306.asm\"\n"
                                                "\n"
                                                "RESET:\n"
                                                "\tLDI R16, 0xFF\n"
                                                "\tOUT 0X22, R16\n"
                                                "LOOP:\n"
                                                "\tCLR R16\n"
                                                "\tMOV R17, R16\n"
                                                "\tRCALL DO_SOMETHING\n"
                                                "\tRJMP LOOP\n"
                                                "DO_SOMETHING:\n"
                                                "\tIN R18, 0X23\n"
                                                "\tANDI R18, 1<<3\n"
                                                "\tORI R18, 1<<4\n"
                                                "\tOUT 0X23, R18\n"
                                                "\tRET\n", &prjFil);
    f_close(&prjFil);
/***********************************************************/
    if(f_open(&prjFil, ((TCHAR *)"draw.asm"), FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) {
        qDebug() << "ERROR: Creating draw.asm file.";
    } else {
        qDebug() << "OK: Creating draw.asm file.";
    }
    qDebug() << "WRITTEN: " << f_puts((TCHAR *) "RESET:\n"
                                                "\tLDI R16, 0xFF\n"
                                                "\tOUT 0X22, R16\n"
                                                "DRAW_C:\n"
                                                "\tCLR R16\n"
                                                "\tMOV R17, R16\n"
                                                "\tRCALL DO_SOMETHING\n"
                                                "\tRJMP LOOP\n"
                                                "DRAW_S:\n"
                                                "\tIN R18, 0X23\n"
                                                "\tANDI R18, 1<<3\n"
                                                "\tORI R18, 1<<4\n"
                                                "\tOUT 0X23, R18\n"
                                                "\tRET\n", &prjFil);
    f_close(&prjFil);
/***********************************************************/
    if(f_open(&prjFil, ((TCHAR *)"ssd1306.asm"), FA_OPEN_ALWAYS | FA_WRITE) != FR_OK) {
        qDebug() << "ERROR: Creating ssd1306.asm file.";
    } else {
        qDebug() << "OK: Creating ssd1306.asm file.";
    }
    qDebug() << "WRITTEN: " << f_puts((TCHAR *) "SSD1306_INIT:\n"
                                                "\tLDI R16, 0xFF\n"
                                                "\tOUT 0X22, R16\n"
                                                "SSD1306_CLR:\n"
                                                "\tCLR R16\n"
                                                "\tMOV R17, R16\n"
                                                "\tRCALL DO_SOMETHING\n"
                                                "\tRJMP LOOP\n"
                                                "SSD1306_DRAW_PIXEL:\n"
                                                "\tIN R18, 0X23\n"
                                                "\tANDI R18, 1<<3\n"
                                                "\tORI R18, 1<<4\n"
                                                "\tOUT 0X23, R18\n"
                                                "\tRET\n", &prjFil);
    f_close(&prjFil);
/***********************************************************/

    vram = (uint8_t *)calloc(1, DISPLAY_FUNC_GET_X() * DISPLAY_FUNC_GET_Y() * sizeof(uint8_t));
    memset(textBuff, 0, sizeof(textBuff));

    graphicsView_Display = ui->graphicsView_Display;
    scene = new QGraphicsScene();
    ui->graphicsView_Display->setScene(scene);

    fileEditor.filePtr = (uint32_t)textBuff;
    fileEditor.maxFileLen = sizeof(textBuff);
    fileEditor.box = box;
    fileEditor.gfxString.foreColor = false;
    fileEditor.gfxString.inkColor = true;
    fileEditor.gfxString.spi = &spi;
    fileEditor.gfxString.tabSpaces = 3;
    fileEditor.gfxString.vram = vram;
    fileEditor.gfxString.wordWrap = false;
    fileEditor.gfxString.maxLen = 0;
    fileEditor.gfxString.maxLineLen = 0;
    fileEditor.textEditMode = false;
    textEditor_Init(&fileEditor);
    addFile(&fileEditor, (char *)"main.asm");
    addFile(&fileEditor, (char *)"draw.asm");
    addFile(&fileEditor, (char *)"ssd1306.asm");
    if(changeFile(&fileEditor, 0)) {
        qDebug() << "ERROR: Changing file 1.";
    } else {
        qDebug() << "OK: Changing file 1.";
    }
    if(changeFile(&fileEditor, 1)) {
        qDebug() << "ERROR: Changing file 2.";
    } else {
        qDebug() << "OK: Changing file 2.";
    }
    if(changeFile(&fileEditor, 2)) {
        qDebug() << "ERROR: Changing file 3.";
    } else {
        qDebug() << "OK: Changing file 3.";
    }
    if(changeFile(&fileEditor, 0)) {
        qDebug() << "ERROR: Changing file 4.";
    } else {
        qDebug() << "OK: Changing file 4.";
    }

    avrAsmCompiler_Compile((void **)fileEditor.files);


    timerLoop.setInterval(10);
    connect(&timerLoop, SIGNAL(timeout()), this, SLOT(loopRefresh()));
    timerLoop.start();

    ui->graphicsView_Display->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//#define USE_TEXT_EDITOR

bool MainWindow::eventFilter(QObject* , QEvent* event) {
    if (event->type()==QEvent::KeyPress) {
        QKeyEvent* key = static_cast<QKeyEvent*>(event);
        if(key->key() == Qt::Key_Up) {
            textEditor_goUp(&fileEditor);
        } else if(key->key() == Qt::Key_Down) {
            textEditor_goDown(&fileEditor);
        } else if(key->key() == Qt::Key_Left) {
            textEditor_goLeft(&fileEditor);
        } else if(key->key() == Qt::Key_Right) {
            textEditor_goRight(&fileEditor);
        } else if(key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) {
            textEditor_edit(&fileEditor, '\n');
        } else if(key->key() >= Qt::Key_Space && key->key() < Qt::Key_AsciiTilde) {
            textEditor_edit(&fileEditor, (uint8_t)key->key());
        } else if(key->key() == Qt::Key_Backspace) {
            textEditor_edit(&fileEditor, 0x08);
        } else if(key->key() == Qt::Key_Home) {
        } else if(key->key() == Qt::Key_End) {
        } else if(key->key() == Qt::Key_PageUp) {
            //textEditor_pageUp(&fileEditor);
        } else if(key->key() == Qt::Key_PageDown) {
            //textEditor_pageDown(&fileEditor);
        } else if(key->key() == Qt::Key_Delete) {
            textEditor_edit(&fileEditor, (uint8_t)key->key());
        } else if(key->key() == Qt::Key_Tab) {
            textEditor_edit(&fileEditor, '\t');
        }
        return true;
    }
    return false;
}

void MainWindow::loopRefresh() {
    timerLoop.stop();
    textEditor_Idle(&fileEditor);
    timerLoop.start();
}

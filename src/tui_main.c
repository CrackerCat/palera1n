#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <assert.h>

#include <common.h>
#include <tui.h>

int redraw_screen() {
    return 0;
}

int destroy_window() {
    return 0;
}

int init_window() {
    setlocale(LC_ALL, NULL);
    if (getenv("NEWT_COLORS") == NULL)
        putenv(
            "NEWT_COLORS=root=,black\n"
            "border=lightgray,black\n"
            "title=lightgray,black\n"
            "roottext=red,black\n"
            "label=lightgray,black\n"
            "entry=lightgray,black\n"
            "window=red,black\n"
            "textbox=lightgray,black\n"
            "button=black,lightgray\n"
            "compactbutton=lightgray,black\n"
            "listbox=lightgray,black\n"
            "actlistbox=black,lightgray\n"
            "actsellistbox=black,lightgray\n"
            "checkbox=lightgray,black\n"
            "actcheckbox=black,lightgray\n");

    newtInit();
    newtCls();
    newtDrawRootText(0, 0, "palera1n version 2.0.0");
    newtPushHelpLine(NULL);
    return 0;
}

int tui() {
    init_window();
    int ret = MAIN_SCREEN;
    while (1) {
        switch (ret) {
        case ERROR_SCREEN:
            goto out;
            break;
        case EXIT_SCREEN:
            goto out;
            break;
        case MAIN_SCREEN:
            ret = tui_screen_main();
            break;
        case OPTIONS_SCREEN:
            ret = tui_screen_options();
            break;
        case ENTER_RECOVERY_SCREEN:
            ret = tui_screen_enter_recovery();
            break;
        case ENTER_DFU_SCREEN:
            ret = tui_screen_enter_dfu();
            break;
        case JAILBREAKING_SCREEN:
            ret = tui_screen_jailbreak();
            break;
        default:
            assert(0);
            goto out;
        }
        newtPopWindow();
    }
out:
    newtFinished();
    return 0;

}

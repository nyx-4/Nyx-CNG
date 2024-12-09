#include<iostream>
using namespace std;
#include "../Nyx-ANSI/ANSI.h"
#include "NyxSS.h"

struct List { // For DDL & TB & RB
    string Title;
    string* Opts;
    int nOpts;
    int cur;
};
struct Select { // For CB & LB
    string Title;
    string* Opts;
    int nOpts;
    bool* cur;
};
struct TS {
    bool cur;
};

struct LBL { // For LBL & TXT
    string Label;
};

void cb(Select CheckBox, int y, int x, int width) {
    if (width == 0) {
        for (int i = 0; i < CheckBox.nOpts; i++)
            if (CheckBox.Opts[i].length() > width) width = CheckBox.Opts[i].length();
        width += 7;
    }
    box(y, x, CheckBox.nOpts + 2, width);
    gotoyx(y, 2);
    cout << CheckBox.Title;
    for (int i = 0; i < CheckBox.nOpts; i++) {
        gotoyx(y + i + 1, x + 1);
        if (CheckBox.cur[i] == true) cout << "[x] ";
        else cout << "[ ] ";
        cout << CheckBox.Opts[i];
    }
}


void window() { // box + menubar + menu(s)

}

int main() {
    cout << CLEAR;
    string File[] = { "New", "Open", "Save", "Save As", "Exit" };
    string Edit[] = { "Undo", "Redo", "Cut", "Copy", "Paste", "Find", "Replace" };
    string View[] = { "Open View...", "Appearance", "Run", "Extension", "Word Wrap" };
    string Run[] = { "Start", "Stop", "Toggle", "compile", "Run", "Compile & Run" };
    string Help[] = { "Welcome", "Documentation", "Keyboard Shortcut", "About" };

    Smenu MyMenu[5] = {
        Smenu({ "File", File, 5 }),
        Smenu({ "Edit", Edit, 7 }),
        Smenu({ "View", View, 5 }),
        Smenu({ "Run", Run, 6 }),
        Smenu({ "Help", Help, 4 }),
    };
    bool cur[5] = { 0,1,1 };
    Smenubar MyMenubar = Smenubar({ MyMenu, 5 });
    char ch = '.';
    do {
        cout << CLEAR;
        box(1, 1, 8, 50);
        menubar(MyMenubar, 0, 0, BG_WHITE + FG_YELLOW, BG_BLUE, ch);
    } while ((ch = getchar()) != 'x');
    // Select MySelect = Select({ "File", File,5,cur });
    // char ch = '.';
    // do {
    //     cout << CLEAR;
    //     cb(MySelect, 1, 1, 0);
    // } while ((ch = getchar()) != 'x');
    getchar();
    return 0;
}

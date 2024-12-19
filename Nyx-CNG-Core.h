// system("date +'%a %b %0e  %H:%M'");  // Length = 17


struct Smenu {
    string Title;

    string* Opts;
    int nOpts;
};

struct Smenubar {
    Smenu* Menu;
    int nMenu;
};

void gotoyx(int y, int x) {
    cout << "\033[" << y << ";" << x << "H";
}

void box(int start_row, int start_col, int height, int width, char Title[]) {
    cout << START_LINE_MODE;
    gotoyx(start_row, start_col);
    cout << "l";
    for (int i = 1; i < width - 1; i++) cout << "q";
    cout << "k";

    for (int i = 1; i < height - 1;i++) {
        gotoyx(i + start_row, start_col);
        cout << "x";
        gotoyx(i + start_row, start_col + width - 1);
        cout << "x";
    }

    gotoyx(start_row + height - 1, start_col);
    cout << "m";
    for (int i = 1; i < width - 1; i++) cout << "q";
    cout << "j";
    cout << STOP_LINE_MODE;
    gotoyx(start_row, start_col + 2);
    cout << Title;
}

void vr(int start_row, int start_col, int length, char start_ch = 'w', char line_ch = 'x', char end_ch = 'v') {
    cout << START_LINE_MODE;
    gotoyx(start_row, start_col);
    cout << start_ch;
    for (int i = 1; i < length - 1;i++) {
        gotoyx(i + start_row, start_col);
        cout << line_ch;
    }
    gotoyx(start_row + length - 1, start_col);
    cout << end_ch;

    cout << STOP_LINE_MODE;
}

void hr(int start_row, int start_col, int length, char start_ch = 't', char line_ch = 'q', char end_ch = 'u') {
    cout << START_LINE_MODE;
    gotoyx(start_row, start_col);
    cout << start_ch;
    for (int i = 1; i < length - 1; i++) cout << line_ch;
    cout << end_ch;

    cout << STOP_LINE_MODE;
}

void ch(int start_row_hr, int start_col_hr, int length_hr, int start_row_vr, int start_col_vr, int length_vr,
    char start_vr_ch = 'w', char line_vr_ch = 'x', char end_vr_ch = 'v', char start_hr_ch = 't', char line_hr_ch = 'q',
    char end_hr_ch = 'u', char center_ch = 'n') {

    hr(start_row_hr, start_col_hr, length_hr, start_hr_ch, line_hr_ch, end_hr_ch);
    vr(start_row_vr, start_col_vr, length_vr, start_vr_ch, line_vr_ch, end_vr_ch);
    cout << START_LINE_MODE;
    gotoyx(start_row_hr, start_col_vr);
    cout << center_ch;
    cout << STOP_LINE_MODE;
}

string ResizeStr(string Str, int size, char ch = ' ') {
    string StrOfSize;
    for (int i = 0; i <= size; i++) {
        if (Str.length() > i) StrOfSize += Str[i]; // If Str still have some characters left, add that character
        else StrOfSize += ch;                      // else add white spaces.
    }
    return StrOfSize;
}

void menu(Smenu Menu, int Width, int y, int x, string fUnSelected, string fSelected, int curMenuItem) {
    if (Width == 0) {
        Width = Menu.Opts[0].length();
        for (int i = 1; i < Menu.nOpts; i++)
            if (Menu.Opts[i].length() > Width) Width = Menu.Opts[i].length();
    }
    for (int i = 0; i < Menu.nOpts; i++) {
        gotoyx(y + i, x);
        if (i == curMenuItem) cout << fSelected;
        else cout << fUnSelected;
        cout << ResizeStr(Menu.Opts[i], Width);
        cout << RESET;
    }
}


/*
    char ch = '.';
    do {
        cout << CLEAR;
        box(1, 1, 8, 50);
        menubar(MyMenubar, 0, 0, BG_WHITE + FG_YELLOW, BG_BLUE, ch);
    } while ((ch = getchar()) != 'x');
*/
void menubar(Smenubar MenuBar, int FixedLen, int Width, string fUnSelected, string fSelected, char curInput) {
    int runningLen = 3, x_pad;
    static int curMenuItem = 0, preMenu = 0, curMenu = 0;
    for (int i = 0; i < MenuBar.nMenu; i++) {
        gotoyx(1, runningLen);
        if (i == curMenu) x_pad = runningLen;
        if (FixedLen == 0) runningLen += MenuBar.Menu[i].Title.length() + 1;
        else runningLen += FixedLen;
        cout << MenuBar.Menu[i].Title << "\n";
    }
    gotoyx(2, x_pad);

    if (curInput == 'k') {
        curMenuItem--;
        if (curMenuItem < 0) curMenuItem = MenuBar.Menu[curMenu].nOpts - 1;
    }
    else if (curInput == 'j') {
        curMenuItem++;
        if (curMenuItem > MenuBar.Menu[curMenu].nOpts - 1) curMenuItem = 0;
    }
    else if (curInput == 'h') {
        preMenu = curMenu;
        curMenu--;
        if (curMenu < 0) curMenu = MenuBar.nMenu - 1;
    }
    else if (curInput == 'l') {
        preMenu = curMenu;
        curMenu++;
        if (curMenu > MenuBar.nMenu - 1) curMenu = 0;
    }
    if (curMenu != preMenu) {
        preMenu = curMenu;
        curMenuItem = 0;
    }
    else menu(MenuBar.Menu[curMenu], Width, 2, x_pad, fUnSelected, fSelected, curMenuItem);
}

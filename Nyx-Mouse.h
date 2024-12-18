// @param x The x position (Column) of Mouse when event trigered
// @param y The y position (Row) of Mouse when event trigered
// @param z The raw state of Modifiers and Button
// @param MB The Mouse Button state when event trigered. (0, Primary Button);  (1, Middle Button);  (2, Secondary Button);  (3, Release);
//           The Button encoding might be different on other machines.
// @param Shift True if Shift was pressed
// @param Alt True if Alt was pressed
// @param Ctrl True if Ctrl was pressed
// @param ScrUp True if event was Scroll up.
// @param ScrDn True if event was Scroll Down.
// @param Release True when mouse button was released. False when it was clicked. Use for drag event.
// @warning Don't use if its not supported mouse event, infinite loops may triger with no way to break loop due to raw mode enabled.
struct MEVENT {
    int x = 0, y = 0, z = 0, MB = 0;
    bool Shift = 0, Alt = 0, Ctrl = 0, ScrUp = 0, ScrDn = 0, Release = 0;
};

struct termios saved_attributes;

char ENABLE_ALT_SCREEN[] = "\033[?1049h";
char DISABLE_ALT_SCREEN[] = "\033[?1049l";
int ALT_SCREEN_SZ = 8;

char ENABLE_MOUSE_TRACKING[] = "\033[?1000h\033[?1006h";
char DISABLE_MOUSE_TRACKING[] = "\033[?1000l\033[?1006l";
int MOUSE_TRACKING_SZ = 16;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &saved_attributes);
    write(STDIN_FILENO, &DISABLE_ALT_SCREEN, ALT_SCREEN_SZ);
    write(STDIN_FILENO, &DISABLE_MOUSE_TRACKING, MOUSE_TRACKING_SZ);
}

void enable_raw_mode(int ChToWait = 0, int TimeToWait = 0, bool enableMouse = false) {
    if (!isatty(STDIN_FILENO)) return;

    write(STDIN_FILENO, &ENABLE_ALT_SCREEN, ALT_SCREEN_SZ);
    if (enableMouse) write(STDIN_FILENO, &ENABLE_MOUSE_TRACKING, MOUSE_TRACKING_SZ);

    tcgetattr(STDIN_FILENO, &saved_attributes);

    struct termios raw = saved_attributes;

    // Enables raw mode.
    raw.c_iflag &= ~(BRKINT | INPCK | PARMRK | INLCR | IGNCR | ISTRIP | ICRNL | IXON);
    //  raw.c_oflag &= ~(OPOST);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cflag &= ~(CSIZE | PARENB);
    raw.c_cflag |= (CS8);

    raw.c_cc[VMIN] = ChToWait;
    raw.c_cc[VTIME] = TimeToWait;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// @brief A utility function to debug the mouse event
void printMouse(MEVENT MouseEvent) {
    cout << "x: " << MouseEvent.x << ", y: " << MouseEvent.y << ", z: " << MouseEvent.z << ", Shift: " << MouseEvent.Shift << ", Alt: " << MouseEvent.Alt << ", Ctrl: " << MouseEvent.Ctrl << ", " << "MB" << MouseEvent.MB << ", ScrUp: " << MouseEvent.ScrUp << ", ScrDn: " << MouseEvent.ScrDn << ", Release: " << MouseEvent.Release << "\n";
}

void handleClick(MEVENT& MouseEvent) {
    char c;

    while (read(STDIN_FILENO, &c, 1) && c != 59)
        MouseEvent.z = MouseEvent.z * 10 + (int)c - 48;

    while (read(STDIN_FILENO, &c, 1) && c != 59)
        MouseEvent.x = MouseEvent.x * 10 + (int)c - 48;

    while (read(STDIN_FILENO, &c, 1) && !(c == 77 || c == 109))
        MouseEvent.y = MouseEvent.y * 10 + (int)c - 48;

    if (c == 109) MouseEvent.Release = 1;

    MouseEvent.MB = MouseEvent.z % 4;           // First and Second bit of z
    MouseEvent.Shift = (MouseEvent.z >> 2) & 1; // Third bit of z
    MouseEvent.Alt = (MouseEvent.z >> 3) & 1;   // Fourth bit of z
    MouseEvent.Ctrl = (MouseEvent.z >> 4) & 1;  // Fifth bit of z
    if ((MouseEvent.z >> 6) & 1)                // Sixth bit of z
        if (MouseEvent.MB == 0) MouseEvent.ScrDn = 1;
        else if (MouseEvent.MB == 1) MouseEvent.ScrUp = 1;
}

// @param MouseEvent Struct of type MEVENT, in which the MouseEvent will be stored.
// @brief This currently only support Mouse `Position/Click/Scroll/SHIFT+ALT+CTRL Modifiers`.
// @note Use it only when c is 27 and then 91
void handleMouse(MEVENT& MouseEvent) {
    char c;
    read(STDIN_FILENO, &c, 1);
    MouseEvent = MEVENT{ 0 };
    switch ((int)c) {
        case 60:
            handleClick(MouseEvent);
            break;
    }
}


// int main(void) {
//     enable_raw_mode(1, 0, true);
//     char c = '1';
//     MEVENT MouseEvent;
//     int Status;
//     while (c != 'q') {
//         Status = read(STDIN_FILENO, &c, 1);
//         if (!Status) cout << "-\n";
//         else if (c == 27) { // ANSI ESC
//             read(STDIN_FILENO, &c, 1);
//             switch ((int)c) {
//                 case 91:
//                     handleMouse(MouseEvent);
//                     printMouse(MouseEvent);
//                     break;
//                 default:
//                     cout << "\\033\n";
//             }
//         }
//         else
//             cout << (int)c << " ('" << c << "')\n";
//     }
//     disable_raw_mode();
//     return 0;
// }

// Basic Escape sequences
char START_LINE_MODE[] = "\033(0";
char STOP_LINE_MODE[] = "\033(B";

// Basic Clear Sequences
char CLEAR[] = "\033c";
char CLEAR_LINE[] = "\033[2K\r";

char CLEAR_SCREEN_Cursor_To_End[] = "\033[0J";
char CLEAR_SCREEN_Beg_to_Cursor[] = "\033[1J";
char CLEAR_SCREEN_FULL_But_Dont_Move_Cursor[] = "\033[2J";

char CLEAR_LINE_Cursor_To_End[] = "\033[0K";
char CLEAR_LINE_Beg_to_Cursor[] = "\033[1K";
char CLEAR_LINE_FULL_But_Dont_Move_Cursor[] = "\033[2K";


char RESET[] = "\033[0m";

char FG_BLACK[] = "\033[30m";
char FG_RED[] = "\033[31m";
char FG_GREEN[] = "\033[32m";
char FG_YELLOW[] = "\033[33m";
char FG_BLUE[] = "\033[34m";
char FG_MAGENTA[] = "\033[35m";
char FG_CYAN[] = "\033[36m";
char FG_WHITE[] = "\033[37m";
char FG_DEFAULT[] = "\033[39m";

char BG_BLACK[] = "\033[40m";
char BG_RED[] = "\033[41m";
char BG_GREEN[] = "\033[42m";
char BG_YELLOW[] = "\033[43m";
char BG_BLUE[] = "\033[44m";
char BG_MAGENTA[] = "\033[45m";
char BG_CYAN[] = "\033[46m";
char BG_WHITE[] = "\033[47m";
char BG_DEFAULT[] = "\033[49m";

char BRIGHT[] = "\033[1m";
char BOLD[] = "\033[1m";
char DIM[] = "\033[2m";
char ITALIC[] = "\033[3m";
char UNDERLINE[] = "\033[4m";
char BLINK[] = "\033[5m";
char REVERSE[] = "\033[7m";
char HIDDEN[] = "\033[8m";
char STRIKETHROUGH[] = "\033[9m";

char RESET_BRIGHT[] = "\033[22m";
char RESET_BOLD[] = "\033[22m";
char RESET_DIM[] = "\033[22m";
char RESET_ITALIC[] = "\033[23m";
char RESET_UNDERLINE[] = "\033[24m";
char RESET_BLINK[] = "\033[25m";
char RESET_REVERSE[] = "\033[27m";
char RESET_HIDDEN[] = "\033[28m";
char RESET_STRIKETHROUGH[] = "\033[29m";

char CURSOR_INVISIBLE[] = "\033[?25l";
char CURSOR_VISIBLE[] = "\033[?25h";
#ifndef CONSOLE_H
#define CONSOLE_H

class Console
{
public:
    enum class Colors
    {
        RED,
        GREEN,
        BLUE,
        WHITE,
        PINK,
        CYAN,
        YELLOW
    };
    

    static void bind (
        const LPCTSTR name,
        const bool topmost = false,
        const Colors textColor = Colors::WHITE,
        const LONG x = 0,
        const LONG y = 0,
        const LONG width = 0,
        const LONG height = 0
    );
    static void detach ();

    static void write (const std::string &message);
    static void clear ();

    static void setTextColor (const Colors color);

protected:
private:
    typedef struct
    {
        HANDLE in, out, error;
    } StdHandle;

    
    static bool m_isBound;

    static StdHandle m_stdHandle;

    static HWND m_wnd;


    static void adjust (LONG x, LONG y, LONG width, LONG height);
    
};

#endif
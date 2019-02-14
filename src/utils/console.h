#ifndef CONSOLE_H
#define CONSOLE_H

#include "singleton.h"


class Console : public Singleton<Console>
{
    friend class Singleton<Console>;

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
    

    void bind (
        const LPCSTR name,
        const bool topmost = false,
        const Colors textColor = Colors::WHITE,
        const int x = 0,
        const int y = 0,
        const int width = 0,
        const int height = 0
    );
    void detach ();

    void print (const std::string &message) const;
    void clear () const;

    void setTextColor (const Colors color) const;

protected:
private:
    typedef struct
    {
        HANDLE in, out, error;
    } StdHandle;

    
    bool m_isBound;

    StdHandle m_stdHandle;

    HWND m_wnd;


    Console ();
    ~Console ();
    
    void adjust (int x, int y, int width, int height);
    
};

#endif
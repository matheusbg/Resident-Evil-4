#include "../common.h"
#include "console.h"


Console::Console () :
    m_isBound { false }
{
}

Console::~Console ()
{
}


void Console::adjust (int x, int y, int width, int height)
{
    if (x == 0 && y == 0 && width == 0 && height == 0)
    {
        RECT consoleRect;
        GetWindowRect (m_wnd, &consoleRect);
        width = consoleRect.right - consoleRect.left;
        height = consoleRect.bottom - consoleRect.top;
        
        RECT desktopRect;
        HWND desktopWnd = GetDesktopWindow ();
        GetWindowRect (desktopWnd, &desktopRect);
        x = (desktopRect.right - desktopRect.left - width) / 2;
        y = (desktopRect.bottom - desktopRect.top - height) / 2;
    }

    MoveWindow (m_wnd, x, y, width, height, TRUE);
}

void Console::bind (
        const LPCSTR name,
        const bool topmost,
        const Colors textColor,
        const int x,
        const int y,
        const int width,
        const int height
    )
{
    /* Attach a console to our current process.
       Note: a process can have only one console. */
    AllocConsole ();

    /* Initialize private variables. */
    m_stdHandle.in = GetStdHandle (STD_INPUT_HANDLE);
    m_stdHandle.out = GetStdHandle (STD_OUTPUT_HANDLE);
    m_stdHandle.error = GetStdHandle (STD_ERROR_HANDLE);

    m_wnd = GetConsoleWindow ();

    adjust (x, y, width, height);

    if (topmost)
    {
        SetWindowPos (m_wnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }

    SetConsoleTitle (name);

    /* Indicates that our console is ready for use. */
    m_isBound = true;

    setTextColor (textColor);
}

void Console::detach ()
{
    if (!m_isBound) return;
    
    FreeConsole ();
    m_isBound = false;
}

void Console::print (const std::string &message) const
{
    if (!m_isBound) return;
    
    DWORD charsWritten;
    WriteConsole (
        m_stdHandle.out,
        message.c_str (),
        message.length (),
        &charsWritten,
        nullptr
    );
}

void Console::clear () const
{
    if (!m_isBound) return;
    
    system ("cls");
}

void Console::setTextColor (const Colors color) const
{
    if (!m_isBound) return;
    
    WORD attributes = 0;
    
    switch (color)
    {
    case Colors::RED:
        {
            attributes |= FOREGROUND_RED;
        }
        break;

    case Colors::GREEN:
        {
            attributes |= FOREGROUND_GREEN;
        }
        break;

    case Colors::BLUE:
        {
            attributes |= FOREGROUND_BLUE;
        }
        break;

    case Colors::WHITE:
        {
            attributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
        break;

    case Colors::PINK:
        {
            attributes |= FOREGROUND_RED | FOREGROUND_BLUE;
        }
        break;

    case Colors::CYAN:
        {
            attributes |= FOREGROUND_GREEN | FOREGROUND_BLUE;
        }
        break;

    case Colors::YELLOW:
        {
            attributes |= FOREGROUND_RED | FOREGROUND_GREEN;
        }
        break;
    }

    SetConsoleTextAttribute (m_stdHandle.out, attributes);
}

#ifndef CONSOLE_H
#define CONSOLE_H

/* Taken from https://stackoverflow.com/questions/311955/redirecting-cout-to-a-console-in-windows. */
void bindConsole (bool bindStdIn, bool bindStdOut, bool bindStdErr);

void detachConsole ();

#endif
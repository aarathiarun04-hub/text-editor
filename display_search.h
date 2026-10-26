/** displayText() - Render current editor state
showCursorPosition() - Display cursor coordinates
findText() - Search for text patterns
replaceText() - Replace text patterns **/


#ifndef DISPLAY_SEARCH_H
#define DISPLAY_SEARCH_H
#include "text_editor.h"
void displayText(TextEditor *editor);
void showCursorPosition(TextEditor *editor);
void findText(TextEditor *editor,char *text);
void replaceText(TextEditor *editor,char *oldtext,char *newtext);
#endif
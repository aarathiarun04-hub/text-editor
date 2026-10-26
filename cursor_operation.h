/** moveCursorUp() / moveCursorDown() - Vertical navigation
moveCursorLeft() / moveCursorRight() - Horizontal navigation
jumpToStartOfFile() / jumpToEndOfFile() - File boundaries
jumpToStartOfLine() / jumpToEndOfLine() - Line boundaries **/


#ifndef CURSER_NAVIGATIONS_H
#define CURSER_NAVIGATIONS_H

#include "text_editor.h"
void moveCursorLeft(TextEditor *editor);
void moveCursorRight(TextEditor *editor);
void moveCursorUp(TextEditor *editor);
void moveCursorDown(TextEditor *editor);
#endif
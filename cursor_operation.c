/** void moveCursorLeft(TextEditor *editor);
void moveCursorRight(TextEditor *editor);
void moveCursorUp(TextEditor *editor);
void moveCursorDown(TextEditor *editor); **/
   #include <string.h>
#include "cursor_operation.h"
#include "text_editor.h"
void moveCursorLeft(TextEditor *editor)
{
   if(editor->cursor != NULL && editor->cursorPos > 0)
    {
        editor->cursorPos--;
    }

}
void moveCursorRight(TextEditor *editor)
{
    if(editor->cursor != NULL && editor->cursorPos < strlen(editor->cursor->data))
    {
        editor->cursorPos++;
    }
}
void moveCursorDown(TextEditor *editor)
{
    if(editor->cursor != NULL && editor->cursor->next != NULL)
    {
        editor->cursor = editor->cursor->next;
        editor->cursorLine++;
        editor->cursorPos = 0;
    }
}
void moveCursorUp(TextEditor *editor)
{
    if(editor->cursor != NULL &&
       editor->cursor->prev != NULL)
    {
        editor->cursor = editor->cursor->prev;

        if(editor->cursorLine > 1)
        {
            editor->cursorLine--;
        }

        editor->cursorPos = 0;
    }
}

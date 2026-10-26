#ifndef READ_UNDO_H
#define READ_UNDO_H
#include "text_editor.h"
typedef struct
{
    char *operation;
    char *text;
    int cursorLine;
    int cursorPos;
} Action;
typedef struct
{
    Action *actions;
    int size;
    int capacity;
} DynamicArrayStack;
void initStack(DynamicArrayStack *stack);
void pushAction(DynamicArrayStack *stack,  char *operation,  char *text,  int cursorLine,  int cursorPos);
Action popAction(DynamicArrayStack *stack);
void clearStack(DynamicArrayStack *stack);
void undo(TextEditor *editor,DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
void redo(TextEditor *editor,  DynamicArrayStack *undoStack, DynamicArrayStack *redoStack);
#endif
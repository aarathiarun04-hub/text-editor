#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "redo_undo.h"
#include "text_operation.h"


void initStack(DynamicArrayStack *stack)
{
    stack->size = 0;
    stack->capacity = 5;
    stack->actions = malloc(sizeof(Action) * stack->capacity);
    if(stack->actions == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
}


void pushAction(DynamicArrayStack *stack,char *operation,  char *text, int cursorLine,int cursorPos)
{
    if(stack->size == stack->capacity)
    {
        stack->capacity = stack->capacity * 2;
        stack->actions =  realloc(stack->actions,sizeof(Action) * stack->capacity);
        if(stack->actions == NULL)
        {
            printf("Memory allocation failed\n");
            exit(1);
        }
    }

    stack->actions[stack->size].operation = malloc(strlen(operation) + 1);
    strcpy(stack->actions[stack->size].operation, operation);
    stack->actions[stack->size].text = malloc(strlen(text) + 1);
    strcpy(stack->actions[stack->size].text, text);

    stack->actions[stack->size].cursorLine = cursorLine;
    stack->actions[stack->size].cursorPos =  cursorPos;
    stack->size++;
}


Action popAction(DynamicArrayStack *stack)
{
    Action action;

    action.operation = NULL;
    action.text = NULL;
    action.cursorLine = 0;
    action.cursorPos = 0;

    if(stack->size == 0)
    {
        return action;
    }

    stack->size--;

    action = stack->actions[stack->size];

    return action;
}


void clearStack(DynamicArrayStack *stack)
{
    int i;

    for(i = 0; i < stack->size; i++)
    {
        free(stack->actions[i].operation);
        free(stack->actions[i].text);
    }

    stack->size = 0;
}

Node *getNodeAtLine(TextEditor *editor, int line)
{
    Node *temp = editor->head;
    int currentLine = 1;

    while(temp != NULL)
    {
        if(currentLine == line)
        {
            return temp;
        }

        temp = temp->next;
        currentLine++;
    }

    return NULL;
}

void undo(TextEditor *editor,   DynamicArrayStack *undoStack,   DynamicArrayStack *redoStack)
{
    Action action;
    Node *temp;
    if(undoStack->size == 0)
    {
        printf("Nothing to undo\n");
        return;
    }

    action = popAction(undoStack);
    if(strcmp(action.operation, "insert") == 0)
    {
        temp = getNodeAtLine(editor, action.cursorLine);

        if(temp != NULL)
        {
            editor->cursor = temp;
            editor->cursorLine = action.cursorLine;
            editor->cursorPos = 0;

            delete_line(editor);
        }
    }
    else if(strcmp(action.operation, "delete") == 0)
    {
        temp = getNodeAtLine(editor, action.cursorLine);

        if(temp != NULL)
        {
            editor->cursor = temp;
            editor->cursorLine = action.cursorLine;
            editor->cursorPos = action.cursorPos;

            free(editor->copy_content);

            editor->copy_content =
                malloc(strlen(action.text) + 1);

            strcpy(editor->copy_content, action.text);

            paste(editor);

            free(editor->copy_content);
            editor->copy_content = NULL;
        }
    }
    else if(strcmp(action.operation, "paste") == 0)
    {
        temp = getNodeAtLine(editor, action.cursorLine);

        if(temp != NULL)
        {
            editor->cursor = temp;
            editor->cursorLine = action.cursorLine;
            editor->cursorPos = action.cursorPos;

            delete_char(editor, strlen(action.text));
        }
    }

    pushAction(redoStack, action.operation,action.text,action.cursorLine, action.cursorPos);
    free(action.operation);
    free(action.text);
    printf("Undo successful\n");
}
void redo(TextEditor *editor,  DynamicArrayStack *undoStack,  DynamicArrayStack *redoStack)
{
    Action action;
    Node *temp;

    if(redoStack->size == 0)
    {
        printf("Nothing to redo\n");
        return;
    }

    action = popAction(redoStack);
    if(strcmp(action.operation, "insert") == 0)
    {
        insert_text(editor, action.text);
    }

    else if(strcmp(action.operation, "delete") == 0)
    {
        temp = getNodeAtLine(editor, action.cursorLine);

        if(temp != NULL)
        {
            editor->cursor = temp;
            editor->cursorLine = action.cursorLine;
            editor->cursorPos = action.cursorPos;

            delete_char(editor, strlen(action.text));
        }
    }


    else if(strcmp(action.operation, "paste") == 0)
    {
        temp = getNodeAtLine(editor, action.cursorLine);

        if(temp != NULL)
        {
            editor->cursor = temp;
            editor->cursorLine = action.cursorLine;
            editor->cursorPos = action.cursorPos;

            free(editor->copy_content);

            editor->copy_content =
                malloc(strlen(action.text) + 1);

            strcpy(editor->copy_content,
                   action.text);

            paste(editor);

            free(editor->copy_content);
            editor->copy_content = NULL;
        }
    }
    pushAction(undoStack, action.operation,  action.text,  action.cursorLine,  action.cursorPos);

    free(action.operation);
    free(action.text);

    printf("Redo successful\n");
}
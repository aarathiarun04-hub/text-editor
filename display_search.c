#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_editor.h"
#include "display_search.h"
#include "text_operation.h"

void displayText(TextEditor *editor)
{
    Node *temp = editor->head;

    while(temp != NULL)
    {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

void showCursorPosition(TextEditor *editor)
{
    printf("Line: %d\n", editor->cursorLine);
    printf("Position: %d\n", editor->cursorPos);
}

void findText(TextEditor *editor, char *text)
{
    Node *temp = editor->head;

    while(temp != NULL)
    {
        char *ptr = strstr(temp->data, text);

        if(ptr != NULL)
        {
            printf("Found\n");
            return;
        }

        temp = temp->next;
    }

    printf("Not found\n");
}

void replaceText(TextEditor *editor, char *oldtext, char *newtext)
{
    Node *temp = editor->head;

    while(temp != NULL)
    {
        char *ptr = strstr(temp->data, oldtext);

        if(ptr != NULL)
        {
            editor->cursor = temp;
            editor->cursorPos = ptr - temp->data;

            cut(editor, strlen(oldtext));

            editor->copy_content = malloc(strlen(newtext) + 1);
            strcpy(editor->copy_content, newtext);

            paste(editor);

            free(editor->copy_content);
            editor->copy_content = NULL;

            break;
        }

        temp = temp->next;
    }
}
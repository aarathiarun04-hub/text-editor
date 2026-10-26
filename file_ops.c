#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file_ops.h"
#include "text_operation.h"

void openFile(TextEditor *editor, char *filename)
{
    FILE *fp;
    char text[100];

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }
  Node *temp = editor->head;
    Node *next;

    while(temp != NULL)
    {
        next = temp->next;

        free(temp->data);
        free(temp);

        temp = next;
    }

    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;
    editor->cursorLine = 1;
    editor->cursorPos = 0;

    while(fgets(text, sizeof(text), fp) != NULL)
    {
        text[strcspn(text, "\n")] = '\0';
        insert_text(editor, text);
    }

   
    if(editor->head != NULL)
    {
        editor->cursor = editor->head;
        editor->cursorLine = 1;
        editor->cursorPos = 0;
    }

    printf("File opened successfully\n");
}

void saveFile(TextEditor *editor, char *filename)
{
    FILE *fp;
    Node *temp;

    fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("File cannot be opened\n");
        return;
    }

    temp = editor->head;

    while(temp != NULL)
    {
        fprintf(fp, "%s\n", temp->data);

        temp = temp->next;
    }

    fclose(fp);

    printf("File saved successfully\n");
}

void closeFile(TextEditor *editor)
{
    Node *temp;
    Node *next;

    temp = editor->head;

    while(temp != NULL)
    {
        next = temp->next;

        free(temp->data);
        free(temp);

        temp = next;
    }

    editor->head = NULL;
    editor->tail = NULL;
    editor->cursor = NULL;

    if(editor->copy_content != NULL)
    {
        free(editor->copy_content);
        editor->copy_content = NULL;
    }

    editor->cursorLine = 1;
    editor->cursorPos = 0;

    printf("Editor closed\n");
}
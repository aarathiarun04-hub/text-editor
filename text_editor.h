#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node
{
    char *data;
    struct Node *prev;
    struct Node *next;
} Node;
typedef struct
{
    Node *head;
    Node *tail;
    Node *cursor;
    char *copy_content;
    int cursorLine;
    int cursorPos;
} TextEditor;
#endif
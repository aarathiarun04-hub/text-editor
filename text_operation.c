#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "text_operation.h"
#include "text_editor.h"
//insert at last
void insert_text(TextEditor *editor,char *text)
{
    Node *newNode;
    Node *temp;
    newNode = malloc(sizeof(Node));

    if(newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

   newNode->data = malloc(strlen(text) + 1);//data ur storing also later modification happen so dynamically store
if(newNode->data == NULL)
    {
        free(newNode);
        printf("Memory allocation failed\n");
        return;
    }
    strcpy(newNode->data, text);
    newNode->next = NULL;
    newNode->prev = NULL;
//empty list
    if (editor->head == NULL)
    {
        editor->head = newNode;
         editor->tail = newNode;
          editor->cursor = newNode;
          editor->cursorLine=1;
          editor->cursorPos=0;

        return;
    }

    temp = editor->head;

    // Go to last node 
    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
    editor->tail = newNode;
     editor->cursor = newNode;
      editor->cursorLine++;
    editor->cursorPos = 0;
}
void delete_char(TextEditor *editor,int count)
{
    char *text;
    int j=0;
    int i;
     if(editor->cursor == NULL)
    {
        printf("No text available\n");
        return;
    }

    if(count <= 0)
    {
        return;
    }

    text=editor->cursor->data;
    for(i=0;i<strlen(text);i++)
    {
        if(!((i>=editor->cursorPos) && (i<(editor->cursorPos)+count)))
    {
text[j++]=text[i];
    }

    }
    text[j]='\0';
    if(editor->cursorPos > strlen(text))
    {
        editor->cursorPos = strlen(text);
    }
}

void copy(TextEditor *editor, int count)
{
    char *text;
    int available;
    int copyCount;

    if(editor->cursor == NULL)
    {
        printf("No text available\n");
        return;
    }

    if(count <= 0)
    {
        return;
    }

    text = editor->cursor->data;

    available = strlen(text) - editor->cursorPos;

    if(available < 0)
    {
        available = 0;
    }

    copyCount = (count < available) ? count : available;

    free(editor->copy_content);

    editor->copy_content = malloc(copyCount + 1);

    if(editor->copy_content == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strncpy(editor->copy_content,
            text + editor->cursorPos,
            copyCount);

    editor->copy_content[copyCount] = '\0';
}

void paste(TextEditor *editor)
{
    int j=0;
    char *text;
    int i;
    char *new_text;

    if(editor->cursor == NULL || editor->copy_content == NULL)
    {
        printf("Nothing to paste\n");
        return;
    }
    text = editor->cursor->data;
    new_text = malloc(strlen(text) + strlen(editor->copy_content) + 1);
    if(new_text == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
 //shift all remaining charcters after count+currentpos tyms
for(int i=0;i<editor->cursorPos;i++)//first half copied 
{
new_text[j++]=text[i];
}
//add after 
for(int i=0;editor->copy_content[i]!='\0';i++)
{
    new_text[j++]=editor->copy_content[i];
}
for(int i=editor->cursorPos;text[i]!='\0';i++)
{
    new_text[j++]=text[i];
}
new_text[j]='\0';
free(editor->cursor->data);
//strcpy(editor->cursor->data,new_text);Because the old memory may be too small not possible to copy
editor->cursor->data = new_text;
  editor->cursorPos += strlen(editor->copy_content);
}

void delete_line(TextEditor *editor)//delte line is deleting one full node
{
    //Node*temp=editor->cursor;//cureent node cursor pointing to
    //if first node
     Node *temp;

    if(editor->head==NULL || editor->cursor==NULL)
    {
        printf("no node to delete");
        return;
    }
 temp = editor->cursor;
     
if(temp->prev == NULL && temp->next == NULL)
    {
        free(temp->data);
        free(temp);
        editor->head = NULL;
        editor->tail = NULL;
        editor->cursor = NULL;
        

        editor->cursorLine = 1;
        editor->cursorPos = 0;
        return;
    }
//first node
if(temp==editor->head)
{
    editor->head=temp->next;
    temp->next->prev=NULL;
  editor->cursor = editor->head;
    free((temp->data));
    free(temp);
    editor->cursorLine = 1;
     editor->cursorPos = 0;
    return;

}
    //if ode is in between
    if(temp==editor->tail)
    {
        editor->tail=temp->prev;
        //temp->prev->next=NULL;
        editor->tail->next = NULL;

        editor->cursor=editor->tail;
        free(temp->data);
        free(temp);
         if(editor->cursorLine > 1)
        {
            editor->cursorLine--;
        }

        editor->cursorPos = 0;
        return;
    }
    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    editor->cursor=temp->next;
    free(temp->data);
    free(temp);
    editor->cursorPos = 0;

}
void cut(TextEditor *editor, int count)
{
     if(editor->cursor == NULL)
    {
        printf("No text available\n");
        return;
    }

    copy(editor, count);
    delete_char(editor, count);
}
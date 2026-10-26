#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "text_editor.h"
#include "text_operation.h"
#include "cursor_operation.h"
#include "file_ops.h"
#include "display_search.h"
#include "redo_undo.h"

void printMenu()
{
    printf("\n");
    printf("1.Insert\n");
    printf("2.Delete Character\n");
    printf("3.Copy\n");
    printf("4.Cut\n");
    printf("5.Paste\n");
    printf("6.Display\n");
    printf("7.Move Cursor Left\n");
    printf("8.Move Cursor Right\n");
    printf("9.Move Cursor Up\n");
    printf("10.Move Cursor Down\n");
    printf("11.Show Cursor Position\n");
    printf("12.Find Text\n");
    printf("13.Replace Text\n");
    printf("14.Open File\n");
    printf("15.Save File\n");
    printf("16.Close Editor\n");
    printf("17.Undo\n");
    printf("18.Redo\n");
    printf("19.Exit\n");
}

int main()
{
    TextEditor editor;
    DynamicArrayStack undoStack;
    DynamicArrayStack redoStack;
    int choice;
    int count;
    char text[100];
    char filename[100];
    char oldtext[100];
    char newtext[100];
    editor.head = NULL;
    editor.tail = NULL;
    editor.cursor = NULL;
    editor.copy_content = NULL;
    editor.cursorLine = 1;
    editor.cursorPos = 0;
    initStack(&undoStack);
    initStack(&redoStack);

    while(1)
    {
        printMenu();
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice)
{
            case 1:
                printf("Enter text: ");
                scanf(" %[^\n]", text);
                insert_text(&editor, text);
                pushAction(&undoStack, "insert", text,editor.cursorLine, editor.cursorPos);
                clearStack(&redoStack);
                break;
            case 2:

                if(editor.cursor != NULL)
                {
                    printf("Enter number of characters to delete: ");
                    scanf("%d", &count);

                    if(count > 0 && editor.cursorPos + count <=strlen(editor.cursor->data))
                    {
                        char deletedText[100];
                        strncpy(deletedText,editor.cursor->data +editor.cursorPos,count);
                       deletedText[count] = '\0';
                        pushAction(&undoStack, "delete", deletedText,editor.cursorLine,editor.cursorPos);
delete_char(&editor, count);
clearStack(&redoStack);
                    }
                    else
                    {
                        printf("Invalid number of characters\n");
                    }
                }
                else
                {
                    printf("No text available\n");
                }

                break;
            case 3:

                if(editor.cursor != NULL)
                {
                    printf("Enter number of characters to copy: ");
                    scanf("%d", &count);
                    copy(&editor, count);
                }
                else
                {
                    printf("No text available\n");
                }

                break;
            case 4:
                if(editor.cursor != NULL)
                {
                    printf("Enter number of characters to cut: ");
                    scanf("%d", &count);
                    if(count > 0 && editor.cursorPos + count <= strlen(editor.cursor->data))
                    {
                        char cutText[100];
                        strncpy(cutText, editor.cursor->data + editor.cursorPos, count);
                        cutText[count] = '\0';
                        pushAction(&undoStack,"delete",   cutText,   editor.cursorLine,  editor.cursorPos);
                        cut(&editor, count);
                        clearStack(&redoStack);//stack sstores up the action
                    }
                    else
                    {
                        printf("Invalid number of characters\n");
                    }
                }
                else
                {
                    printf("No text available\n");
                }

                break;
            case 5:

                if(editor.cursor != NULL && editor.copy_content != NULL)
                {
                    pushAction(&undoStack,  "paste",  editor.copy_content,  editor.cursorLine,  editor.cursorPos);
                    paste(&editor);
                    clearStack(&redoStack);
                }
                else
                {
                    printf("Nothing to paste\n");
                }

                break;

            case 6:
                displayText(&editor);
                break;
            case 7:

                if(editor.cursor != NULL)
                {
                    moveCursorLeft(&editor);
                }

                break;
            case 8:
                if(editor.cursor != NULL)
                {
                    moveCursorRight(&editor);
                }

                break;
            case 9:

                if(editor.cursor != NULL)
                {
                    moveCursorUp(&editor);
                }

                break;
            case 10:

                if(editor.cursor != NULL)
                {
                    moveCursorDown(&editor);
                }

                break;

            case 11:

                showCursorPosition(&editor);

                break;
            case 12:

                printf("Enter text to find: ");
                scanf(" %[^\n]", text);
                findText(&editor, text);
                break;
            case 13:

                printf("Enter old text: ");
                scanf(" %[^\n]", oldtext);
                printf("Enter new text: ");
                scanf(" %[^\n]", newtext);
                replaceText(&editor,  oldtext,  newtext);
                break;
            case 14:

                printf("Enter filename: ");
                scanf("%s", filename);

                openFile(&editor, filename);

                break;
            case 15:

                printf("Enter filename: ");
                scanf("%s", filename);

                saveFile(&editor, filename);

                break;

            case 16:

                closeFile(&editor);
                clearStack(&undoStack);
                clearStack(&redoStack);
                break;
            case 17:
                undo(&editor,  &undoStack,  &redoStack);
                break;
            case 18:
                redo(&editor,  &undoStack, &redoStack);
                break;
            case 19:

                closeFile(&editor);

                clearStack(&undoStack);
                clearStack(&redoStack);

                free(undoStack.actions);
                free(redoStack.actions);

                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
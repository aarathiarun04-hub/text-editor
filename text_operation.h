
//inserttext,copytext,deletechar,copytext,cut,paste,delete
/** insertText() - Insert text at cursor position
deleteCharacters() - Remove specified number of characters
copyText() / cutText() / pasteText() - Clipboard operations
deleteLine() - Remove entire line **/

#ifndef TEXT_OPERATION_H
#define TEXT_OPERATION_H
#include "text_editor.h"
 void insert_text(TextEditor *editor,char *text);//in main insertText(&editor, "Hello");
 void delete_char(TextEditor *editor,int count);
 void copy(TextEditor *editor,int count);
 //count
 // ↓
//how many characters to delete
  void cut(TextEditor *editor,int count);
   void paste(TextEditor *editor);
    void delete_line(TextEditor *editor);

    #endif
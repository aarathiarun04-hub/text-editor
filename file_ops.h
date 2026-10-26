/** openFile() - Load file content into editor
saveFile() - Write editor content to file
closeFile() - Clean up file resources **/
#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include "text_editor.h"

void openFile(TextEditor *editor,char *filename);
void saveFile(TextEditor *editor,char *filename);
void closeFile(TextEditor *editor);

#endif
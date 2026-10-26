# Text Editor

A console text editor written in C. The document is a **doubly linked list with
one node per line**, a cursor points at the current line and column, and every
change is pushed onto an undo/redo stack — the same core ideas as a real editor,
implemented from scratch.

## Features

- Insert and delete text at the cursor
- Move the cursor left / right / up / down and show its position
- **Copy, cut and paste** through an internal clipboard
- **Find** text and **replace** text
- **Open** a file into the editor and **save** the buffer back to disk
- **Undo / redo** — every action is recorded on a dynamic array stack with the
  operation, the text and the cursor position, so undo restores the cursor too
- Line and column tracking (`cursorLine`, `cursorPos`)

## Build & run

```sh
gcc -o editor *.c
./editor          # editor.exe on Windows
```

## Menu

```
1.Insert                     11.Show Cursor Position
2.Delete Character           12.Find Text
3.Copy                       13.Replace Text
4.Cut                        14.Open File
5.Paste                      15.Save File
6.Display                    16.Close Editor
7.Move Cursor Left           17.Undo
8.Move Cursor Right          18.Redo
9.Move Cursor Up             19.Exit
10.Move Cursor Down
```

`trial.txt` is a small file you can load with option **14** to try the editor.

## Project structure

| File | Purpose |
| --- | --- |
| `text_editor.h` | `Node` and `TextEditor` types (line list + cursor + clipboard) |
| `main.c` | Menu loop and command dispatch |
| `text_operation.c/h` | Insert / delete character, display, copy / cut / paste |
| `cursor_operation.c/h` | Cursor movement and position reporting |
| `display_search.c/h` | Find and replace |
| `file_ops.c/h` | Open, save and close files |
| `redo_undo.c/h` | Dynamic array stack, undo and redo |
| `trial.txt` | Sample file to open |

## Notes

- Input strings are held in fixed 100-character buffers, so very long paste
  operations should be split up.
- Remember to **Save File (15)** before exiting — closing the editor frees the
  buffer without writing it to disk.

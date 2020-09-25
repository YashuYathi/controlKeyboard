# controlKeyboard
A arduino library to detect and handle keyboard events.

The Folder contain an example program.So, Please refer it to understand and implement it in your program.
The key array size is of 100 and I only used it for UP,DOWN,LEFT and RIGHT arrow keys, W,S and SPACE keys as shown in the example.
I implemented it using Arduino DUE board(programming port) and HID keyboard connected through native port of the board.
As key pressed, it is updated to key_array and that array is used to detect key events.As I mentioned we can store upto 100 keys which are OEM keys. 

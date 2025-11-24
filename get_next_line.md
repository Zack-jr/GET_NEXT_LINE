# **PERSONAL NOTES - get_next_line**

## Introduction
- create a function that takes a file descriptor as an argument and returns the next line of a text file using an unknown buffer size.
- get_next_line() should be able to read an entire file after successive calls.

## KEY CONCEPTS LEARNED

### 1. FILE DESCRIPTORS 
- `What is a file descriptor?`
  - a file descriptor is an integer value used to reference a file in our code, they are usually ranged from 0 to 1024 in linux systems.
  - fd == 0 is the stdin (standard input) file descriptor, used to get user input mainly from the terminal.
  - fd == 1 is the stdout (standard output) file descriptor, taking the terminal as a reference to print something on it.
  - fd == 2 is the stderr (standard error) file descriptor, used as an output stream for errors.
  - fds from 3 to 1024 (linux systems) are the regular file descriptors, accessed using the *open* fonction.

- `read() function`
  - the read function is part of the unistd.h library.
  - read() takes 3 arguments, first the file descriptor we want to read from, then the buffer we want to store our data in, and lastly the buffer size in order to specify how many bytes we want to read at once with read()
  - read() returns a ssize_t (signed size_t) every call, which will be equal to the number of bytes we managed to read into our buffer, if there is an error, read() will return -1.

- `open() function`
  - the open function is part of the fcntl.h library.
  - it is used to open a file for either reading, writing, or both.
  - open() allows us to get a file descriptor for any file.
  - it takes a flag as an argument ex: O_RDWR, O_RDONLY...
  - once a file has been processed and does not need to be open anymore, use close() to close the file descriptor.

#### USEFUL KNOWLEDGE
- `static variables`
  - a static variable is essentialy a variable that will retain it's value after the function it's been used to reaches the main. This allows us to create a "stash" variable (or reserve variable) that will
  store the values of the characters that we passed to it.

## GET_NEXT_LINE() logic
- `get_next_line()`
    - the main function of this project, here we declare all of our variables, check for the input, malloc the buffer into the heap and importantly, check the stash(static char *) to see if it is empty before doing anything else.
    - from this function, we call loop() which will read every byte from the fd into buffer, to then pass it to the stash(that we malloced with ft_strdup or ft_strjoin)
    - then we use the find_newline() function to check for a '\n' character in our stash. If we find one, we must extract the line from the stash using extract_line(). That function  will return the wanted line as well as freeing the characters before the newline in our stash. We always pass stash as **stash to be able to change the adress of the first character.
    - Before returning the line we extracted, we should always free the buffer to avoid leaks.
- `get_next_line_utils.c`
    - this utils file contains the rest of the functions we use in our project such as: find_newline(), ft_strjoin(), ft_strdup(), ft_strncpy() and finally ft_strlen().
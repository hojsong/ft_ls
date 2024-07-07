# ft_ls
This guide will help you write a README.md file for a project that implements the ls command along with its options -a, -l, -r, -R, -t using C language. It will present a clear way to communicate the purpose and functionalities of your project, along with a brief description of the functions used. 😊

Project Overview
Purpose: To implement the ls command and its options -a, -l, -r, -R, -t in C, providing the functionality to list contents of the file system.
Features:
Basic ls: Lists the contents of a directory.
Option -a: Includes hidden files in the listing.
Option -l: Lists file details such as permissions, number of links, owner, group, size, and last modified date.
Option -r: Lists files in reverse order.
Option -R: Recursively lists subdirectories encountered.
Option -t: Lists files sorted by modification time.
Functions Used
File and Directory Handling: opendir, readdir, closedir, stat, lstat, readlink 7
User and Group Information: getpwuid, getgrgid
Time Related: time, ctime
Memory Management: malloc, free
Error Handling: perror, strerror
Program Termination: exit
This project aims to replicate the basic functionalities required for listing and managing file system contents. For a detailed explanation of the code structure and the functions used, please refer to the comments within the project's source code. If you have any feedback or questions about the project, feel free to open an issue. 🌟

This guide is based on the information about the functions and options used in the project implementation. While every effort has been made to ensure the accuracy of this guide, please be aware that errors may exist.
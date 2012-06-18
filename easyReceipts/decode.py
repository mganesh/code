#!/usr/bin/python
 
if __name__ == '__main__':
    f=open("./test.easy", "r")
    lines=f.read()
    for char in lines:
        if char.isalpha():
            print char,

#!/usr/bin/env python

# -*- coding: utf-8 -*-

import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox

file_path = ''

def refresh_filepath():
    global file_path
    file_path = file_entry.get()
    win.after(1000, refresh_filepath)

def but1_onclick():
    global file_path
    file_path = filedialog.askopenfilename(
        filetypes=(('Excel表格', '*.xlsx'), ('所有文件', '*.*')))
    file_entry.delete(0, tk.END)
    file_entry.insert(0, file_path)


win = tk.Tk()
win.title('xlsx转ics（哈深）')
win.geometry('800x600')
win.resizable(0, 0)

tk.Label(win, text='Excel文件位置：', font=(
    'Microsoft Yahei UI', 12)).place(x=10, y=15, anchor='nw')
file_entry = tk.Entry(win, font=(
    'Microsoft Yahei UI', 12))
tk.Button(win, text='  浏览  ', font=('Microsoft Yahei UI', 11), command=but1_onclick
          ).place(x=729, y=13, height=30, anchor='nw')

file_entry.place(x=130, y=16, width=588, anchor='nw')

win.after(1, refresh_filepath)
win.mainloop()

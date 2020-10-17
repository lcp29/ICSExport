
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


def btn1_onclick():
    global file_path
    file_path = filedialog.askopenfilename(
        filetypes=(('Excel表格', '*.xlsx'), ('所有文件', '*.*')))
    file_entry.delete(0, tk.END)
    file_entry.insert(0, file_path)


def btn2_onclick():
    return


win = tk.Tk()
win.title('xlsx转ics（哈深）')
win.geometry('800x600')
win.resizable(0, 0)

tk.Label(win, text='Excel文件位置：', font=(
    'Microsoft Yahei UI', 11)).place(x=10, y=15, anchor='nw')

tk.Label(win, text='VEVENT列表：', font=('Microsoft Yahei UI', 11)
         ).place(x=10, y=45, anchor='nw')

tk.Button(win, text='浏览', font=('Microsoft Yahei UI', 11), command=btn1_onclick
          ).place(x=729, y=13, width=60, height=30, anchor='nw')

tk.Button(win, text='开始转换', font=('Microsoft Yahei UI', 11),
          command=btn2_onclick).place(x=10, y=555, width=780, anchor='nw')

file_entry = tk.Entry(win, font=(
    'Microsoft Yahei UI', 11))

vlist = tk.Listbox(win)

file_entry.place(x=127, y=16, width=591, anchor='nw')
vlist.place(x=10, y=75, width=780, height=470, anchor='nw')

win.after(1, refresh_filepath)
win.mainloop()

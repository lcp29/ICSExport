
#!/usr/bin/env python

# -*- coding: utf-8 -*-

import tkinter as tk
from tkinter import filedialog
from tkinter import messagebox
import xlrd

file_path = ''
vevents = []
exist = False
gym_name = '大'
global workbook
global sheet


class vevent:
    summ = 'nil'
    desc = 'nil'
    loca = 'nil'
    week = 'nil'
    wcnt = 'nil'
    clas = 'nil'


def drawlist():
    vlist.delete(0, tk.END)
    for i in vevents:
        vlist.insert(tk.END, '课程名称：' + i.summ + ' 地点：' + i.loca + ' 任课老师：' +
                     i.desc + ' 周数：第' + i.week + '周，周' + i.wcnt + ' 节数：第' + i.clas + '节')


def updatelist():
    if exist == False:
        return
    vevents.clear()
    for c in range(1, 7):
        for r in range(3, 8):
            buf = sheet.cell_value(r, c)
            if buf.isspace() or buf == '':
                continue
            buf = buf.strip()
            a = 0  # 指向要读取的下一个字符的索引
            b = 0  # 指向下一个']'的索引
            while b != len(buf) - 1:
                v = vevent()
                # 读取SUMMARY
                v.summ = buf[a:buf.find('[', a)]
                # 循环读取剩余内容
                end = False  # 指示一轮读取是否结束
                while end == False:
                    a = buf.find('[', a) + 1
                    b = buf.find(']', a)
                    if(buf[a:b].startswith('T') or buf[a:b].startswith('G') or buf[a:b].startswith('H') or buf[a:b].startswith(gym_name)):
                        v.loca = buf[a:b]
                    elif(buf[a:b].endswith('周')):
                        v.week = buf[a:b-1]
                    elif(not buf[a:b].endswith('节')):
                        v.desc = buf[a:b]
                    if(b == len(buf) - 1):
                        end = True
                    elif(buf[b+1] == ','):
                        end = True
                        a = buf.find('[', b) + 1
                        b = a + 1
                v.wcnt = str(c)
                v.clas = str(r-2)
                vevents.append(v)
    for i in vevents:
        if i.summ.endswith('\n'):
            i.summ = i.summ[0:len(i.summ) - 1]


def openfile():
    global workbook
    global sheet
    global exist
    try:
        workbook = xlrd.open_workbook(file_path)
    except FileNotFoundError:
        exist = False
        return
    else:
        exist = True
        sheet = workbook.sheet_by_index(0)


def refresh_filepath():
    global file_path
    global gym_name
    file_path = file_entry.get()
    if gym_entry.get() != '':
        gym_name = gym_entry.get()
    openfile()
    updatelist()
    drawlist()


def btn1_onclick():
    global file_path
    file_path = filedialog.askopenfilename(
        filetypes=(('Excel表格', '*.xlsx'), ('所有文件', '*.*')))
    file_entry.delete(0, tk.END)
    file_entry.insert(0, file_path)


def btn2_onclick():
    refresh_filepath()
    ofile_path = file_path[0:file_path.rfind('.')] + '.tmp'
    ofile = open(ofile_path, 'w+')
    # 注意：这里的周日期是硬编码的，需要根据实际情况改动
    ofile.write('7-20201012\n6\n083000-101500\n103000-121500\n140000-154500\n160000-174500\n184500-203000\n204500-223000\n')
    ofile.write(str(len(vevents)) + '\n')
    for i in vevents:
        ofile.write(i.summ + '\n')
        ofile.write(i.desc + '\n')
        ofile.write(i.loca + '\n')
        ofile.write(i.week + '\n')
        ofile.write(i.wcnt + '\n')
        ofile.write(i.clas + '\n')


def about():
    about_win = tk.Toplevel()
    about_win.geometry("220x65")
    about_win.title('关于')
    win.resizable(0, 0)
    tk.Label(about_win, font=(
        'Microsoft Yahei UI', 11), text='哈深xlsx转ics小助手@0402').pack()
    tk.Button(about_win, font=(
        'Microsoft Yahei UI', 11), text='确定', command=about_win.destroy).pack()
    about_win.mainloop()


win = tk.Tk()
win.title('xlsx转ics（哈深）')
win.geometry('800x600')
win.resizable(0, 0)

tk.Label(win, text='Excel文件位置：', font=(
    'Microsoft Yahei UI', 11)).place(x=10, y=15, anchor='nw')

tk.Label(win, text='VEVENT列表：', font=('Microsoft Yahei UI', 11)
         ).place(x=10, y=45, anchor='nw')

tk.Label(win, text='体育上课地点的前几个字（必须与Excel文件中的相同）：', font=(
    'Microsoft Yahei UI', 11)).place(x=150, y=45, anchor='nw')

tk.Button(win, text='浏览', font=('Microsoft Yahei UI', 11), command=btn1_onclick
          ).place(x=729, y=13, width=60, height=30, anchor='nw')

tk.Button(win, text='开始转换', font=('Microsoft Yahei UI', 11),
          command=btn2_onclick).place(x=405, y=555, width=385, anchor='nw')

tk.Button(win, text='刷新', font=('Microsoft Yahei UI', 11),
          command=refresh_filepath).place(x=70, y=555, width=325, anchor='nw')

tk.Button(win, text='关于', font=('Microsoft Yahei UI', 11),
          command=about).place(x=10, y=555, width=50)

file_entry = tk.Entry(win, font=(
    'Microsoft Yahei UI', 11))

gym_entry = tk.Entry(win, font=(
    'Microsoft Yahei UI', 11))

vlist = tk.Listbox(win)

file_entry.place(x=127, y=16, width=591, anchor='nw')
gym_entry.place(x=535, y=46, width=254, anchor='nw')
vlist.place(x=10, y=75, width=780, height=470, anchor='nw')

win.mainloop()

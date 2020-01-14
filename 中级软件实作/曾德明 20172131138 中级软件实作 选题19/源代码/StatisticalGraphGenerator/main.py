import gloval as gl
import my_functions as mf
from db import dbmodel
from tkinter import *
from tkinter import ttk
from tkinter import scrolledtext        # 导入滚动文本框的模块
import tkinter
import tkinter.messagebox

# 主窗口
rootWindow = Tk()
# 控件
# 表名下拉框
tablename = StringVar()     # StringVar是Tk库内部定义的字符串变量类型，在这里用于管理部件上面的字符
com1 = ttk.Combobox(rootWindow, textvariable=tablename)
# 字段1下拉框
fieldname1 = StringVar()
fieldselect1 = ttk.Combobox(rootWindow, textvariable=fieldname1)
# 字段2下拉框
fieldname2 = StringVar()
fieldselect2 = ttk.Combobox(rootWindow, textvariable=fieldname2)
# 统计图类型下拉框
graphname = StringVar()
graphselect = ttk.Combobox(rootWindow, textvariable=graphname)
# 分析按钮和画图按钮
btn_analy = Button(rootWindow, text="分析数据", anchor="center", relief="raised") # 样式：居中凸起
btn_draw = Button(rootWindow, text="画图", anchor="center", relief="raised") # 样式：居中凸起
# 滚动文本框
scr = scrolledtext.ScrolledText(rootWindow, width=90, height=20,font=("隶书",10))  #滚动文本框（宽，高（这里的高应该是以行数为单位），字体样式）

def set_globel_vars():
    """添加需要的全局变量并设置初值"""
    gl.set_value('tables', [])      # 数据表名列表
    gl.set_value('groups', {})      # 分析数据函数使用的全局变量，用于存储x轴的数据
    gl.set_value('factors', {})     # 分析数据函数使用的全局变量，用于存储y轴的数据
    gl.set_value('model', None)     # 数据表模型


def software_init():
    """软件初始化"""
    gl._init()
    set_globel_vars()
    # 获取所有的数据表名，并存储到全局变量tables中
    tables = mf.get_all_table()
    gl.set_value('tables', tables)


def get_com1_valus(*args):
    """处理事件，即用户选定数据表事件，*args表示可变参数 """
    usingtable = com1.get()
    model = dbmodel.DBModel(usingtable)     # 当选定了数据表则根据数据表名来生成模型
    """
    result = model.findAll()
    datatext.delete('1.0', 'end')
    for v in result:
        datatext.insert('end', result)
        datatext.index('end', '\n')
    """
    if gl.get_value('model') is None:       # 如果还没保存模型，则直接添加全局变量
        gl.set_value('model', model)
    else:                                   # 如果已经添加了，则先消除原本的实例，再添加
        tmp = gl.get_value('model')
        del tmp
        gl.set_value('model', model)
    # 更改字段下拉框的可选项
    global fieldselect1
    global fieldselect2
    fieldselect1['value'] = tuple(model.get_fields())
    fieldselect2['value'] = tuple(model.get_fields())

def btn_analy_action(event):
    field1 = fieldselect1.get()
    field2 = fieldselect2.get()
    gl.set_value('field1', field1)
    gl.set_value('field2', field2)
    if field1 == '' or field2 == '' or field1 == '(还没选择数据库)' or field2 == '(还没选择数据库)':
        # 弹出对话框
        result = tkinter.messagebox.askquestion(title='warming', message='警告：你还没选择变量')
        # 返回值为：yes/no
        print(result)
    elif field1 == field2:
        # 弹出对话框
        result = tkinter.messagebox.askquestion(title='warming', message='警告：不能选择相同的变量')
        # 返回值为：yes/no
        print(result)
    else:
        model = gl.get_value('model')
        if mf.analy_data(field1, field2, model):
            # 弹出对话框
            result = tkinter.messagebox.askquestion(title='warming', message='提示：分析成功')
            # 显示二维表
            pcrosstab = gl.get_value('crosstab')
            pgroups = gl.get_value('groups')
            pfactors = gl.get_value('factors')
            #print(pgroups)
            #print(pfactors)
            #print(pcrosstab)
            xname = []
            for key in pgroups.keys():
                xname.append(key)
            scr.delete('1.0','end')
            scr.insert('end', '交叉表：' + '\n')
            for i in pfactors:
                scr.insert('end', i)
                scr.insert('end', '\t')
            scr.insert('end', '\n')
            x = 0
            for i in pcrosstab:
                for j in i:
                    scr.insert('end', j)
                    scr.insert('end', '\t')
                #scr.insert('end', i)
                scr.insert('end', xname[x])
                x += 1
                scr.insert('end', '\n')

        else:
            # 弹出对话框
            result = tkinter.messagebox.askquestion(title='warming', message='警告：分析失败')

def btn_draw_action(event):
    field1 = fieldselect1.get()
    field2 = fieldselect2.get()
    if field1 != gl.get_value('field1') or field2 != gl.get_value('field2'):
        result = tkinter.messagebox.askquestion(title='warming', message='警告：还没进行数据分析')
    else:
        type = graphselect.get()
        if type == '':
            # 弹出对话框
            result = tkinter.messagebox.askquestion(title='warming', message='警告：你还没选择类型')
            # 返回值为：yes/no
            print(result)
        else:
            mf.draw_graph(type)

def windows_init():
    """主窗口初始化"""
    # 软件变量初始化
    software_init()
    # 引用主窗口
    global rootWindow
    # 窗口大小
    rootWindow.geometry('800x600')
    # 窗口标题
    rootWindow.title('统计图表生成软件')
    # 设置三个下拉框
    label_tablename = Label(rootWindow, text="数据表名称:")   # 添加一个标签
    label_tablename.place(relx=0.1, rely=0.1)
    global com1
    com1.place(relx=0.1, rely=0.15, relwidth=0.2)
    value = tuple(gl.get_value('tables'))
    com1["value"] = value   # 设置下拉数据
    com1.bind("<<ComboboxSelected>>", get_com1_valus)  # 绑定事件,(下拉列表框被选中时，绑定go()函数)

    label_fieldx = Label(rootWindow, text="x轴的字段:")
    label_fieldx.place(relx=0.4, rely=0.1)
    global fieldselect1
    fieldselect1.place(relx=0.4, rely=0.15)
    fieldvalue1 = ("(还没选择数据库)")
    fieldselect1['value'] = fieldvalue1

    label_fieldy = Label(rootWindow, text="y轴的字段:")
    label_fieldy.place(relx=0.7, rely=0.1)
    global fieldselect2
    fieldselect2.place(relx=0.7, rely=0.15)
    fieldvalue2 = ("(还没选择数据库)")
    fieldselect2['value'] = fieldvalue2

    label_graph = Label(rootWindow, text="请选择图像类型:")
    label_graph.place(relx=0.4, rely=0.2)
    global graphselect
    graphselect.place(relx=0.4, rely=0.25)
    graphvalue = ("柱状图", "饼状图", "折线图")   # "条形图"
    graphselect['value'] = graphvalue

    global btn_analy
    btn_analy.place(relx=0.1, rely=0.2)
    btn_analy.bind("<Button-1>", btn_analy_action) # 绑定动作函数<Button-1>为鼠标左击事件

    global btn_draw
    btn_draw.place(relx=0.4, rely=0.3)
    btn_draw.bind("<Button-1>", btn_draw_action)  # 绑定动作函数

    global scr
    scr.place(relx=0.1, rely=0.4)


if __name__ == '__main__':
    windows_init()
    rootWindow.mainloop()


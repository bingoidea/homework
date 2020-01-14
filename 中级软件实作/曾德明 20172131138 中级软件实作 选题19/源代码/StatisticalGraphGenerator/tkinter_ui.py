import gloval as gl
import my_functions as mf
from db import dbmodel
from tkinter import *
from tkinter import ttk
'''
rootWindow = Tk()
# 控件
tablename = StringVar()  # StringVar是Tk库内部定义的字符串变量类型，在这里用于管理部件上面的字符
com1 = ttk.Combobox(rootWindow, textvariable=tablename)
fieldname1 = StringVar()
fieldselect1 = ttk.Combobox(rootWindow, textvariable=fieldname1)
fieldname2 = StringVar()
fieldselect2 = ttk.Combobox(rootWindow, textvariable=fieldname2)
btn_analy = Button(rootWindow, text="分析数据", anchor="center", relief="raised")  # 样式：居中凸起

class App:
    """App类"""
    
    # 主窗口
    rootWindow = Tk()
    # 控件
    tablename = StringVar()  # StringVar是Tk库内部定义的字符串变量类型，在这里用于管理部件上面的字符
    com1 = ttk.Combobox(rootWindow, textvariable=tablename)
    fieldname1 = StringVar()
    fieldselect1 = ttk.Combobox(rootWindow, textvariable=fieldname1)
    fieldname2 = StringVar()
    fieldselect2 = ttk.Combobox(rootWindow, textvariable=fieldname2)
    btn_analy = Button(rootWindow, text="分析数据", anchor="center", relief="raised")  # 样式：居中凸起
    
    

    def set_globel_vars(self):
        """添加需要的全局变量并设置初值(私有函数)"""
        gl.set_value('tables', [])  # 数据表名列表
        gl.set_value('groups', {})  # 分析数据函数使用的全局变量，用于存储x轴的数据
        gl.set_value('factors', {})  # 分析数据函数使用的全局变量，用于存储y轴的数据
        gl.set_value('model', None)  # 数据表模型

    def software_init(self):
        """软件初始化(私有函数)"""
        gl._init()
        self.set_globel_vars()
        # 获取所有的数据表名，并存储到全局变量tables中
        tables = mf.get_all_table()
        gl.set_value('tables', tables)

    def window_init(self):
        """初始化窗口"""
        # 软件初始化
        self.software_init()
        # 窗口大小
        self.rootWindow.geometry('800x600')
        # 窗口标题
        self.rootWindow.title('统计图表生成软件')
        # 设置三个下拉框
        # 第一个
        label_tablename = Label(self.rootWindow, text="数据表名称:")  # 添加一个标签
        label_tablename.place(relx=0.1, rely=0.1)
        self.com1.place(relx=0.1, rely=0.15, relwidth=0.2)
        value = tuple(gl.get_value('tables'))
        self.com1["value"] = value  # 设置下拉数据
        self.com1.bind("<<ComboboxSelected>>", self.get_com1_valus())  # 绑定事件,(下拉列表框被选中时，绑定get_com1_valus()函数)
        # 第二个
        label_fieldx = Label(self.rootWindow, text="x轴的字段:")
        label_fieldx.place(relx=0.4, rely=0.1)
        self.fieldselect1.place(relx=0.4, rely=0.15)
        fieldvalue1 = ("(还没选择数据库)")
        self.fieldselect1['value'] = fieldvalue1
        # 第三个
        label_fieldy = Label(self.rootWindow, text="y轴的字段:")
        label_fieldy.place(relx=0.7, rely=0.1)
        self.fieldselect2.place(relx=0.7, rely=0.15)
        fieldvalue2 = ("(还没选择数据库)")
        self.fieldselect2['value'] = fieldvalue2

        self.btn_analy.place(relx=0.1, rely=0.2)

    def get_com1_valus(self):
        """处理事件，即用户选定数据表事件，*args表示可变参数 """
        usingtable = self.com1.get()
        print(usingtable)
        model = dbmodel.DBModel(usingtable)  # 当选定了数据表则根据数据表名来生成模型
        if gl.get_value('model') == None:  # 如果还没保存模型，则直接添加全局变量
            gl.set_value('model', model)
        else:  # 如果已经添加了，则先消除原本的实例，再添加
            tmp = gl.get_value('model')
            del tmp
            gl.set_value('model', model)
        # 更改字段下拉框的可选项
        self.fieldselect1['value'] = tuple(model.get_fields())
        self.fieldselect2['value'] = tuple(model.get_fields())

    def btn_analy_action(self):
        """分析按钮的功能"""

    def run(self):
        """运行app"""
        self.rootWindow.mainloop()



    global btn_analy
    btn_analy.place(relx=0.1, rely=0.2)


def run():
    windows_init()
    rootWindow.mainloop()

run()

'''
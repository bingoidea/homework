# 软件主要函数
import random
import pymysql
from db import config
from db import dbmodel
import matplotlib.pyplot as plt
import matplotlib
from matplotlib.gridspec import GridSpec
import numpy as np
import gloval as gl
#如遇中文显示问题可加入以下代码
from pylab import mpl
mpl.rcParams['font.sans-serif'] = ['SimHei'] # 指定默认字体
mpl.rcParams['axes.unicode_minus'] = False # 解决保存图像是负号'-'显示为方块的问题

def get_all_table():
    """获取指定数据库的所有表名"""
    try:
        temp = []
        conn = pymysql.connect(host=config.host, user=config.user, password=config.password, db=config.dbname,charset="utf8")
        cur = conn.cursor(pymysql.cursors.DictCursor)
        cur.execute('SHOW TABLES')
        dlist = cur.fetchall()
        for v in dlist:
            temp.append(v['Tables_in_%s' % (config.dbname)])
    except Exception as err:
        print("获取失败，原因：%s" % err)
    finally:
        conn.commit()
        conn.close()
    return temp

def cut(field):
    """年龄分组"""
    model = gl.get_value('model')
    result = model.findAll()
    min = max = result[0]['age']
    # 获取年龄的最大值和最小值
    for v in result:
        if v['age'] > max:
            max = v['age']
        if v['age'] < min:
            min = v['age']
    groups = {}
    ages_valus = {}
    cnt = 10    # 按10进行分组
    first = min
    i = 0
    while first != max:
        # 以十为间隔分组，同时给表格数据的年龄做索引
        if first+cnt < max:
            groupname = '[' + str(first) + '-' + str(first+cnt) + ')'
            # 在该范围内的所有年龄都标为与组名相同的键值
            for v in result:
                if first <= v['age'] < first+cnt:
                    ages_valus[v['age']] = i
            first += cnt
            groups[groupname] = i
        else:
            groupname = '[' + str(first) + '-' + str(max) + ']'
            for v in result:
                if first <= v['age'] <= max:
                    ages_valus[v['age']] = i
            first = max
            groups[groupname] = i
        i += 1
    gl.set_value('ages_valus', ages_valus) # 添加全局变量
    return groups

def analy_data(field1, field2, model):
    """进行数据表的分析"""
    len1 = 0
    len2 = 0
    groups = {}
    factors = {}
    crosstab = []
    percrosstab = []
    result = model.findAll()
    if field1 == 'age':
        i = 0
        groups = cut(field1)
        ages_valus = gl.get_value('ages_valus')
        for v in result:
            if v[field2] not in factors:
                factors[v[field2]] = i
                i += 1
        # 建立二维交叉表
        len1 = len(groups)
        len2 = len(factors)
        for i in range(len1):
            crosstab.append([0]*len2)
        for v in result:
            # 先获取年龄的值，再根据年龄的值获取年龄的下标
            crosstab[ages_valus[v[field1]]][factors[v[field2]]] += 1
        # 建立频率二维表
        for i in range(len1):
            percrosstab.append([0]*len2)
        sum = []
        sum.clear()
        for i in range(len1):
            n = 0
            for j in range(len2):
                n += crosstab[i][j]
            sum.append(n)
        # print('sum')
        # print(sum)
        for i in range(len1):
            for j in range(len2):
                percrosstab[i][j] = crosstab[i][j] / sum[i]
    elif field2 == 'age':
        i = 0
        factors = cut(field2)
        ages_valus = gl.get_value('ages_valus')
        for v in result:
            if v[field1] not in groups:
                groups[v[field1]] = i
                i += 1
        # 建立二维交叉表
        len1 = len(groups)
        len2 = len(factors)
        for i in range(len1):
            crosstab.append([0] * len2)
        for v in result:
            # 先获取年龄的值，再根据年龄的值获取下标值
            crosstab[groups[v[field1]]][ages_valus[v[field2]]] += 1
        # 建立频率交叉表
        for i in range(len1):
            percrosstab.append([0]*len2)
        sum = []
        sum.clear()
        for i in range(len1):
            n = 0
            for j in range(len2):
                n += crosstab[i][j]
            sum.append(n)
        # print('sum')
        # print(sum)
        for i in range(len1):
            for j in range(len2):
                percrosstab[i][j] = crosstab[i][j] / sum[i]
    else:
        i = 0
        j = 0
        for v in result:
            # 对x轴元素进行分组编号
            if v[field1] not in groups:
                groups[v[field1]] = i
                i = i+1
            # 对y轴元素进行分组编号
            if v[field2] not in factors:
                factors[v[field2]] = j
                j = j+1
        # 建立二维交叉表
        len1 = len(groups)
        len2 = len(factors)
        for i in range(len1):
            crosstab.append([0]*len2)
        # 根据数据生成二维交叉表
        for v in result:
            crosstab[groups[v[field1]]][factors[v[field2]]] += 1
        # 生成概率二维表
        for i in range(len1):
            percrosstab.append([0]*len2)
        sum = []
        sum.clear()
        for i in range(len1):
            n = 0
            for j in range(len2):
                n += crosstab[i][j]
            sum.append(n)
        # print('sum')
        # print(sum)
        for i in range(len1):
            for j in range(len2):
                percrosstab[i][j] = crosstab[i][j] / sum[i]
    # 存储全局变量
    gl.set_value('groups', groups)
    gl.set_value('factors', factors)
    gl.set_value('len1', len1)
    gl.set_value('len2', len2)
    gl.set_value('crosstab', crosstab)
    gl.set_value('percrosstab', percrosstab)
    if len(crosstab) == len1:
        return True
    else:
        return False

def draw_graph(type):
    """根据交叉表进行画图"""
    len1 = gl.get_value('len1')
    len2 = gl.get_value('len2')
    groups = gl.get_value('groups')
    factors = gl.get_value('factors')
    crosstab = gl.get_value('crosstab')
    percrosstab = gl.get_value('percrosstab')
    if type == '柱状图':
        fig = plt.figure()
        # ax = plt.subplot(111)
        # 获取x轴和y轴的名称
        key_labelx = []
        for key in groups.keys():
            key_labelx.append(key)
        key_labely = []
        for key in factors.keys():
            key_labely.append(key)
        # x轴，从1开始
        ind = range(1, len1 + 1)
        # 更改x轴名字
        xname = tuple(key_labelx)
        width = 0.4    # 柱子的宽度
        d = [0] * len1 # 存储下一次画图的开始位置
        drawlist = []
        for i in range(len2):
            # 堆叠作图
            drawlist.clear()
            for j in range(len1):
                drawlist.append(crosstab[j][i])     # 按照列进行绘图，一共有len(factors)列
            # 绘图 x轴， height 高度, 默认：color="blue", width=0.8
            #p = plt.bar(ind, drawlist, width, bottom=d, label=key_labely[i])
            plt.bar(ind, drawlist, width, bottom=d, label=key_labely[i])
            for j in range(len1):
                d[j] = d[j] + drawlist[j]     # 使用累加确定下一次作图的位置（0.1为柱状图间隔）
            # print(drawlist)         # 测试，print出每列数据
            """
            # 添加数据标签
            for a, b in zip(ind, d):
                plt.text(a, b + 0.05, '%.0f' % b, ha='center', va='bottom', fontsize=10)
            """
        title = '出行方式：' + str(gl.get_value('field1')) + '和' + str(gl.get_value('field2')) + '柱状图'
        plt.title(title)
        plt.xlabel(gl.get_value('field1'))
        plt.ylabel(gl.get_value('field2'))
        plt.xticks(ind, xname)      # 更改x轴名称
        fig.subplots_adjust(right=0.75) # 子图右侧位置
        plt.legend(bbox_to_anchor=(1.05, 0), loc=3, borderaxespad=0)   # 添加图例
        plt.savefig("./t1.svg")
        plt.show()
    elif type == '饼状图':
        fig = plt.figure(figsize=(15,10))
        # 获取x轴的元素
        key_labelx = []
        for key in groups.keys():
            key_labelx.append(key)
        # 获取y的标志
        key_labely = []
        for key in factors.keys():
            key_labely.append(key)
        if len1%2 == 0:
            #r = c = len1 / 2
            r = c = len1
        else:
            r = int((len1+1)/2 - 1)
            c = int((len1+1)/2)
        #r = c = len1
        # 生成一个r*c的网格
        grids = GridSpec(r, c)
        # 突出第一个扇形
        exp = [0]*len2
        exp[0] = 0.1
        # 用于定位
        x = y = 0
        for i in range(len1):
            plt.subplot(grids[x, y], aspect=1)
            fraces = crosstab[i]  # 返回的是第i行数据
            # print(fraces)   # 测试数据
            plt.pie(x=fraces, labels=key_labely, explode=exp, shadow=True, autopct='%.0f%%')  # x是绘图数据，labels用于生成图例
            # 添加标题
            title = '出行方式 ' + str(key_labelx[i]) + ' 饼状图'
            plt.title(title)
            fig.subplots_adjust(right=0.75)  # 子图右侧位置
            #plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0)  # 添加图例
            y = y + 1
            if y >= c:
                x = x + 1
                y = y%c
            """
            # 对每个x进行画图，有多少个x就能做多少个饼状图
            fraces = crosstab[i] # 返回的是第i行数据
            print(fraces)
            plt.axes(aspect=1)
            # plt.subplot(len1/2, len1/2, i + 1)
            plt.pie(x=fraces, labels=key_labely, explode=exp, shadow=True, autopct='%.0f%%') # x是绘图数据，labels用于生成图例
            # 添加标题
            title = str(key_labelx[i]) + '饼状图'
            plt.title(title)
            fig.subplots_adjust(right=0.75)  # 子图右侧位置
            plt.legend(bbox_to_anchor=(1.05, 0), loc=3, borderaxespad=0)  # 添加图例
            plt.show()
            """
        plt.savefig("./t2.svg")
        plt.show()
    elif type == '折线图' :
        fig = plt.figure()
        ax = plt.subplot(111)
        # 获取x轴和y轴的元素和值
        key_labelx = []
        value_x = []
        key_labely = []
        value_y = []
        for key in groups.keys():
            key_labelx.append(key)
            value_x.append(groups[key]+1)
        for key in factors.keys():
            key_labely.append(key)
        # x轴从1开始
        ind = range(1, len1+1)
        # 更改x的名字
        xname = tuple(key_labelx)
        # print(key_labelx)
        # print(key_labely)
        # print(value_x)
        markets = ['s', '.', 'v', '*', 'X'] # 不同的标志
        for i in range(len2):
            # 按列作图
            value_y.clear()
            for j in range(len1):
                value_y.append(crosstab[j][i])
            #plt.plot(value_x, value_y, marker='o', label=key_labely[i]) # market为显示点
            ax.plot(value_x, value_y, marker=markets[random.randint(0, len(markets)-1)], label=key_labely[i])  # market为显示点
            # 设置数字标签
            """
            for a, b in zip(value_x, value_y):
                plt.text(a, b, b, ha='center', va='bottom', fontsize=10)
            """
            # print(value_y)
        # 以矢量图保存，这样放大不会失真，不会模糊
        title = '出行方式：' + str(gl.get_value('field1')) + '和' + str(gl.get_value('field2')) + '折线图'
        plt.title(title)
        plt.xlabel(gl.get_value('field1'))
        plt.ylabel(gl.get_value('field2'))
        plt.xticks(ind, xname)
        fig.subplots_adjust(right=0.75)  # 调整子图位置subplots_adjust()函数的作用是调整子图布局，它包含6个参数，其中4个参数left, right, bottom, top的作用是分别调整子图的左部，右部，底部，顶部的位置
        # plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0) 右侧上部 bbox_to_anchor=(0.4, -0.1), loc=2, borderaxespad=0 底侧
        plt.legend(bbox_to_anchor=(1.05, 0), loc=3, borderaxespad=0) # bbox_to_anchor被赋予的二元组中，num1用于控制legend的左右移动，值越大越向右边移动，num2用于控制legend的上下移动
        plt.savefig("./t3.svg")
        plt.show()
    else:
        fig = plt.figure()
        # ax = plt.subplot(111)
        # 获取x轴和y轴的名称
        key_labelx = []
        for key in groups.keys():
            key_labelx.append(key)
        key_labely = []
        for key in factors.keys():
            key_labely.append(key)
        # x轴，从1开始
        ind = range(1, len1 + 1)
        # 更改x轴名字
        xname = tuple(key_labelx)
        width = 0.4  # 柱子的宽度
        d = [0] * len1  # 存储下一次画图的开始位置
        drawlist = []
        for i in range(len2):
            # 堆叠作图
            drawlist.clear()
            for j in range(len1):
                drawlist.append(crosstab[j][i])  # 按照列进行绘图，一共有len(factors)列
            p = plt.barh(ind, drawlist, width, left=d, label=key_labely[i])

            for j in range(len1):
                d[j] += drawlist[j]  # 使用累加确定下一次作图的位置
            # print(drawlist)  # 测试，print出每列数据
        title = str(gl.get_value('field1')) + '和' + str(gl.get_value('field2')) + '条形图'
        plt.title(title)
        plt.yticks(ind, xname)  # 更改y轴名称
        fig.subplots_adjust(right=0.75)  # 子图右侧位置
        plt.legend(bbox_to_anchor=(1.05, 0), loc=3, borderaxespad=0)  # 添加图例
        plt.savefig("./t4.svg")
        plt.show()

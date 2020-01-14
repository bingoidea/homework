#-*-coding:utf-8-*-
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec


label = [u"90分以上",u"80到90",u"70到80",u"60到70",u"60分以下"]
fractions = [8,22,20,34.5,15.5]
explode = (0.3,0,0,0,0)

#生成一个3*3的网格
grids = GridSpec(3, 3)

#设置画布大小
plt.figure(figsize=(15, 10))

for i in range(3):
    for j in range(3):
        plt.subplot(grids[i, j], aspect=1)
        plt.pie(fractions, labels=label, autopct='%1.1f%%', shadow=True)
        plt.title("shadow")
        plt.legend()

plt.show()

'''
#定位到第一个网格
plt.subplot(grids[0, 0], aspect=1)

# autopct就是设置自动生成的百分比的输出格式
plt.pie(fractions, labels=label, autopct='%1.1f%%', shadow=True)
plt.title("shadow")

# 定位到第一行第二个
plt.subplot(grids[0, 1], aspect=1)

# startangle是这种第一个与x的角度
plt.pie(fractions, explode=explode, labels=label, autopct='%.0f%%',startangle=45)
plt.title("explode,startangle=45")

plt.subplot(grids[0, 2], aspect=1)
patches, texts, autotexts = plt.pie(fractions, labels=label,autopct='%.0f%%', radius=0.5)
for t in texts:
    t.set_size('smaller')
plt.title("radius=0.5,texts smaller")


plt.subplot(grids[1, 0], aspect=1)
# labeldistance影响的是标签离圆心的距离
patches, texts, autotexts = plt.pie(fractions, labels=label,autopct='%.0f%%',labeldistance=1.0)
for t in autotexts:
    t.set_size('x-small')
plt.title("labeldistance=1.0,autotexts x-smaller")

plt.subplot(grids[1, 1], aspect=1)
# pctdistance影响的是百分比离圆心的距离
patches, texts, autotexts = plt.pie(fractions, labels=label,autopct='%.0f%%',pctdistance=1.0)
for t in autotexts:
    t.set_color('y')
plt.title("pctdistance=1.0,autotexts color y")

plt.subplot(grids[1, 2], aspect=1)
plt.pie(fractions, labels=label,autopct='%.0f%%',rotatelabels=True)
plt.title("rotatelabels=True")


plt.subplot(grids[2, 0], aspect=1)
# counterclock设置的是顺时针填充还是逆时针填充
plt.pie(fractions, labels=label,autopct='%.0f%%',wedgeprops={'linewidth': 10},counterclock=False)
plt.title("wedgeprops,counterclock=False")

plt.subplot(grids[2, 1], aspect=1)
# frame设置是否画坐标轴
plt.pie(fractions, labels=label,autopct='%.0f%%',frame=True,radius=0.5)
plt.title("frame=True")


plt.subplot(grids[2, 2], aspect=1)
patches, texts, autotexts = plt.pie(fractions, labels=label,autopct='%.0f%%',center=(0.5,0.5),frame=True,radius=0.5)
plt.title("center=(0.5,0.5),frame=True,radius=0.5")

# figure = plt.gcf()
# figure.set_size_inches(18.5, 10.5)
# figure.savefig("pie.png")
# plt.savefig("pie.png")
plt.show()

"""
#绘制饼图

plt.pie(x=data, #绘制数据

labels=labels,#添加编程语言标签

explode=explode,#突出显示Python

colors=colors, #设置自定义填充色

autopct='%.3f%%',#设置百分比的格式,保留3位小数

pctdistance=0.8, #设置百分比标签和圆心的距离

labeldistance=1.0,#设置标签和圆心的距离

startangle=180,#设置饼图的初始角度

center=(4,4),#设置饼图的圆心(相当于X轴和Y轴的范围)

radius=3.8,#设置饼图的半径(相当于X轴和Y轴的范围)

counterclock= False,#是否为逆时针方向,False表示顺时针方向

wedgeprops= {'linewidth':1,'edgecolor':'green'},#设置饼图内外边界的属性值

textprops= {'fontsize':12,'color':'black','fontproperties':my_font},#设置文本标签的属性值

frame=1) #是否显示饼图的圆圈,1为显示

'''
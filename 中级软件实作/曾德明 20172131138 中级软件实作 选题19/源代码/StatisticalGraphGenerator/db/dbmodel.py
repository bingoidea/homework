import pymysql
from db import config

class DBModel:
    """单表信息操作类"""
    table_name = None   # 数据表名
    link = None         # 数据库连接对象
    cursor = None       # 游标对象
    pk = 'id'           # 主键字段名
    fields = []         # 表的所有字段名

    def __init__(self,tablename,config=config):
        """构造类方法，通过表名初始化，通过config获取基本信息"""
        try:
            # 表名
            self.table_name = tablename
            # 初始化字段名列表
            self.fields.clear()
            # 连接信息
            self.link = pymysql.connect(host = config.host, user = config.user, password = config.password, db = config.dbname, charset = "utf8")
            # 使用cursor()方法创建一个游标对象cursor，参数pymysql.cursors.DictCursor让查询结果元素以字典数据格式返回，默认是列表
            self.cursor = self.link.cursor(pymysql.cursors.DictCursor)
            # 调用内部方法，加载当前表的字段信息
            self.__loadFields()
        except Exception as err:
            print("Model初始化报错，原因：%s" % err)

    def __loadFields(self):
        """加载当前表的字段信息,内部私有方法"""
        # sql
        sql = "SHOW COLUMNS FROM %s" % (self.table_name)
        # 执行sql
        self.cursor.execute(sql)
        # 获取所有记录，返回的是字典列表，每个元素类似这样：{'Field': 'id', 'Type': 'int(11)', 'Null': 'NO', 'Key': 'PRI', 'Default': None, 'Extra': 'auto_increment'}
        dlist = self.cursor.fetchall()
        # print(dlist)
        # 遍历所有字段信息
        for v in dlist:
            # 收集每个字段名称
            self.fields.append(v['Field'])
            # 判断并收集表的主键名称
            if v['Key'] == 'PRI':
                self.pk = v['Field']

    def get_table_name(self):
        return self.table_name

    def get_fields(self):
        return self.fields

    def findAll(self):
        """获取当前表的所有信息，没有信息返回空列表[]"""
        try:
            sql = "select * from %s" % (self.table_name)
            self.cursor.execute(sql)
            return self.cursor.fetchall()
        except Exception as err:
            print("SQL查询执行错误，原因：%s" % err)
            return []

    def find(self, id):
        """获取指定主键值的当条信息，没有返回None"""
        try:
            sql = "select * from %s where %s='%s'" % (self.table_name, self.pk, id)
            self.cursor.execute(sql)
            return self.cursor.fetchone()
        except Exception as err:
            print("SQL查询执行错误，原因：%s" % err)
            return None

    def select(self, where=[], order=None, limit=None):
        '''获取当前表的所有信息，没有信息返回空列表[]'''
        try:
            sql = "select * from %s " % (self.table_name)
            # 判断并封装where搜索条件
            if isinstance(where, list) and len(where) > 0:
                sql += " where " + " and ".join(where)
            # 判断并封装order排序条件
            if order is not None:
                sql += " order by " + order
            # 判断并封装limit条件
            if limit is not None:
                sql += " limit " + str(limit)
            print(sql)
            self.cursor.execute(sql)
            return self.cursor.fetchall()
        except Exception as err:
            print("SQL查询执行错误，原因：%+s" % err)
            return []

    def save(self, data={}):
        ''' 添加数据方法，通过字典参数data传递要添加的信息，并实现添加操作'''
        try:
            # 组装sql语句
            keys = []
            values = []
            for k, v in data.items():
                if k in self.fields:
                    keys.append(k)
                    values.append(v)
            sql = "insert into %s(%s) values(%s)" % (self.table_name, ','.join(keys), ','.join(['%s'] * len(values)))
            # print(sql)
            # 指定参数，并执行sql添加
            self.cursor.execute(sql, tuple(values))
            # 事务提交
            self.link.commit()
            # 获取并返回最新自增ID
            return self.cursor.lastrowid
        except Exception as err:
            print("SQL添加执行错误，原因：%s" % err)
            return 0

    def update(self, data={}):
        '''修改方法，通过字典参数data，传递要修改信息，并完成修改操作'''
        try:
            # 组装sql语句
            values = []
            for k, v in data.items():
                if (k in self.fields) and (k != self.pk):
                    values.append("%s='%s'" % (k, v))
            sql = "update %s set %s where %s='%s'" % (self.table_name, ','.join(values), self.pk, data.get(self.pk))
            print(sql)
            # 指定参数，并执行修改sql
            self.cursor.execute(sql)
            # 事务提交
            self.link.commit()
            # 返回数据条数或影响行数
            return self.cursor.rowcount
        except Exception as err:
            print("SQL修改执行错误，原因：%s" % err)
            return 0

    def delete(self, id=0):
        '''接收参数值id并执行删除对应的数据信息'''
        try:
            # 组装sql语句
            sql = "delete from %s where %s='%s'" % (self.table_name, self.pk, id)
            print(sql)
            # 指定参数，并执行修改sql
            self.cursor.execute(sql)
            # 事务提交
            self.link.commit()
            # 返回数据条数或影响行数
            return self.cursor.rowcount
        except Exception as err:
            print("SQL修改执行错误，原因：%s" % err)
            return 0

    def __del__(self):
        # 关闭游标对象
        if self.cursor != None:
            self.cursor.close()
        # 关闭数据库连接
        if self.link != None:
            self.link.close()




# 全局变量管理模块(global关键字仅限于在一个py文件中调用全局变量)
from db import dbmodel

def _init():
    """使用键值对存储全局变量"""
    global _global_dict
    _global_dict = {}

def set_value(name, value):
    """设置全局变量"""
    _global_dict[name] = value

def get_value(name, defValue=None):
    """获取全局变量，如果没有则返回None"""
    try:
        return _global_dict[name]
    except KeyError:
        return defValue
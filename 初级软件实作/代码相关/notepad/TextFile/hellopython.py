'''
程序用于获取html网页信息
'''
import requests

#模拟浏览器的header(Mozilla/5.0是常用的浏览器访问头)
BrowserHead = {'user-agent':'Mozilla/5.0'}

#获得HTML网页内容
def getHTMLtext(url):
	'''该函数用于获取网页文本，用try-catch语句来检测获取异常'''
	try:
		r = requests.get(url, headers=BrowserHead, timeout=30)
		r.raise_for_status()               #如果状态不是200，则产生HTTPError异常
		r.encoding = r.apparent_encoding   #把编码设置为网页文本的编码
		return r.text[:1000]               #text返回的是处理过的Unicode型的数据(可用切片的方式返回一部分内容)
	except:
		return "产生异常"

#主函数(__是双下划线)
if __name__ == "__main__":
	url = "https://item.jd.com/2766632.html"   #随意更换商品网址
	print(getHTMLtext(url))

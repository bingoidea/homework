'''
�������ڻ�ȡhtml��ҳ��Ϣ
'''
import requests

#ģ���������header(Mozilla/5.0�ǳ��õ����������ͷ)
BrowserHead = {'user-agent':'Mozilla/5.0'}

#���HTML��ҳ����
def getHTMLtext(url):
	'''�ú������ڻ�ȡ��ҳ�ı�����try-catch���������ȡ�쳣'''
	try:
		r = requests.get(url, headers=BrowserHead, timeout=30)
		r.raise_for_status()               #���״̬����200�������HTTPError�쳣
		r.encoding = r.apparent_encoding   #�ѱ�������Ϊ��ҳ�ı��ı���
		return r.text[:1000]               #text���ص��Ǵ������Unicode�͵�����(������Ƭ�ķ�ʽ����һ��������)
	except:
		return "�����쳣"

#������(__��˫�»���)
if __name__ == "__main__":
	url = "https://item.jd.com/2766632.html"   #���������Ʒ��ַ
	print(getHTMLtext(url))

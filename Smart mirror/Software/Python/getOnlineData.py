import requests

class GetOnlineData(object):
		
	def getDateTime(self):
		r = requests.get('http://just-the-time.appspot.com/')
		dateTime = r.text
		dateTimeList = dateTime.split(" ")
		date = dateTimeList[0]
		time = dateTimeList[1]
		timeList = time.split(":")
		hours = int(timeList[0])+2
		time = str(hours) + ":" + timeList[1]
		return time,date

	def getNews(self):
		r = requests.get('https://newsapi.org/v2/top-headlines?'
				'country=us&'
       				'apiKey=4773294fbbc34ae492d43e2dce858537')
		data = r.json()
		print ("Author: " + data[u'articles'][1][u'author'])
		print ("Title: " + data[u'articles'][1][u'title'])
		print ("Desctiption: " + data[u'articles'][1][u'description'])

	def getWeather(self):
		r = requests.get('http://api.openweathermap.org/data/2.5/forecast?'
				'id=360630&APPID=a86c507aba6a3322866ab2cdfa1271fb')
		data = r.json()
		temp = int(data[u'list'][0][u'main'][u'temp'])
		temp /= 10
		return str(temp)


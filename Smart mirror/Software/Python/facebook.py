import facebook

class handleFacebook(object):
		
	def __init__():
		

	def uploadPost(self):
		r = requests.get('http://just-the-time.appspot.com/')
		dateTime = r.text
		dateTimeList = dateTime.split(" ")
		date = dateTimeList[0]
		time = dateTimeList[1]
		timeList = time.split(":")
		hours = int(timeList[0])+2
		time = str(hours) + ":" + timeList[1]
		return time,date



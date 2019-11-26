#!/usr/bin/env python

import time
from qt_connector import QtConnector
from getOnlineData import GetOnlineData

def Main():
    	connector = QtConnector()  # to start a connection with qt app
	onlineData = GetOnlineData()
		
	dateTime = onlineData.getDateTime()
    	connector.set_qLabel("timeLabel" , dateTime[0]) #set the text of qline the function accept string
	#time.sleep(2)
	connector.set_qLabel("dateLabel" , dateTime[1]) #set the text of qline the function accept string
	#time.sleep(2)

	weather = onlineData.getWeather()
	connector.set_qLabel("tempLabel" , weather + " C") #set the text of qline the function accept string
	#time.sleep(2)


if __name__ == "__main__":
    Main()

import socket
import sys

class QtConnector(object):
    def __init__(self , TCP_IP="127.0.0.1" , TCP_PORT=10000 ):
        '''
        constractor that accept the following prams to instantiate a connection with qt_application
        :param TCP_IP: "127.0.0.1" for local connection
        :param TCP_PORT:10000 configured in qt app
        :return the app will closed if the qt-app not active
        '''
        super(QtConnector,self).__init__()
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.is_connected = False
        try:
            self.client.connect((TCP_IP, TCP_PORT))
            self.is_connected = True
        except socket.error:
            self.clean_up()

    def __set_widget(self,widget,text):
        '''
        :param widget:text that indicates which widget will be modified
        :param text: the conntent of the widget
        :return: ret_val indicates whether the server has accepted the message or not
        '''
        ret_val, response = False, ""
        if self.is_connected:
            try:
                message = widget + chr(2) + str(text)
                self.client.send(message)
                response = self.client.recv(1024)
                if (response == "ok"):
                    ret_val = True
            except Exception as e:
                self.clean_up()

        return ret_val, response

    def set_qLabel(self , labelName , text):
        '''
        set the conntent of qline
        :return:ret_val indicates whether the server has accepted the message or not and the widget content
        '''
        return self.__set_widget(labelName , text)

    def clean_up(self):
        print ("connection refused makesure the server is running")
        sys.exit(1)



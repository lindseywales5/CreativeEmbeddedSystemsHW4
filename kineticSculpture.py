#http://165.227.76.232:3000/lbw2149/running
import time
import socket
import requests

while(True):

	UDP_IP = "192.168.1.29" # The IP that is printed in the serial monitor from the ESP32
	SHARED_UDP_PORT = 4210
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
	sock.connect((UDP_IP, SHARED_UDP_PORT))
	response = requests.get("http://165.227.76.232:3000/lbw2149/running")
	json_data=response.json()
	data = str(json_data)
	sock.send(data.encode())
	print(data)
	if (data == "False"):
		time.sleep(5)
	else:
		time.sleep(30)

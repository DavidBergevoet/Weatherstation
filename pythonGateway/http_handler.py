import requests
import json

class http_handler:
	_CREDENTIAL_FILE = 'credentials.json'
	_URL = 'https://dbergevoet.nl'
	_HEADERS = {'Content-type' : 'application/x-www-form-urlencoded'}

	def __init__(self):
		file = open(self._CREDENTIAL_FILE, 'r')
		self._credentials = json.load(file)
		file.close()
		print(self._credentials)

	def send_sensor_application(self, sensor_name):
		content = f"username={self._credentials['username']}&password={self._credentials['password']}&id={sensor_name}"
		api_url = '/api/sensor_application'
		complete_url = self._URL + api_url
		print(f"Sending request to: {complete_url} with: {content}")
		response = requests.post(complete_url, content, headers=self._HEADERS)
		print(f"Response: {response.status_code} \n\t{response.content}")
		return response

	def send_sensor_temperature(self, sensor_name, temperature):
		content = f"username={self._credentials['username']}&password={self._credentials['password']}&id={sensor_name}&temp={temperature}"
		api_url = '/api/temperature'
		complete_url = self._URL + api_url
		print(f"Sending request to: {complete_url} with: {content}")
		response = requests.post(complete_url, content, headers=self._HEADERS)
		print(f"Response: {response.status_code} \n\t{response.content}")
		return response

	def send_sensor_humidity(self, sensor_name, humidity):
		content = f"username={self._credentials['username']}&password={self._credentials['password']}&id={sensor_name}&hum={humidity}"
		api_url = '/api/humidity'
		complete_url = self._URL + api_url
		print(f"Sending hum request to: {complete_url} with: {content}")
		response = requests.post(complete_url, content, headers=self._HEADERS)
		print(f"Response: {response.status_code}\n\t{response.content}")
		return response


if __name__ == '__main__':
	handler = http_handler()
	handler.send_sensor_application("Binnen")
	handler.send_sensor_temperature("Binnen", 21.5)
	handler.send_sensor_humidity("Binnen", 60)
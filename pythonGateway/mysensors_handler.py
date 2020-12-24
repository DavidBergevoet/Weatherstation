import datetime
from serial_connection import serial_connection
from http_handler import http_handler
import time

class node:
	def __init__(self, node_id, name=''):
		self._node_id = int(node_id)
		self._node_name = name
		self._received = True

	def get_node(self):
		return {"node_id":self._node_id,
				"name":self._node_name,
				"received": self._received
				}

	def reset_received(self):
		self._received = False

	def set_received(self):
		self._received = True

class mysensors_handler:
	added_node = False
	sended_broadcast = False

	def __init__(self, serial_port):
		self._serial = serial_connection(serial_port)
		self._my_nodes = []
		self._site_handler = http_handler()

	def add_node(self, node_id, name):
		for n in self._my_nodes:
			node_dict = n.get_node()
			if node_dict['node_id'] == int(node_id) or node_dict['name'] == name:
				print(f"Couldn't add node: {node_id} : {name}")
				return False
		print(f"Adding node: {node_id} : {name}")
		temp_node = node(node_id, name)
		self._my_nodes.append(temp_node)
		self._site_handler.send_sensor_application(name)
		self.added_node = True
		return True

	def handle_temp(self, node, temp):
		self._site_handler.send_sensor_temperature(node.get_node()['name'], temp)

	def handle_humidity(self, node, humidity):
		self._site_handler.send_sensor_humidity(node.get_node()['name'], humidity)

	def handle_command(self):
		self.added_node = False
		self.sended_broadcast= False
		if self._serial.is_readable():
			cmd = self._serial.read_command()
			if cmd is not None and cmd['node_id'] != 0:
				print(cmd)
				if cmd['child_sensor_id'] == 'A':
					self.add_node(cmd['node_id'], cmd['payload'])

				elif cmd['child_sensor_id'] == 'T':
					for n in self._my_nodes:
						if n.get_node()['node_id'] == cmd['node_id']:
							print(f"Received temp of {n.get_node()['node_id']} : {cmd['payload']}")
							n.set_received()
							self.handle_temp(n, cmd['payload'])
				elif cmd['child_sensor_id'] == 'H':
					for n in self._my_nodes:
						if n.get_node()['node_id'] == cmd['node_id']:
							print(f"Received hum of {n.get_node()['node_id']} : {cmd['payload']}")
							n.set_received()
							self.handle_humidity(n, cmd['payload'])

	def send_broadcast(self):
		self.sended_broadcast = True
		for n in self._my_nodes:
			print(f"Sending command to: nr: {n.get_node()['node_id']}, name : {n.get_node()['name']}")
			self._serial.write_command(n.get_node()['node_id'], child_sensor_id='R')
			n.reset_received()

	def send_retry(self):
		for n in self._my_nodes:
			if n.get_node()['received'] == False:
				print(f"Sending retry to: nr: {n.get_node()['node_id']}, name : {n.get_node()['name']}")
				self._serial.write_command(n.get_node()['node_id'], child_sensor_id='R')



if __name__ == '__main__':
	BROADCAST_DELAY = 600 # seconds
	RETRY_DELAY = 10 #seconds

	handler = mysensors_handler('/dev/ttyUSB0')
	br_datetime_start = datetime.datetime.now()
	ret_datetime_start = datetime.datetime.now()
	while 1:
		handler.handle_command()
		datetime_end = datetime.datetime.now()

		# Handling broadcast
		br_seconds_diff = (datetime_end - br_datetime_start).total_seconds()
		if br_seconds_diff >= BROADCAST_DELAY:
			ret_datetime_start = datetime.datetime.now()
			br_datetime_start = datetime.datetime.now()
			handler.send_broadcast()

		# Handling retry
		ret_seconds_diff = (datetime_end - ret_datetime_start).total_seconds()
		if ret_seconds_diff >= RETRY_DELAY:
			ret_datetime_start = datetime.datetime.now()
			handler.send_retry()
		time.sleep(0.1)

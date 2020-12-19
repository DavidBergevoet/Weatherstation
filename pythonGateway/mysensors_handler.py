from serial_connection import serial_connection

class node:
	def __init__(self, node_id, name=''):
		self._node_id = int(node_id)
		self._node_name = name

	def get_node(self):
		return {"node_id":self._node_id,
				"name":self._node_name
				}

class mysensors_handler:
	added_node = False
	send_broadcast = False

	def __init__(self, serial_port):
		self._serial = serial_connection(serial_port)
		self._my_nodes = []

	def add_node(self, node_id, name):
		print(f"Adding node: {node_id} : {name}")
		for n in self._my_nodes:
			node_dict = n.get_node()
			if node_dict['node_id'] == int(node_id) or node_dict['node_name'] == name:
				return False
		temp_node = node(node_id)
		self._my_nodes.append(temp_node)
		self.added_node = True
		return True

	def handle_command(self):
		self.added_node = False
		self.send_broadcast= False
		if self._serial.is_readable():
			cmd = self._serial.read_command()
			print(cmd)
			if cmd['node_id'] != '0' and cmd['child_sensor_id'] == 'A':
				self.add_node(cmd['node_id'], cmd['payload'])
				print(self._my_nodes[0].get_node())
				print(self.added_node)




if __name__ == '__main__':
	handler = mysensors_handler('/dev/ttyUSB0')
	while 1:
		handler.handle_command()
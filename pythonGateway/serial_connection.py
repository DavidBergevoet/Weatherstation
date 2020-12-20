import serial


class serial_connection:

	def __init__(self, port, baudrate=115200):
		self._serial_port = serial.Serial(port,baudrate)
		self._inited = True

	def disconnect(self):
		self._serial_port.close()
		self._inited = False

	def read_command(self):
		if self._inited and self._serial_port.is_open and self._serial_port.in_waiting > 0:
			command = self._serial_port.readline().decode('utf-8')
			command_list = command.split(';')
			indices = ['node_id','child_sensor_id', 'command', 'ack','type','payload']

			if len(command_list) == len(indices):
				temp_dict = dict(zip(indices,command_list))
				temp_dict['payload'] = temp_dict['payload'][:-1]
				temp_dict['node_id'] = int(temp_dict['node_id'])
				temp_dict['child_sensor_id'] = chr(int(temp_dict['child_sensor_id']))
				return temp_dict
		#print("Unsuccessful read")
		return None

	def write_command(self, node_id, child_sensor_id=0, command=0, ack=0, type=0, payload=''):
		if self._inited and self._serial_port.is_open and self._serial_port.writable:
			cmd = f"{node_id};{ord(child_sensor_id)};{command};{ack};{type};{payload}\n"
			print(f"Writing command: '{cmd[:-1]}'")
			self._serial_port.write(cmd.encode('utf-8'))

	def is_readable(self):
		return self._serial_port.readable


if __name__ == '__main__':
	ser = serial_connection('/dev/ttyUSB0')
	while 1:
		if ser.is_readable():
			cmd = ser.read_command()
			print(cmd)
			if cmd['node_id'] != '0' and cmd['child_sensor_id'] == 'A':
				ser.write_command(2, 82, 0,0,0,'')


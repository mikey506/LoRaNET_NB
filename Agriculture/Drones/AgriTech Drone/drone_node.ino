import socket
import machine
import ujson
import time

# Set your LoRa parameters
LORA_FREQUENCY = 868E6
LORA_SF = 7
LORA_PORT = 1  # Set your LoRa port

# Initialize LoRa
lora = Lora(mode=LoRa.LORA, frequency=LORA_FREQUENCY, sf=LORA_SF)
lora_socket = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
lora_socket.setblocking(False)

# Initialize sensors and modules (adjust pins and configurations as needed)
dht_sensor = DHT(pin=23, sensor_type=0)  # DHT11 Temperature and Humidity Sensor
soil_moisture_sensor = ADC(Pin(35))  # Capacitive Soil Moisture Sensor (V1.2)
ultrasonic_front = Ultrasonic(trigger_pin=25, echo_pin=26)  # Front Ultrasonic Sensor
ultrasonic_back = Ultrasonic(trigger_pin=27, echo_pin=32)  # Back Ultrasonic Sensor
ultrasonic_left = Ultrasonic(trigger_pin=12, echo_pin=14)  # Left Ultrasonic Sensor
ultrasonic_right = Ultrasonic(trigger_pin=13, echo_pin=15)  # Right Ultrasonic Sensor
ultrasonic_above = Ultrasonic(trigger_pin=16, echo_pin=17)  # Above Ultrasonic Sensor
ultrasonic_below = Ultrasonic(trigger_pin=18, echo_pin=19)  # Below Ultrasonic Sensor
relay = Relay([4, 5, 6, 7])  # 4 Channel Relay Board

# GPS module settings
uart = UART(1, baudrate=9600, tx=17, rx=16)
gps = Gps(uart, timeout=3000)

# Function to send sensor data to the server_node
def send_sensor_data():
    temperature = dht_sensor.temperature()
    humidity = dht_sensor.humidity()
    soil_moisture = soil_moisture_sensor.read()
    ultrasonic_data = {
        "front_distance": ultrasonic_front.distance_cm(),
        "back_distance": ultrasonic_back.distance_cm(),
        "left_distance": ultrasonic_left.distance_cm(),
        "right_distance": ultrasonic_right.distance_cm(),
        "above_distance": ultrasonic_above.distance_cm(),
        "below_distance": ultrasonic_below.distance_cm(),
    }
    gps_data = {
        "latitude": gps.latitude(),
        "longitude": gps.longitude(),
    }

    sensor_data = {
        "drone_id": DRONE_ID,
        "temperature": temperature,
        "humidity": humidity,
        "soil_moisture": soil_moisture,
        "ultrasonic_data": ultrasonic_data,
        "gps_data": gps_data,
    }

    lora_socket.send(ujson.dumps(sensor_data), port=LORA_PORT)

# Function to receive commands from the server_node
def receive_commands():
    try:
        data = lora_socket.recv(256)
        if data:
            command_data = ujson.loads(data)
            command = command_data.get("command")
            if command:
                handle_command(command)
    except Exception as e:
        pass

# Function to handle commands received from the server_node
def handle_command(command):
    if command == "takeoff":
        # Implement takeoff logic
        pass
    elif command == "land":
        # Implement land logic
        pass
    elif command == "move_forward":
        # Implement move forward logic
        pass
    elif command == "move_backward":
        # Implement move backward logic
        pass
    # Add more command handling logic as needed

# Main loop
while True:
    try:
        send_sensor_data()
        receive_commands()
    except Exception as e:
        print("Error:", str(e))
    time.sleep(1)  # Adjust the sleep duration based on your requirements

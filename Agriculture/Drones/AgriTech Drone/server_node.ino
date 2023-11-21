from flask import Flask, request, jsonify, render_template
import socket
import network
import machine
import ujson

app = Flask(__name__)

# LoRa settings
lora = Lora(mode=LoRa.LORA, frequency=868E6, sf=7)
lora_socket = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
lora_socket.setblocking(False)

# WiFi AP settings
ssid = "YOUR_WIFI_SSID"
password = "YOUR_WIFI_PASSWORD"
ap = network.WLAN(network.AP_IF)
ap.active(True)
ap.config(essid=ssid, password=password)

# Sample drone state
drone_state = {
    "status": "Idle",
    "battery": 90,
    "location": {"latitude": 0.0, "longitude": 0.0},
    "temperature": 25.0,
    "humidity": 50.0,
    "soil_moisture": 40,
    "ultrasonic_data": {
        "front_distance": 0,
        "back_distance": 0,
        "left_distance": 0,
        "right_distance": 0,
        "above_distance": 0,
        "below_distance": 0,
    },
    "relay_states": {
        "channel_1": False,
        "channel_2": False,
        "channel_3": False,
        "channel_4": False,
    },
    "gps_data": {"latitude": 0.0, "longitude": 0.0},
    # Add more drone state parameters as needed
}

# Sample commands to be sent to the drone
commands = {
    "takeoff": "Take off",
    "land": "Land",
    "move_forward": "Move Forward",
    "move_backward": "Move Backward",
    # Add more commands as needed
}

@app.route('/get_drone_state', methods=['GET'])
def get_drone_state():
    return jsonify(drone_state)

@app.route('/send_command', methods=['POST'])
def send_command():
    content = request.get_json()
    command = content.get('command')

    # Send the command to the drone using LoRa
    send_command_to_drone(command)

    return jsonify({"status": "Command sent successfully", "command": command})

def send_command_to_drone(command):
    # Implement logic to send the command to the drone using LoRa
    lora_socket.send(ujson.dumps({"command": command}))

@app.route('/')
def index():
    return render_template('index.html', commands=commands)

@app.route('/receive_sensor_data', methods=['POST'])
def receive_sensor_data():
    content = request.get_json()

    # Update drone state with received sensor data
    drone_state['temperature'] = content.get('temperature')
    drone_state['humidity'] = content.get('humidity')
    drone_state['soil_moisture'] = content.get('soil_moisture')
    drone_state['ultrasonic_data'] = content.get('ultrasonic_data')
    drone_state['relay_states'] = content.get('relay_states')
    drone_state['gps_data'] = content.get('gps_data')

    return jsonify({"status": "Sensor data received successfully"})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)  # Run the server on the local network


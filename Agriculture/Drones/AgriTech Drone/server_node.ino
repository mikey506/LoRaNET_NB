from flask import Flask, request, jsonify, render_template
import socket
import machine
import ujson
import os
import time

app = Flask(__name__)

# LoRa settings
lora = Lora(mode=LoRa.LORA, frequency=868E6, sf=7)
lora_socket = socket.socket(socket.AF_LORA, socket.SOCK_RAW)
lora_socket.setblocking(False)

# Set your server's LoRa port
SERVER_LORA_PORT = 1

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
    return jsonify(get_drone_state_data())

@app.route('/send_command', methods=['POST'])
def send_command():
    content = request.get_json()
    command = content.get('command')
    drone_id = content.get('drone_id')

    # Send the command to the specific drone using LoRa
    send_command_to_drone(command, drone_id)

    return jsonify({"status": "Command sent successfully", "command": command})

def send_command_to_drone(command, drone_id):
    # Implement logic to send the command to the specific drone using LoRa
    lora_socket.send(ujson.dumps({"command": command, "drone_id": drone_id}), port=SERVER_LORA_PORT)

@app.route('/')
def index():
    return render_template('index.html', commands=commands)

@app.route('/receive_sensor_data', methods=['POST'])
def receive_sensor_data():
    content = request.get_json()

    # Update drone state with received sensor data
    drone_id = content.get('drone_id')
    drone_state = get_drone_state_data(drone_id)
    drone_state['temperature'] = content.get('temperature')
    drone_state['humidity'] = content.get('humidity')
    drone_state['soil_moisture'] = content.get('soil_moisture')
    drone_state['ultrasonic_data'] = content.get('ultrasonic_data')
    drone_state['relay_states'] = content.get('relay_states')
    drone_state['gps_data'] = content.get('gps_data')

    save_drone_state_data(drone_id, drone_state)

    return jsonify({"status": "Sensor data received successfully"})

def get_drone_state_data(drone_id=None):
    # Read the current state of a specific drone or all drones
    drone_states = {}
    if drone_id:
        filename = f'drone_{drone_id}_state.json'
        if os.path.exists(filename):
            with open(filename, 'r') as file:
                drone_states[drone_id] = ujson.load(file)
    else:
        for file in os.listdir():
            if file.endswith('_state.json'):
                with open(file, 'r') as f:
                    drone_id = file.split('_')[1]
                    drone_states[drone_id] = ujson.load(f)

    return drone_states

def save_drone_state_data(drone_id, drone_state):
    # Save the current state of a specific drone
    filename = f'drone_{drone_id}_state.json'
    with open(filename, 'w') as file:
        ujson.dump(drone_state, file)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)  # Run the server on the local network


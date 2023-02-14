#!/usr/bin/python3

import random
import time
import paho.mqtt.client as mqtt
import paho.mqtt.publish as publish

host = "127.0.0.1"
port = 9001
username = "water"
password = "water"
topic = "water/level"
client_id = f'water-publisher-{random.randint(0, 1000)}'

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Filed to connect, return code %d\n", rc)

    client = mqtt.Client(client_id=client_id, transport="websockets")
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(host, port)
    return client

def publish(client):
    msg_count = 100
    while True:
        time.sleep(1)
        result = client.publish(topic, msg_count)
        status = result[0]
        if status == 0:
            print(f"Send `{msg_count}` to topic `{topic}`")
        else:
            print(f"Filed to send message to topic {topic}")
        msg_count -=1
        if msg_count == -1:
            msg_count = 100

def run():
    client = connect_mqtt()
    client.loop_start()
    publish(client)

if __name__ == '__main__':
    run()



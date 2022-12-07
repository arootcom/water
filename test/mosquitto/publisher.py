#!/usr/bin/python3

import paho.mqtt.publish as publish

host = "localhost"

publish.single(
    topic="water/level", payload="{\"device\":1,\"level\":100}", hostname=host,
    auth={"username":"water", "password":"water"}
)



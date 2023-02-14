# Requires

## Clone water

    $ git clone git@github.com:arootcom/water.git
    $ cd ./water

## Install mosquitto-clients

On Linux with the apt-get package manager:

    $ sudo apt-get install mosquitto-clients

## Create docker image "MQTT Tiles"

    $ cd ..
    $ git clone https://github.com/flespi-software/MQTT-Tiles.git
    $ cd ./MQTT-Tiles/
    $ cp ../water/manifest/tiles/Dockerfile ./
    $ docker build . -t rootcom/mqtt-tiles

# Start

    $ cd ./manifest
    $ docker-compose up -d

For testing, you can run a script that will write the water level in the water/level topic

    $ ./test/mosquitto/publisher.py

Open in a browser
http://localhost:8080/

Сreate a connection
* MQTTclient name: water-client
* ClientID: water-tiles
* Host: http://127.0.0.1:9001
* Keep alive: 60
* Version of MQTT: 3.1.1
* Clean session:  true
* Username: water
* Password: water

Create dashboard

Create Widgets

# Logs

    $ tail -f ./manifest/mosquitto/log/mosquitto.log

# Mosquitto

Using [MQTT](http://en.wikipedia.org/wiki/Mqtt) and [Mosquitto](http://mosquitto.org/)

## Subsriber

    $ mosquitto_sub -t water/level --username water --pw water

## Publisher

    $ mosquitto_pub -d -h 127.0.0.1 -p 1883 -q 0 -t water/level -m "{\"device\":1,\"level\":100}" --username water --pw water

## Docker

### Execute command inside container

    $ docker exec -it mosquitto sh

### Change user password / create a new user

    $ docker exec -it mosquitto mosquitto_passwd -c /mosquitto/config/passwd <user name>

### Delete user

    $ docker-compose exec mosquitto mosquitto_passwd -D /mosquitto/config/password.txt user

# References

 * [MQTT](http://en.wikipedia.org/wiki/Mqtt)
 * [Mosquitto](http://mosquitto.org/)
 * [Mosquitto docker-compose](https://github.com/vvatelot/mosquitto-docker-compose)
 * [Mosquitto python example](https://github.com/roppert/mosquitto-python-example)
 * [MQTT Tiles](https://flespi.com/tools/mqtt-tiles)


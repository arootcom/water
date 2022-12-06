
Stand for development

## Start

    cd ./manifest
    docker-compose up -d

## Logs

    tail -f ./manifest/mosquitto/log/mosquitto.log

## Dockers

### Mosquitto

Using [MQTT](http://en.wikipedia.org/wiki/Mqtt) and [Mosquitto](http://mosquitto.org/)

Execute command inside container

    docker exec -it mosquitto sh

Create a new user

    docker exec -it mosquitto mosquitto_passwd -c /mosquitto/config/passwd <user name>



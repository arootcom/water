
Using [MQTT](http://en.wikipedia.org/wiki/Mqtt) and [Mosquitto](http://mosquitto.org/)

## Execute command inside container

    docker exec -it mosquitto sh

## Create a new user

    docker exec -it mosquitto mosquitto_passwd -c /mosquitto/config/passwd <user name>

Еnter a new password



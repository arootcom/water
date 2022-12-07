
## Requires

Install mosquitto-clients

On Linux with the apt-get package manager:

    sudo apt-get install mosquitto-clients

## Start

    cd ./manifest
    docker-compose up -d

## Logs

    tail -f ./manifest/mosquitto/log/mosquitto.log


## Mosquitto

Using [MQTT](http://en.wikipedia.org/wiki/Mqtt) and [Mosquitto](http://mosquitto.org/)

### Subsriber

    mosquitto_sub -t water/level --username water --pw water

### Publisher

    mosquitto_pub -d -h 127.0.0.1 -p 1883 -q 0 -t water/level -m "{\"device\":1,\"level\":100}" --username water --pw water

### Docker

#### Execute command inside container

    docker exec -it mosquitto sh

#### Change user password / create a new user

    docker exec -it mosquitto mosquitto_passwd -c /mosquitto/config/passwd <user name>

#### Delete user

    docker-compose exec mosquitto mosquitto_passwd -D /mosquitto/config/password.txt user

## See Also

[MQTT](http://en.wikipedia.org/wiki/Mqtt)
[Mosquitto](http://mosquitto.org/)
[Mosquitto docker-compose](https://github.com/vvatelot/mosquitto-docker-compose)
[Mosquitto python example](https://github.com/roppert/mosquitto-python-example)



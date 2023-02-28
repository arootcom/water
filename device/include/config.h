//
// config.h
//

// Настройки WiFi
#define wifi_ssid     "iPhone (Кирилл )"
#define wifi_pass     "vjqKirill05"

// Сервер MQTT
#define mqtt_server   "172.20.10.6"
#define mqtt_port     1883
#define mqtt_login    "water"
#define mqtt_pass     "water"

// MQTT топики
#define mqtt_topic_out     "water/level/1"
#define latitude_topic_out "water/topic/to/lat/1"
#define longitude_topic_out "water/topic/to/lon/1"

// Настройки весов
#define DT  D2                  
#define SCK D3
#define calibration_factor 0.8
#define FULL 8140
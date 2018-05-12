import paho.mqtt.publish as publish

publish.single("hello/world", '{"sensor":"clock","time":"12/05/2018 14:05:55","number":0}', hostname="iot.franciscocalaca.com")
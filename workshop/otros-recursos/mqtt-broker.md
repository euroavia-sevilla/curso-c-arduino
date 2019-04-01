# MQTT Broker

A MQTT Broker is configured for Euroavia C/Arduino workshop. The provided ESP8266-based boards will be able to publish generic and sensor data to this server.

* Address: `iot.tesla.studio`
* MQTT port: `1883`
* WebSocket port: `1884`
* MQTT URI: [mqtt://iot.tesla.studio:1883](mqtt://iot.tesla.studio:1883)
* WebSockeet URI: [ws://iot.tesla.studio:1884](ws://iot.tesla.studio:1884)

Available topics and privacy for this devices:

| Topic path | Description |
| :----- | :----- |
| `euroavia-pool/#` | Subscribe access to any device (public pool) |
| `euroavia-pool/USERNAME/#` | Subscribe/Publish access to a specific path (public pool) |
| `euroavia-devices/USERNAME/#` | Subscribe/Publish access (private zone) |

## Install both broker and clients

```shell
root@iot:~# apt-get install mosquitto mosquitto-clients
root@iot:~# service mosquitto status
```

If OK will look like this:

```shell
● mosquitto.service - LSB: mosquitto MQTT v3.1 message broker
   Loaded: loaded (/etc/init.d/mosquitto; generated; vendor preset: enabled)
   Active: active (running) since Fri 2019-03-29 00:52:35 CET; 7s ago
     Docs: man:systemd-sysv-generator(8)
   CGroup: /system.slice/mosquitto.service
           └─4806 /usr/sbin/mosquitto -c /etc/mosquitto/mosquitto.conf

Mar 29 00:52:35 iot systemd[1]: Starting LSB: mosquitto MQTT v3.1 message broker...
Mar 29 00:52:35 iot mosquitto[4801]: Starting network daemon:: mosquitto.
Mar 29 00:52:35 iot systemd[1]: Started LSB: mosquitto MQTT v3.1 message broker.
```

## Configure protocols

Enable both MQTT and WebSockets protocols

```bash
root@iot:~# cat /etc/mosquitto/conf.d/protocols.conf
listener 1883
protocol mqtt

listener 1884
protocol websockets
```

Restart the server and check status

```bash
root@iot:~# service mosquitto restart
root@iot:~# service mosquitto status
```

## Configure storage and persistence

This allows the broker to keep the data even between restarts

```bash
root@iot:~# cat /etc/mosquitto/conf.d/storage.conf
persistence true
persistence_location /var/lib/mosquitto/
persistence_file mosquitto.db
```

Restart the server and check status

```bash
root@iot:~# service mosquitto restart
root@iot:~# service mosquitto status
```

## Configure password file and users

Add first (-c), then in batch (-b). Use (-D) for user deletion

```bash
root@iot:~# mosquitto_passwd -c /etc/mosquitto/passwd web_client
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0001 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0002 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0003 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0004 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0005 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0006 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0007 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0008 PASSHERE
root@iot:~# mosquitto_passwd -b /etc/mosquitto/passwd tc_d1_0000 PASSHERE
```

## Configure access control list (ACL)

Create rules for clients with and without username

```bash
root@iot:~# cat /etc/mosquitto/aclfile
#
# Clients without username
#
# This affects access control for clients with no username.
topic read $SYS/#

#
# Clients with username
#
## Main users: admin and web_client
user admin
topic readwrite #

user web_client
topic read #

## Other users: TC-Euroavia
pattern readwrite euroavia-pool/%u/#
pattern read euroavia-pool/#
pattern readwrite euroavia-devices/%u/#
```

## Configure clients access

Enable both password and ACL

```bash
root@iot:~# cat /etc/mosquitto/conf.d/access.conf
allow_anonymous false
password_file /etc/mosquitto/passwd
acl_file /etc/mosquitto/aclfile
```

Restart the server and check status

```bash
root@iot:~# service mosquitto restart
root@iot:~# service mosquitto status
```

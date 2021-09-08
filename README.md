# Hydroponics

<h1 align="center"><Hydroponics System></h1>
In this project, the Raspberry pi 4B will be the controller of the Hydroponics System which connected to the Arduino Nano with the sensors and water pumps. The sensor data will trasfer throught the IoT grafana and InflexDB. VNC will be used in order to remote the Raspberry Pi

## Links

- [VNC](https://www.realvnc.com/en/connect/download/viewer/)

- [InfluxDB and Grafana Quick start](https://simonhearne.com/2020/pi-influx-grafana/)


## Equipments:

- Raspberry Pi 4B 4GB

- Arduino Nano

- Water level sensor

- DHT22 temperature-humidity sensor
  
- TDS sensor

- pH value sensor
  
- Water pump X2
  
## Screenshots

![Home Page](https://github.com/Chrischrislch/Hydroponics/blob/main/Screenshot%202021-09-07%20at%204.57.31%20PM.png)
(https://github.com/Chrischrislch/Hydroponics/blob/main/Arduino%20overview.png)

![plot](https://github.com/Chrischrislch/Hydroponics/blob/main/Arduino%20overview.png)  

##Guideline:
  
### Pin connection:
  
| Water Level Sensor | Arduino Nano |
| :----------------- | :----------: |
| S                  |   A2   |
| +                  |   5V   |
| -                  |   GND  |

<br>

| TDS Meter V1.0 | Arduino Nano |
| :------------- | :-----------:|
| A              |   A1   |
| +              |   5V   |
| -              |   GND  |
  
<br>

| pH Meter V1.1 | Arduino Nano |
| :------------ | :----------: |
| A             |   A0   |
| +             |   5V   |
| -             |   GND  |
  
<br>
  
| Temperature and Humidity (DHT22) | Arduino Nano |
| :------------------------------- | :----------: |
| OUT                              |   D4   |
| +                                |   5V   |
| -                                |   GND  |
  
<br>
  
| JQC-3FF-S-Z (WaterPump) | Arduino Nano |
| :---------------------  | :----------: |
| IN                      |   D6         |
| VCC                     |   5V         |
| GND                     |   GND        |
  
<br>
  
| JQC-3FF-S-Z (MixturePump) | Arduino Nano |
| :------------------------ | :----------: |
| IN                        |   D7         |
| VCC                       |   5V         |
| GND                       |   GND        |


### Sensor Testing,

- [Arduino Code](https://github.com/Chrischrislch/Hydroponics/tree/main/Sensor%20testing)

### Serial communication between Arduino and Raspberry Pi,

In the Arduino IDE, open the Serial Monitor
To find the corresponding USB port name, pls type "ls  /dev/ttyUSB*" in the Raspberry Pi Terminal.

- [Code](https://github.com/Chrischrislch/Hydroponics/tree/main/SerialTest)

### InfluxDB testing,

After the Quick set up of the InfluxDB and grafana, you can try with the following code:  
- [Code](https://github.com/Chrischrislch/Hydroponics/blob/main/DBtest.py)


### Result,

Before running the python, pls remember to install the required libraries. <br>
pip3 install -r - [requirements2.txt](https://github.com/Chrischrislch/Hydroponics/blob/main/requirements2.txt)<br>
pip install -r - [requirements.txt](https://github.com/Chrischrislch/Hydroponics/blob/main/requirements.txt)

- [Raspberry Pi Code] (https://github.com/Chrischrislch/Hydroponics/blob/main/System.py) <br>
- [Arduino Code] (https://github.com/Chrischrislch/Hydroponics/blob/main/Hydroponics_system.ino) <br>


## Built With

- C++
- Python
- Unix

## Future Updates

- [ ] Reliable Storage



## 🤝 Support

Contributions, issues, and feature requests are welcome!

Give a ⭐️ if you like this project!

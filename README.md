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
  
## Pin connection:

### Sensor Testing,

- [Arduino Code](https://github.com/Chrischrislch/Hydroponics/tree/main/Sensor%20testing)

### Serial communication between Arduino and Raspberry Pi,

In the Arduino IDE, open the Serial Monitor
To find the corresponding USB port name, pls type "ls  /dev/ttyUSB*" in the Raspberry Pi Terminal.

- [Code](https://github.com/Chrischrislch/Hydroponics/tree/main/SerialTest)

### InfluxDB testing,

After the Quick set up of the InfluxDB and grafana, you can try with the following coed:  
- [Code](https://github.com/Chrischrislch/Hydroponics/blob/main/DBtest.py)


### Result,

Before running the python, pls remember to install the required libraries.
pip3 install -r - [requirements2.txt](https://github.com/Chrischrislch/Hydroponics/blob/main/requirements2.txt)<br>
pip install -r - [requirements.txt](https://github.com/Chrischrislch/Hydroponics/blob/main/requirements.txt)


### `"serve": "node server"`

For running the server file on you can use this command.

### `npm run serve`

## Built With

- C++
- Python
- Unix

## Future Updates

- [ ] Reliable Storage

## Author

**Chris**

- [Profile](https://github.com/rohit19060 "Rohit jain")
- [Email](mailto:rohitjain19060@gmail.com?subject=Hi "Hi!")
- [Website](https://kingtechnologies.in "Welcome")

## 🤝 Support

Contributions, issues, and feature requests are welcome!

Give a ⭐️ if you like this project!

from io import StringIO
import subprocess
import serial, time, random
import smtplib, ssl
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from picamera import PiCamera
from time import sleep
import io
import picamera
import logging
import socketserver
from threading import Condition
from http import server
 
def email():
 #Go to the account settings and allow less secure apps:
 #https://myaccount.google.com/lesssecureapps?pli=1&rapt=AEjHL4M7GRZ51xeWLASZaUizwZbotPlnp42GfSm2Sd66lp74_cQwYDeubdh7-Q5778A1QnN1CW7HzDYjBUwU040D5puayfiaAg
 
 sender = 'xxx@gmail.com'
 senderpassword = 'yourpassword'
 receiver = 'xxx@gmail.com'
 msg = MIMEMultipart()
 msg['From'] = sender
 msg['To'] = receiver
 msg['Subject'] = 'Warning'
 message = 'Tempperature too high!'
 msg.attach(MIMEText(message))
 mailserver = smtplib.SMTP('smtp.gmail.com',587)
# identify ourselves to smtp gmail client
 mailserver.ehlo()
# secure our email with tls encryption
 mailserver.starttls()
# re-identify ourselves as an encrypted connection
 mailserver.ehlo()
 mailserver.login(sender, senderpassword)
 mailserver.sendmail(sender,receiver,msg.as_string())
 mailserver.quit()
 
ifuser = "grafana"
ifpass = "<password>"
ifdb   = "home"
ifhost = "yourip"
ifport = 8086
#email()
 
 
# InfluxDB
#from influxdb import InfluxDBClient
from influxdb import InfluxDBClient
#from influxdb import SYNCHRONOUS
client = InfluxDBClient(ifhost,ifport,ifuser,ifpass,ifdb)
#client = InfluxDBClient(host='192.168.0.37', port=8086, database='home')
#client = InfluxDBClient(host='192.168.0.37', port=8086)
#client.switch_database('<home>')
 
bucket = "<my-bucket>"
org = "<my-org>"
token = "<my-token>"
# Store the URL of your InfluxDB instance
url="https://us-west-2-1.aws.cloud2.influxdata.com"
 
 
 
# Serial communication with Arduino
#ser = serial.Serial('/dev/ttyUSB0', 115200) #timeout must fit to thr arduino timestamp
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1) #timeout must fit to thr arduino timestamp
ser.flush()
 
import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '3'
import numpy as np
import json
from os.path import join
import numpy as np
tempa = 0.0
tempb = 0.0
tempc = 0
tempd = 0
tempe = 0.0
 
 
while True:
 #print(serialdata)
 try:
   ser.write(b"S\n")
   line = ser.readline().decode('utf-8').rstrip()
   dataset = line.split("-")
   print(line)
   if (len(dataset) == 5):
     humidity = float(dataset[0])
     if (humidity < 10.0):
       humidity = 50.0
     temp = float(dataset[1])
     waterlvl = int(dataset[2])
     tds = int(dataset[3])
     ph = float(dataset[4])
     json_body = [
     {
     "measurement": "hydroponics-temp",
     "fields": {
     "value": temp
     }
     }
     ]
 
     json_body2 = [
     {
     "measurement": "hydroponics-humidity",
     "fields": {
     "value": humidity
     }
     }
     ]
     json_body3 = [
     {
     "measurement": "hydroponics-waterlevel",
     "fields": {
     "value": waterlvl
     }
     }
     ]
     json_body4 = [
     {
     "measurement": "hydroponics-tds",
     "fields": {
     "value": tds
     }
     }
     ]
     json_body5 = [
     {
     "measurement": "hydroponics-ph",
     "fields": {
     "value": ph
     }
     }
     ]
   if temp > 40.0:
     email()
   client.write_points(json_body)
   client.write_points(json_body2)
   client.write_points(json_body3)
   client.write_points(json_body4)
   client.write_points(json_body5)
 except Exception:
   #print('An exception flew by!')
   a = tempa
 time.sleep(10)
 
#  temp = int(dataset[2])
#  humidity = int(dataset[3])
#  waterlvl = int(dataset[4])
 
# print("ph: ",ph," tds: ",tds," temp: ",temp," humidity: ",humidity," waterlvl: ", waterlvl)
 
  #time.sleep(10)       #larger timestamp can be more stable.. 60s


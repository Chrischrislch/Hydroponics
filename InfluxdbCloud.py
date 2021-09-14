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
from datetime import datetime, timedelta
from random import randrange, uniform
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

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

# You can generate a Token from the "Tokens Tab" in the UI
token = "your Tokens"
org = "your org"
bucket = "your bucket"
client = InfluxDBClient(url="https://ap-southeast-2-1.aws.cloud2.influxdata.com", token=token)
write_api = client.write_api(write_options=SYNCHRONOUS)
#write_api = client.write_api()

ser = serial.Serial('/dev/ttyUSB1', 115200, timeout=1) #timeout must fit to thr arduino timestamp
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
now = datetime.utcnow()

while True:
  #print(serialdata)
  try:
     #for x in range(1, 10):
    ser.write(b"S\n")
    line = ser.readline().decode('utf-8').rstrip()
    dataset = line.split("-")
    #print(line)
    if (len(dataset) == 5):
        print(line)
        hum = float(dataset[0])
        if (hum < 10.0):
            hum = 50.0
        temp = float(dataset[1])
        waterlvl = int(dataset[2])
        tds = int(dataset[3])
        ph = float(dataset[4])
        point = Point("temp") \
        .tag("host", "host1") \
        .field("humidity", hum) \
        .field("tempature", temp) \
        .field("water_level", waterlvl) \
        .field("tds", tds) \
        .field("ph", ph)
        #.time(now - 5*timedelta(minutes=x), WritePrecision.NS)
        # write_api.write(bucket=bucket, org=org, record=p)
        write_api.write(bucket, org, point)
        #write_api.write(bucket, org, data)
        if temp > 40.0:
            email()

  except Exception:
      a = tempa
        #print('An exception flew by!')
  time.sleep(10)

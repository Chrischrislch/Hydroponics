from datetime import datetime, timedelta

from random import randrange, uniform


from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS

# You can generate a Token from the "Tokens Tab" in the UI
token = "your Tokens"
org = "your org"
bucket = "your bucket"
client = InfluxDBClient(url="https://ap-southeast-2-1.aws.cloud2.influxdata.com", token=token)
write_api = client.write_api(write_options=SYNCHRONOUS)
now = datetime.utcnow()

for x in range(1, 10):
    ph = round(uniform(1, 14), 1)
    humidity = randrange(10, 99, 1) 
    val = randrange(22, 40, 1) 
    tds = randrange(200, 300, 1) 
    water_level = randrange(0, 100, 1) 
    print(ph)

    point = Point("temp") \
    .tag("host", "host1") \
    .field("ran", val) \
    .field("tds", tds) \
    .field("water_level", water_level) \
    .field("ph", ph) \
    .field("humidity", humidity) \
    .time(now - 5*timedelta(minutes=x), WritePrecision.NS)


    write_api.write(bucket, org, point)
    # write_api.write(bucket, org, data)

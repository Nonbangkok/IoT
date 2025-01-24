# import Library
from machine import Pin,SoftI2C 
from time import sleep
from hcsr04 import HCSR04 # link : https://github.com/PerfecXX/KMITL-IIoTDevBoard/blob/main/library/hcsr04.py
from ssd1306 import SSD1306_I2C # link : https://github.com/PerfecXX/MicroPython-SSD1306/blob/main/ssd1306.py
from netpie import NETPIE # link : https://github.com/PerfecXX/MicroPython-NETPIE/blob/main/netpie.py
from network import WLAN,STA_IF

# Delare Constant
screen_width = 128
screen_height = 64

client_id = "ee5f92e5-b878-4332-93cf-dd1d77634929"
token = "d2TjifH2DqYhMwdRHQjzkf7Kxw3FD3WM"
secret = "C8XtYJpeJBxTdRBHAitoG19Xp5VGtfCC"

# Pin Setup
ultrasonic = HCSR04(trigger_pin=18,echo_pin=19)
i2c = SoftI2C(scl=Pin(22),sda=Pin(21))
oled = SSD1306_I2C(screen_width,screen_height,i2c)

# Network Setup
ssid = "Wokwi-GUEST"
password = ""

wlan = WLAN(STA_IF)
wlan.active(True)
if not wlan.isconnected():
  print("Connecting to wifi",ssid)
  wlan.connect(ssid,password)
  while not wlan.isconnected():
    pass

print("Conecction Successful!")

# NETPIE Setup
netpie_cilent = NETPIE()
netpie_cilent.set_profile(client_id,token,secret)
netpie_cilent.connect()

print("Netpie Connection Successful!")

while True:
  # get distance and screening
  distance = ultrasonic.distance_cm()
  oled.fill(0)
  # text,x,y,color
  oled.text("Dis:",0,0)
  oled.text(str(distance),40,0)
  oled.show()

  # Create payload prepare to publish to NETPIE
  payload = {
    "distance":distance
  }

  # Plublish to NETPIE
  netpie_cilent.publishShadow(payload)

  sleep(1)

# link : https://wokwi.com/projects/420876599132199937

# Import Library
from machine import Pin
from time import sleep

# Pin Setup
led_pin = Pin(15,Pin.OUT)

# LED Blinking every 1 second
while True:
  led_pin.value(1) # Turn on LED
  sleep(1) # Sleep for 1 second
  led_pin.value(0) # Turn off LED
  sleep(1) # Sleep for 1 second

# Link : https://wokwi.com/projects/420875564825029633  

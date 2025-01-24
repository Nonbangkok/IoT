# Import Library
from machine import Pin
from time import sleep

# Pin Setup
btn_pin = Pin(2,Pin.IN)
led_pin = Pin(15,Pin.OUT)

while True:
    # Read Button State
    btn_state = btn_pin.value()
    print(btn_state)

    # Check Button State for turn the LED
    if btn_state == 1:
        led_pin.value(1)
    else :
        led_pin.value(0)

    sleep(0.3)

# link : https://wokwi.com/projects/420876334711695361

# Author: David Ramirez

import time
import RPi.GPIO as GPIO

# Import the ADS1x15 module.
import Adafruit_ADS1x15
GPIO.setmode(GPIO.BCM)

x = 10000
water_pump_relay = 17
GPIO.setup(water_pump_relay, GPIO.OUT)
# Create an ADS1115 ADC (16-bit) instance.
adc = Adafruit_ADS1x15.ADS1115()


def turnoff():
    GPIO.output(water_pump_relay, GPIO.LOW)
GAIN = 1

print('Reading ADS1x15 values, press Ctrl-C to quit...')

print('| {0:>6} | {1:>6} | {2:>6} | {3:>6} |'.format(*range(4)))
print('-' * 37)
# Main loop.
while True:
    # Read all the ADC channel values in a list.
    values = [0]*4
    for i in range(4):
        # Read the specified ADC channel using the previously set gain value.
        values[i] = adc.read_adc(i, gain=GAIN)
        a = values[0]
        b = values[1]
        c = values[2]
        d = values[3]
        
        
        if a > x:
            flag_a = True
            while flag_a:
                GPIO.output(water_pump_relay, GPIO.HIGH)
                a = adc.read_adc(0, gain=GAIN)
                if a < x:
                    flag_a = False
        elif b > x:
            flag_b = True
            while flag_b:
                GPIO.output(water_pump_relay, GPIO.HIGH)
                b = adc.read_adc(1, gain=GAIN)
                if b < x:
                    flag_b = False
        elif c > x:
            flag_c = True
            while flag_c:
                GPIO.output(water_pump_relay, GPIO.HIGH)
                c = adc.read_adc(2, gain=GAIN)
                if c < x:
                    flag_c = False
        elif d > x:
            flag_d = True
            while flag_d:
                GPIO.output(water_pump_relay, GPIO.HIGH)
                d = adc.read_adc(3, gain=GAIN)
                if d < x:
                    flag_d = False
        else:
            turnoff()
        
    # Print the ADC values.
    print('| {0:>6} | {1:>6} | {2:>6} | {3:>6} |'.format(*values))
    # Pause for 5ms
    time.sleep(0.005)

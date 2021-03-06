# Simple demo of of the PCA9685 PWM servo/LED controller library.
# This will move channel 0 from min to max position repeatedly.
# Author: Tony DiCola
# License: Public Domain
from __future__ import division
import time

# Import the PCA9685 module.
import Adafruit_PCA9685


# Uncomment to enable debug output.
#import logging
#logging.basicConfig(level=logging.DEBUG)

# Initialise the PCA9685 using the default address (0x40).
#pwm = Adafruit_PCA9685.PCA9685()
pwm = Adafruit_PCA9685.PCA9685(address=0x40)

# Alternatively specify a different address and/or bus:
#pwm = Adafruit_PCA9685.PCA9685(address=0x41, busnum=2)

# Configure min and max servo pulse lengths
#servo_min = 150  # Min pulse length out of 4096
servo_min = 102 # 0.5(ms) * 4096 / 20(ms)
#servo_max = 600  # Max pulse length out of 4096
servo_max = 492  # 2.4(ms) * 4096 / 20(ms)

# Helper function to make setting a servo pulse width simpler.
def set_servo_pulse(channel, pulse):
    pulse_length = 1000000    # 1,000,000 us per second
    pulse_length //= 60       # 60 Hz
    print('{0}us per period'.format(pulse_length))
    pulse_length //= 4096     # 12 bits of resolution
    print('{0}us per bit'.format(pulse_length))
    pulse *= 1000
    pulse //= pulse_length
    pwm.set_pwm(channel, 0, pulse)

def set_degree(channel, degree):
    if degree > 180:
        degree = 180
    elif degree < 0:
        degree = 0

    print("入力値は{0}です".format(num))
    pulse = int((servo_max - servo_min)*degree/180+servo_min)
    pwm.set_pwm(channel, 0, pulse)

# Set frequency to 60hz, good for servos.
pwm.set_pwm_freq(50)

print('Moving servo on channel 0, press Ctrl-C to quit...')
while True:
    
    s = input()
    try:
        num = int(s)
    except ValueError:
        continue
        
#    print("入力値は{0}です".format(num))
#    if num > servo_max:
#        num = servo_max
#    elif num < servo_min:
#        num = servo_min
    
#    pwm.set_pwm(0, 0, num)
    set_degree(2, num)
    
    
    # Move servo on channel O between extremes.
    #pwm.set_pwm(0, 0, servo_min)
    #time.sleep(1)
    #pwm.set_pwm(0, 0, servo_max)
    #time.sleep(1)

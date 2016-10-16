# installation: https://github.com/IanHarvey/bluepy
# code from: http://ianharvey.github.io/bluepy-doc/notifications.html#example-code

from bluepy import *
import binascii
import time

class MyDelegate(btle.DefaultDelegate):
    def __init__(self, params):
        btle.DefaultDelegate.__init__(self)
        # ... initialise here

    def __init__(self):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        print data


# Initialisation  -------

try:
    p = btle.Peripheral( "98:4F:EE:0F:35:25" )
except btle.BTLEException:
    print "didn't connect"
p.setDelegate( MyDelegate() )

svc = p.getServiceByUUID( "f3156083-4b16-4e6e-87bd-bb2643d9eb8d" )          # device
ch1 = svc.getCharacteristics( "3c8f4751-149b-4d52-9f6b-d7767931d233" )[0]   # sensor 1
ch2 = svc.getCharacteristics( "0ba91872-7567-4d0a-8571-aae7c3ccfe61" )[0]   # sensor 2

# Main loop --------

while True:
    val1 = binascii.b2a_hex(ch1.read())
    print "sensor 1:", val1

    val2 = binascii.b2a_hex(ch2.read())
    print "sensor 2:", val2

    print

    """
    # I don't know what this does ... doesn't seem to be necessary :)
    if p.waitForNotifications(1.0):
        print "in waitForNotifications"
        continue
    """

    # loop rate (seconds)
    time.sleep(.5)

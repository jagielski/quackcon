# installation: https://github.com/IanHarvey/bluepy
# code from: http://ianharvey.github.io/bluepy-doc/notifications.html#example-code

from bluepy import *
import binascii

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
except BTLEException:
    print "didn't connect"
p.setDelegate( MyDelegate() )

# Setup to turn notifications on, e.g.
svc = p.getServiceByUUID( "f3156083-4b16-4e6e-87bd-bb2643d9eb8d" )
ch = svc.getCharacteristics( "3c8f4751-149b-4d52-9f6b-d7767931d233" )[0]
#ch.write( setup_data )

# Main loop --------

while True:
    val = binascii.b2a_hex(ch.read())
    #val = binascii.unhexlify(val)
    print val
    if p.waitForNotifications(1.0):
        print "in waitForNotifications"
        continue

    print "Waiting..."
    # Perhaps do something else here

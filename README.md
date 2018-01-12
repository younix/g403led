# g403led

Set the LED color of wheel and logo for Logitech gaming mouse.
This program is made for OpenBSD and don't use any portable API
like libusb nor libhid.

# Which logitech mouse is supported?

At the moment I've just tested "G403 Prodigy Gaming Mouse" but other
mouse devices of Logitech might also work.

# How to build this software?

The following commands should work on "every" OpenBSD system.

```
git clone https://github.com/younix/g403led
cd g403led
make
```

# Which /dev/uhid you have to use?

When the mouse attaches the following messages show up in dmesg(8):

```
uhidev0 at uhub3 port 1 configuration 1 interface 0 "Logitech G403 Prodigy Gaming Mouse" rev 2.00/8.01 addr 6
uhidev0: iclass 3/1
ums0 at uhidev0: 16 buttons, Z and W dir
wsmouse2 at ums0 mux 0
uhidev1 at uhub3 port 1 configuration 1 interface 1 "Logitech G403 Prodigy Gaming Mouse" rev 2.00/8.01 addr 6
uhidev1: iclass 3/0, 17 report ids
ukbd0 at uhidev1 reportid 1: 8 variable keys, 6 key codes
wskbd1 at ukbd0 mux 1
wskbd1: connecting to wsdisplay0
uhid0 at uhidev1 reportid 3: input=4, output=0, feature=0
uhid1 at uhidev1 reportid 4: input=1, output=0, feature=0
uhid2 at uhidev1 reportid 16: input=6, output=6, feature=0
uhid3 at uhidev1 reportid 17: input=19, output=19, feature=0
```

The last uhid (/dev/uhid3 in this case) seams to work for my device.
If you have other usbdevices attached or another device model this may vary.


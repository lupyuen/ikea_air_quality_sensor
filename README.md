# IKEA VINDRIKTNING Air Quality Sensor connected to LoRaWAN and The Things Network with Apache NuttX OS

(And visualised with Prometheus and Grafana)

Follow the updates on Twitter: https://twitter.com/MisterTechBlog/status/1490147828458405889

# Solder UART Port on IKEA Sensor

We expose the UART Port on IKEA Sensor by soldering these pads...

| UART Pin | IKEA Sensor | Wire Colour
|:---|:--:|:---
| UART Tx | REST | Blue
| GND | GND | Black

[(More details)](https://style.oversubstance.net/2021/08/diy-use-an-ikea-vindriktning-air-quality-sensor-in-home-assistant-with-esphome/)

# Test with Bus Pirate

Let's sniff the UART Port with Bus Pirate. Connect Bus Pirate to IKEA Sensor as follows...

| Bus Pirate | IKEA Sensor | Wire Colour
|:---|:--:|:---
| Data In (MISO) | REST | Blue
| GND | GND | Black

[(More about Bus Pirate interfacing with UART)](http://dangerousprototypes.com/docs/UART)

Enter these Bus Pirate commands to capture the UART output from IKEA Sensor...

```text
HiZ>m
1. HiZ
2. 1-WIRE
3. UART
4. I2C
5. SPI
6. 2WIRE
7. 3WIRE
8. KEYB
9. LCD
10. PIC
11. DIO
x. exit(without change)

(1)>3
Set serial port speed: (bps)
 1. 300
 2. 1200
 3. 2400
 4. 4800
 5. 9600
 6. 19200
 7. 38400
 8. 57600
 9. 115200
10. Input Custom BAUD
11. Auto-Baud Detection (Activity Required)

(1)>5
Data bits and parity:
 1. 8, NONE *default 
 2. 8, EVEN 
 3. 8, ODD 
 4. 9, NONE
(1)>
Stop bits:
 1. 1 *default
 2. 2
(1)>
Receive polarity:
 1. Idle 1 *default
 2. Idle 0
(1)>
Select output type:
 1. Open drain (H=Hi-Z, L=GND)
 2. Normal (H=3.3V, L=GND)

(1)>
Clutch disengaged!!!
To finish setup, start up the power supplies with command 'W'

Ready
UART>W
POWER SUPPLIES ON
Clutch engaged!!!
```

[Watch the demo on YouTube](https://youtu.be/QOJF6hAhFv4)

See below for the ASCII and Binary Logs.

## ASCII Log

ASCII Log of UART Output from IKEA Sensor...

[Watch the demo on YouTube](https://youtu.be/QOJF6hAhFv4)

```text
UART>(2)
Raw UART input
Any key to exit

<@:
   <B:
[6C:;8
[9C:;8
[12C9:7 
[16C997!
[20C987"
[24C876%
[28C876%
[32C876%
[36C866&
[40C856'
[44C745*
[48C745*
[52C745*
[56C745*
[60C735+
[64C614/
[68C614/
[72C614/
[76C614/
[79C
[37;80H 624.
[4C624.
[8C624.
[12C614/
[16C614/
[20C614/
[24C6040
[28C6040
[32C5/33
[36C5.34
[40C4,28
[44C4,28
[48C5-35
[52C5.34
[56C5.34
[60C5-35
[64C4,28
[68C2%0C
[72C2%0C
[76C2&0B
[79C
[37;80H 2'0A
[4C3)1=
[8C3*1<
[12C4+29
```

[(See the complete log)](https://gist.github.com/lupyuen/f40454dda8e3d7f279fb6ef721add465)

## Binary Log

Binary Log of UART Output from IKEA Sensor...

```text
UART>{
UART LIVE DISPLAY, } TO STOP
UART>
READ: -f 0x00
UART>
READ: -f 0x00
UART>
READ: -f 0x00
UART>
READ: 0x16
UART>
READ: 0x11
UART>
READ: 0x0B
UART>
READ: 0x00
UART>
READ: 0x00
UART>
READ: 0x00
UART>
READ: 0x3D
UART>
READ: 0x00
UART>
READ: 0x00
UART>
READ: 0x03
UART>
READ: 0x45
UART>
READ: 0x00
UART>
READ: 0x00
UART>
READ: 0x00
UART>
READ: 0x3B
UART>
READ: 0x01
UART>
READ: 0x00
UART>
READ: 0x00
UART>
```

[(See the complete log)](https://gist.github.com/lupyuen/db0c97b12bd1070e17cd2e570a5aa810)

[(Another binary log)](https://gist.github.com/lupyuen/ebe4c0628fc9ea2e124e6f00d8246b49)

# References

-   ["Use an IKEA VINDRIKTNING air quality sensor in Home Assistant with ESPHome"](https://style.oversubstance.net/2021/08/diy-use-an-ikea-vindriktning-air-quality-sensor-in-home-assistant-with-esphome/)

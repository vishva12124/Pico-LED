# **FRC 7902 WS2812 Controller Project** #
<br />
This program allows the RIO to control two WS2812 LED strips simultaneously using a Raspberry Pi Pico.<br />
<br />
A command is sent in this order (do not have any spaces in the input):<br />

**0,1,2,3,4,5**
<br />
<br />

**0: Strip to Control** (from 0 - 2)
<br />

**1: Brightness** (from 0 - 255)
<br />

**2: Mode** (from 1 - 6)
<br />

**3: R** (Red value)
<br />

**4: G** (Green value)
<br />

**5: B** (Blue value)
<br />
<br />

# **Modes**: #
1: **Static Lights**
<br />

2: **Strobing Lights**
<br />

3: **RGB Colourwave**
<br />

4: **Pulsing Lights**
<br />

5: **Pattern Lights** (I don't know what to properly call this one)<br />

<br />

# **System Information** #
<br />

Microcontroller:
- Raspberry Pi Pico (RP2040)
<br />

Language:
- C
<br />

External Libraries: 
- pico-sdk
- pico-extras
<br />

Hardware APIs Used:
- UART
- PIO
- IRQ
- Multicore
- Watchdog timer (to be implemented)
- ADC (to be implemented)

UART RX Pin
- GPIO 1
<br />

Strip 1 TX Pin:
- GPIO 2
<br />

Strip 2 TX Pin:
- GPIO 5
<br />

Baud rate:
- 1000
<br />


**Thank you Davis and Arjun for all your help :)**

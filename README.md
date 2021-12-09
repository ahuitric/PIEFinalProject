# Emotional Music Box Project

The code in this repository is used to read facial expressions from live webcam video to send to an Arduino that will use the expression to play a preprogrammed song on 15 servos.

## Installation

This project uses a Windows 10 computer with a webcam and an Arduino Uno that is plugged into the laptop with a USB-USBA cable. The Arduino is connected to a PCA9685 (library [here](https://learn.adafruit.com/16-channel-pwm-servo-driver/using-the-adafruit-library)) Adafruit PWM servo driver as fifteen servos are used to play notes on a music box. Note: Serial monitor cannot be open at the same time as running the python code.

Currently the code and its dependencies work on Windows 10, the following things will need to be installed:

```bash
pip install opencv
pip install opencv-contrib-python
pip install numpy
pip install deepface
```

## Usage

The laptopcam.py file runs facial recognition/emotion recognition and will send the information over serial to the arduino with music_box.ino running on it. The other arduino file music_ino is used to run the motor that spins the music box handle. If the arduino is not currently playing a song it will accept serial data from the laptop which will then display an image of the face it found along with dominant emotion data.

## Authors and acknowledgment

Author of the code: Alana Huitric. Electrical engineer: Isabella Abilheira. Mechanical engineers: Emily Wan and Maya Lum.

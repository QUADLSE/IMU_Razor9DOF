# Test for Razor 9DOF IMU
# Jose Julio @2009
# This script needs VPhyton, pyserial and pywin modules

# First Install Python 2.6.4
# Install pywin from http://sourceforge.net/projects/pywin32/
# Install pyserial from http://sourceforge.net/projects/pyserial/files/
# Install Vphyton from http://vpython.org/contents/download_windows.html

from visual import *
import serial
import string
import math
import struct

from time import time

grad2rad = 3.141592/180.0

# Check your COM port and baud rate
ser = serial.Serial(port='COM2',baudrate=250000, timeout=None)

# Main scene
scene=display(title="9DOF Razor IMU test")
scene.range=(1.2,1.2,1.2)
#scene.forward = (0,-1,-0.25)
scene.forward = (1,0,-0.25)
scene.up=(0,0,1)

# Second scene (Roll, Pitch, Yaw)
scene2 = display(title='9DOF Razor IMU test',x=0, y=0, width=500, height=200,center=(0,0,0), background=(0,0,0))
scene2.range=(1,1,1)
scene.width=500
scene.y=200

scene2.select()
#Roll, Pitch, Yaw
cil_roll = cylinder(pos=(-0.4,0,0),axis=(0.2,0,0),radius=0.01,color=color.red)
cil_roll2 = cylinder(pos=(-0.4,0,0),axis=(-0.2,0,0),radius=0.01,color=color.red)
cil_pitch = cylinder(pos=(0.1,0,0),axis=(0.2,0,0),radius=0.01,color=color.green)
cil_pitch2 = cylinder(pos=(0.1,0,0),axis=(-0.2,0,0),radius=0.01,color=color.green)
#cil_course = cylinder(pos=(0.6,0,0),axis=(0.2,0,0),radius=0.01,color=color.blue)
#cil_course2 = cylinder(pos=(0.6,0,0),axis=(-0.2,0,0),radius=0.01,color=color.blue)
arrow_course = arrow(pos=(0.6,0,0),color=color.cyan,axis=(-0.2,0,0), shaftwidth=0.02, fixedwidth=1)

#Roll,Pitch,Yaw labels
label(pos=(-0.4,0.3,0),text="Roll",box=0,opacity=0)
label(pos=(0.1,0.3,0),text="Pitch",box=0,opacity=0)
label(pos=(0.55,0.3,0),text="Yaw",box=0,opacity=0)
label(pos=(0.6,0.22,0),text="N",box=0,opacity=0,color=color.yellow)
label(pos=(0.6,-0.22,0),text="S",box=0,opacity=0,color=color.yellow)
label(pos=(0.38,0,0),text="W",box=0,opacity=0,color=color.yellow)
label(pos=(0.82,0,0),text="E",box=0,opacity=0,color=color.yellow)
label(pos=(0.75,0.15,0),height=7,text="NE",box=0,color=color.yellow)
label(pos=(0.45,0.15,0),height=7,text="NW",box=0,color=color.yellow)
label(pos=(0.75,-0.15,0),height=7,text="SE",box=0,color=color.yellow)
label(pos=(0.45,-0.15,0),height=7,text="SW",box=0,color=color.yellow)

L1 = label(pos=(-0.4,0.22,0),text="-",box=0,opacity=0)
L2 = label(pos=(0.1,0.22,0),text="-",box=0,opacity=0)
L3 = label(pos=(0.7,0.3,0),text="-",box=0,opacity=0)

# Main scene objects
scene.select()
# Reference axis (x,y,z)
arrow(color=color.green,axis=(1,0,0), shaftwidth=0.02, fixedwidth=1)
arrow(color=color.green,axis=(0,-1,0), shaftwidth=0.02 , fixedwidth=1)
arrow(color=color.green,axis=(0,0,-1), shaftwidth=0.02, fixedwidth=1)
# labels
label(pos=(0,0,0.8),text="9DOF Razor IMU test",box=0,opacity=0)
label(pos=(1,0,0),text="X",box=0,opacity=0)
label(pos=(0,-1,0),text="Y",box=0,opacity=0)
label(pos=(0,0,-1),text="Z",box=0,opacity=0)
# IMU object
platform = box(length=1, height=0.05, width=1, color=color.red)
p_line = box(length=1,height=0.08,width=0.1,color=color.yellow)
plat_arrow = arrow(color=color.green,axis=(1,0,0), shaftwidth=0.06, fixedwidth=1)

yawDeg=0
pitchDeg=0
rollDeg=0
omegazero=0
omegaone=0
omegatwo=0
time_loop=0
read=0

# Mando la configuracion
ser.write('1')
ser.write('\xFF')
ser.write('\x00')
ser.write('\x01')
ser.write('\x00')
ser.write('\xF1')
read = struct.unpack('B', ser.read(1))[0]
if(read==0xAA):
    print read
    #RESET
    ser.write('2')

    while 1:
        read = struct.unpack('B', ser.read(1))[0]
        if(read==0xAA):
            while 1:
                ser.write('0')
                read = struct.unpack('B', ser.read(1))[0]
                if read == 0xFF:
                    read=0
                    yawDeg = (struct.unpack('H', ser.read(2))[0]-20000)/100.0
                    pitchDeg = (struct.unpack('H', ser.read(2))[0]-20000)/100.0
                    rollDeg = (struct.unpack('H', ser.read(2))[0]-20000)/100.0
                    omegazero = (struct.unpack('H', ser.read(2))[0]-20000)/10.0
                    omegaone = (struct.unpack('H', ser.read(2))[0]-20000)/10.0
                    omegatwo = (struct.unpack('H', ser.read(2))[0]-20000)/10.0
                    read = struct.unpack('B', ser.read(1))[0]
                    if read == 0xF1:	
                        print 'y:',yawDeg,'p:',pitchDeg,'r:',rollDeg
                        roll = rollDeg*grad2rad
                        pitch = pitchDeg*grad2rad
                        yaw = yawDeg*grad2rad
                        axis=(cos(pitch)*cos(yaw),-cos(pitch)*sin(yaw),sin(pitch)) 
                        up=(sin(roll)*sin(yaw)+cos(roll)*sin(pitch)*cos(yaw),sin(roll)*cos(yaw)-cos(roll)*sin(pitch)*sin(yaw),-cos(roll)*cos(pitch))
                        platform.axis=axis
                        platform.up=up
                        platform.length=1.0
                        platform.width=0.65
                        plat_arrow.axis=axis
                        plat_arrow.up=up
                        plat_arrow.length=0.8
                        p_line.axis=axis
                        p_line.up=up
                        cil_roll.axis=(0.2*cos(roll),0.2*sin(roll),0)
                        cil_roll2.axis=(-0.2*cos(roll),-0.2*sin(roll),0)
                        cil_pitch.axis=(0.2*cos(pitch),0.2*sin(pitch),0)
                        cil_pitch2.axis=(-0.2*cos(pitch),-0.2*sin(pitch),0)
                        arrow_course.axis=(0.2*sin(yaw),0.2*cos(yaw),0)
                        L1.text = str(rollDeg)
                        L2.text = str(pitchDeg)
                        L3.text = str(yawDeg)
                    elif read != 0xF1:
                        print 'ERROR FOOTER'
            #print 'omegazero:',omegazero
            #print 'omegaone:',omegaone
            #print 'omegatwo:',omegatwo
            #print 'timer_loop:',time_loop
            #ser.flushInput()
                elif read != 0xF1:
                    print 'ERROR HEADER'
                read=0
    ser.close

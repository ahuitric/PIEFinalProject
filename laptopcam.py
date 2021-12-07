import cv2 # pip install opencv
#pip install opencv-contrib-python
import matplotlib.pyplot as plt #pip install numpy
from deepface import DeepFace #pip install deepface
#from serial_cmd import Serial_cmd #serial_cmd class is in folder
import serial
import time

arduino = serial.Serial(port='COM6', baudrate=115200, timeout=.1)

scale = 25
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)
xavg = []
xavg.append(250)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    frame = cv2.flip(frame,1)
    #cv2.imshow('frame', frame)

    #get the webcam size
    height, width, channels = frame.shape

    #prepare the crop
    centerX,centerY=int(height/2),int(width/2)
    radiusX,radiusY= int(scale*height/100),int(scale*width/100)

    minX,maxX=centerX-radiusX,centerX+radiusX
    minY,maxY=centerY-radiusY,centerY+radiusY

    cropped = frame[minX:maxX, minY:maxY]
    resized_cropped = cv2.resize(cropped, (width, height))

    if cv2.waitKey(1) == 27:
        break

    faces = face_cascade.detectMultiScale(frame, scaleFactor=1.2, minSize=(20, 20))
    X = 0
    Y = 0
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 255), 1)
        X = x
        Y = y


    # Predict emotion using deepface library
    predictions = DeepFace.analyze(frame,  enforce_detection = False)
    text = predictions['dominant_emotion'] #highest emotional value

    # Add text to show dominant emotion to frame
    coordinates = (X,Y)
    font = cv2.FONT_HERSHEY_SIMPLEX
    fontScale = 1
    color = (255,0,255)
    thickness = 1
    image = cv2.putText(frame, text, coordinates, font, fontScale, color, thickness, cv2.LINE_AA)
    
    emotion_value = 8
    if text == 'neutral':
        emotion_value = 1
    elif text == 'happy':
        emotion_value = 2
    elif text == 'sad':
        emotion_value = 3
    elif text == 'angry':
        emotion_value = 4
    elif text == 'fear':
        emotion_value = 5
    elif text == 'surprise':
        emotion_value = 6
    elif text == 'disgust':
        emotion_value = 7

    
    arduino_data = arduino.readline()
    arduino_string = arduino_data.decode("utf-8")
    
    if "Seeking" in arduino_string:
        print("emotion value")
        print(f'emotion value: {emotion_value}')
        arduino.write(str(emotion_value).encode("utf-8"))
        #Display in imshow
        cv2.imshow('Camera', image)
        if cv2.waitKey(1) & 0xFF == 27:
            break
    else:
        print("arduino stuff:")
        arduino_data = arduino.readline()
        arduino_string = arduino_data.decode("utf-8")
        print(arduino_string)



# When everything done, release the capture

cap.release()
cv2.destroyAllWindows()

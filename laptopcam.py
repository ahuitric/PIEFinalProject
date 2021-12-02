import cv2 #-m pip install --no-cache-dir opencv-python
import matplotlib.pyplot as plt #pip install numpy
from deepface import DeepFace #pip install deepface

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

    #Display in imshow
    cv2.imshow('Camera', image)
    if cv2.waitKey(1) & 0xFF == 27:
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

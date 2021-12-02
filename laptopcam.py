import cv2
import matplotlib.pyplot as plt
from deepface import DeepFace

scale = 25
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

img = cv2.imread('alanaface.png')
#cv2.imshow("le huitric", img)

cv2.waitKey(0)
predictions = DeepFace.analyze(img)
print(str(predictions))

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

    #print(xavg)
    if ((sum(xavg)/len(xavg)) <= 40):
        #print('TURN LEFT')
        scale = 500
    elif ((sum(xavg)/len(xavg)) >= 350):
        #print('TURN RIGHT')
        scale = 500
    else:
        scale = 25

    faces = face_cascade.detectMultiScale(frame, scaleFactor=1.2, minSize=(20, 20))
    for (x, y, w, h) in faces:
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 255), 10)

        if (len(xavg) > 10):
            xavg = xavg[1:]
        xavg.append(x)

        # Display the resulting frame
        #cv2.imshow('frame', frame)

    gray = cv2.medianBlur(cv2.cvtColor(cap.read()[1], cv2.COLOR_BGR2GRAY),5)
    gray = cv2.flip(gray,1)
    circle = cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 10)# ret=[[Xpos,Ypos,Radius],...]
    res = str(circle)
    coords = res.split(' ')
    if (len(coords) > 1):
        print('X: ' + str(coords[0][3:]) + '; Y: ' + str(coords[1]))
    circle = None
    #cv2.imshow('video',gray)
    if cv2.waitKey(1)==27:# esc Key
        break

    predictions = DeepFace.analyze(frame,  enforce_detection = False)
    text = predictions['dominant_emotion']
    coordinates = (100,100)
    font = cv2.FONT_HERSHEY_SIMPLEX
    fontScale = 1
    color = (255,0,255)
    thickness = 2
    image = cv2.putText(frame, text, coordinates, font, fontScale, color, thickness, cv2.LINE_AA)
    cv2.imshow('Camera', image)
    if cv2.waitKey(1) & 0xFF == 27:
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

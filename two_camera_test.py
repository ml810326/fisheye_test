import numpy as np
import cv2

cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
cap2 = cv2.VideoCapture(1)
cap2.set(3,640)
cap2.set(4,480)

while(True):
	ret, frame = cap.read()
	ret2, frame2 = cap2.read()
	
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	gray2 = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)

	cv2.imshow('left', gray)
	cv2.imshow('right', gray2)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

cap.release()
cap2.release()
cv2.destroyAllWindows()

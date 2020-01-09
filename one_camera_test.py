import numpy as np
import cv2

cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
num=1
while(True):
	ret, frame = cap.read()
	
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

	cv2.imshow('left', gray)
	if cv2.waitKey(1) & 0xFF == ord('s'):
		cv2.imwrite('pic'+str(num)+'.jpg',gray)
		print( "save image pic"+str(num)+".jpg")
		num = num + 1
	if cv2.waitKey(10) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()

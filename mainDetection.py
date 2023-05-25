from ultralytics import YOLO
import cv2
import cvzone
import math

#'http://10.0.233.107:4747/video'
cap = cv2.VideoCapture(0)
cap.set(3,1280)
cap.set(4,720)

model = YOLO("../yolov8n.pt")

classNames = ["person"]

while True:
    success, img = cap.read()
    results = model(img, stream=True)
    for r in results:
        boxes = r.boxes
        for box in boxes:
            cls = int(box.cls[0])
            if (cls == 0):
                x1,y1,x2,y2 = box.xyxy[0]
                x1,y1,x2,y2 = int(x1),int(y1),int(x2),int(y2)
                val = ((x2+x1)//2)

                if (val < 480):
                    print("l")
                elif (val > 800):
                    print("r")
                else:
                    print("f")
            else:
                print("n")

            # w,h = x2-x1,y2-y1
            # bbox = int(x1),int(y1),int(w),int(h)
            # cvzone.cornerRect(img,(x1,y1,w,h))

                # conf = math.ceil(box.conf[0]*100)/100


                # cvzone.putTextRect(img,f'{cls} {conf}',(max(0,x1),max(35,y1)))


    cv2.imshow("Image",img)
    cv2.waitKey(1)

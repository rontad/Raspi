#!/usr/bin/env python
# -*- coding: utf-8 -*-

#OpenCVで顔認識し、SG90 2台を使用して認識した方向にカメラを移動するサンプルコード

#OpenCVの顔認識のコードは以下のサイトのものを使用させていただきました。
#https://kokensha.xyz/raspberry-pi/raspberry-pi-opencv-video-face-detection/
#PCA9685はAdafruit_PCA9685ライブラリ内のサンプルを使用させていいただきました。

from __future__ import division
# Import the PCA9685 module.
import Adafruit_PCA9685

from picamera.array import PiRGBArray
from picamera import PiCamera
import cv2, time

# フレームサイズ
FRAME_W = 320
FRAME_H = 192

class myPCA9685:

    def __init__(self,channel):
        self.channel = channel
        # Initialise the PCA9685 using the default address (0x40).
        self.pwm = Adafruit_PCA9685.PCA9685(address=0x40)
        # Set frequency to 60hz, good for servos.
        self.pwm.set_pwm_freq(50)
        self.servo_min = 102  # 0.5(ms) * 4096 / 20(ms) #Min pulse length out of 4096
        self.servo_max = 492  # 2.4(ms) * 4096 / 20(ms)

    def angleToPulse(self,angle):
        return int((self.servo_max - self.servo_min)*angle/180+self.servo_min)

    # パルス指定での移動
    def move2Target(self,pulse):
        if pulse < self.servo_min:
            pulse = self.servo_min
        elif pulse > self.servo_max:
            pulse = self.servo_max

        self.pulse = pulse
        print("チャネル{0}の入力値は{1}です".format(self.channel,self.pulse))
        self.pwm.set_pwm(self.channel, 0, self.pulse)

    # 指定パルスだけ現在地から移動
    def moveDegree(self,pulse):
        self.move2Target(self.pulse + pulse)

    # 角度指定で移動
    def move2Angle(self,angle):
        self.move2Target(self.angleToPulse(angle))


# 正面の顔検出用
cascPath = '/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml'
faceCascade = cv2.CascadeClassifier(cascPath)

camera = PiCamera()
camera.resolution = (FRAME_W, FRAME_H)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(FRAME_W, FRAME_H))
time.sleep(0.1)

c_servoX = myPCA9685(0)
c_servoY = myPCA9685(2)
#サーボを初期位置に移動
c_servoX.move2Angle(90)
c_servoY.move2Angle(90)


found = False
prevTime = time.time()

for image in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):


    frame = image.array
    # frame = cv2.flip(frame, -1) # 上下反転する場合

    # Convert to greyscale for detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.equalizeHist( gray )

    # 顔検出
    faces = faceCascade.detectMultiScale(gray, 1.1, 3, 0, (10, 10))

    # 検出した顔に枠を書く
    for (x, y, w, h) in faces:
        # 見つかった顔を矩形で囲む
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)
        #print(str(x)+","+str(y)+","+str(w)+","+str(h)+",")
        
        #顔の中心座標
        if found == False:
            print("x:"+str(x)+",y:"+str(y)+",w:"+str(w)+",h"+str(h)+",中心(横):"+str(x+w/2)+",中心(縦)"+str(y+h/2))
            centerX = x+w/2
            centerY = y+h/2
            found = True

    frame = cv2.resize(frame, (540,300))

    # ビデオに表示 
    cv2.imshow('Video', frame)
    key = cv2.waitKey(1) & 0xFF

    rawCapture.truncate(0)

    #0.1秒ごとにサーボに指示
    if time.time() - prevTime >= 0.05:
        #顔検知していたらサーボの角度調整
        if found == True:
            #中心座標からずれていたら、ずれている方向にサーボを動かす

            #X軸 (左端0～右端180)
            if centerX > 160 + 20 :
                c_servoX.moveDegree(-2)
            elif centerX < 160 - 20:
                c_servoX.moveDegree(2)

            #Y軸 (下端0～上端180)
            if centerY > 96 + 20 :
                c_servoY.moveDegree(2)
            elif centerY < 96 - 20:
                c_servoY.moveDegree(-2)

            found=False
  
        prevTime = time.time()

    if key == ord("q"):
        break

cv2.destroyAllWindows()

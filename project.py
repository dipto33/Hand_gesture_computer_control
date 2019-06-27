import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui

ArduinoSerial = serial.Serial('com8',9600) #Create Serial port object called arduinoSerialData
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and print it as line
    print incoming

    if 'Leftclicked' in incoming:
        pyautogui.click() 
    
    if 'Rightclicked' in incoming:
        pyautogui.click(button='right') 
    
    if 'Play/Pause' in incoming:
        pyautogui.typewrite(['space'], 0.2)

    if 'Backward' in incoming:
        #pyautogui.hotkey('ctrl', 'left')
        pyautogui.press('left')

    if 'Forward' in incoming:
        #pyautogui.hotkey('ctrl', 'right')
        pyautogui.press('right')

    if 'Vup' in incoming:
        pyautogui.press('up')
        

    if 'Vdown' in incoming:
        pyautogui.press('down')

    incoming = "";

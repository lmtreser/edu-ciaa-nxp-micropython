import pyb

lcd = pyb.LCD(2,0) # 2 lines, dot format:5x8
lcd.clear()

lcd.write("Test LCD\nEDUCIAA")
pyb.delay(1000)

lcd.clear()
lcd.config_cursor(True,True) #Cursor ON, Blink ON

c=0

while(True):
    c=c+1   
    lcd.goto_xy(0,0)
    lcd.write("counter:"+str(c))        
    lcd.goto_xy(10,1)
    lcd.write(str(c))
    pyb.delay(1000)
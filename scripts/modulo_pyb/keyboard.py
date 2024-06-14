import pyb

keyboard = pyb.Keyboard(4,4) #4 rows, 4 columns
print(keyboard)

while True:
  key = keyboard.get_char()
  print("key:"+str(key))
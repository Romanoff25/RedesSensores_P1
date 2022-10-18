
#%%# Librerias
import serial


#%%#Inicializar Serial
ser = serial.Serial('COM3')
ser.baudrate = 115200

#%%# Create header
#    with open(r'.\test\log.csv','a') as f:
#       f.write(ser.readline().decode())

#%%# Escribir en el ".txt"
while(1):
    with open(r'.\test\log.csv','a') as f:
        f.write(ser.readline().decode())


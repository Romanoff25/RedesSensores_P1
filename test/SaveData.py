
#%%# Librerias
import serial
from os.path import exists
#from io import StringIO
#import pandas as pd

#%%# Define
path = r'C:\Users\usuario\OneDrive\Documentos\PlatformIO\Projects\RedesSensores_P1\test\log.csv'

#%%#Inicializar Serial
ser = serial.Serial('COM3')
ser.baudrate = 115200

#%%# Create header
if(not(exists(path))):
    with open(path,'x') as f:
        f.write("axis,d0,d1,d2,d3,d4,d5,d6,d7,d8,d9\n")

#%%# Escribir en el ".txt"
while(1):
    with open(path,'a') as f:
        f.write(ser.readline().decode())


'''
# %%
df = pd.read_csv(StringIO(ser.readline().decode()), sep=";")
# %%
print(df)

#%%
print()
'''
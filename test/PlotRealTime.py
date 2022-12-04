#%%# Librerias
import serial
from os.path import exists
import time
import pandas as pd
from csv import reader
import matplotlib.pyplot as plt

import warnings
warnings.simplefilter(action='ignore', category=FutureWarning)



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
it_0 = time.time()
it = 5 
x_vals = []
y_vals = []
a0= []
a1= []
a2=  []
while(1):
    with open(path,'a') as f:
        data=ser.readline().decode()
        f.write(data)

        if(it_0 + it <  time.time()):
            q= pd.read_csv(path).tail(15)
            q0=q[q.iloc[:,0]=='0']
            q1=q[q.iloc[:,0]=='1']
            q2=q[q.iloc[:,0]=='2']
            del q0['axis']
            del q1['axis']
            del q2['axis']
            
            a0.append(q0.mean().mean());
            a1.append(q1.mean().mean());
            a2.append(q2.mean().mean());


            x_vals.append(it-5)
            it = it+5

            for y_vals in [a0, a1, a2]:
                plt.plot(x_vals,y_vals)
            plt.show()




# %%

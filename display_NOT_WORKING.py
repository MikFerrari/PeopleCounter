import serial
import time
from tkinter import *


def readData(baudRate,ser):
    
    '''
    try:
        while True:
            data = ser.readline()
            str_data = data.decode()
            str_final = str_data.rstrip()
            if str_final != '':
                number = int(str_final)
                print(number)

    finally:
        ser.close()
    '''

    try:
        data = ser.readline()
        str_data = data.decode()
        str_final = str_data.rstrip()
        if str_final != '':
            number = int(str_final)
            print(number)
            return number

    finally:
        ser.close()


def main():
     
    baudRate = 9600
    serPort = 'COM3'
    ser = serial.Serial('COM3',baudRate)

    ## Window creation
    window = Tk()
    window.title('People Counter App')
    window.geometry("1280x720")

    try:
        while True:
            ## Serial port reading
            count = readData(baudRate,ser)

            ## Graphics updating
            count_char_height = 300
            text_char_height = 75

            if count > 0:
                window.configure(background='lawn green')
                label1 = Label(window, text=str(count), font=("Arial", count_char_height), bg='lawn green').place(relx=0.5, rely=0.6, anchor=CENTER)
                label2 = Label(window, text='Numero posti disponibili', font=("Arial", text_char_height), bg='lawn green').place(relx=0.5, rely=0.20, anchor=CENTER)
            else:
                window.configure(background='orangered')
                label2 = Label(window, text='Numero posti disponibili', font=("Arial", text_char_height), bg='orangered').place(relx=0.5, rely=0.20, anchor=CENTER)
                label1 = Label(window, text=str(count), font=("Arial", count_char_height), bg='orangered').place(relx=0.5, rely=0.5, anchor=CENTER)
                label3 = Label(window, text='Numero massimo raggiunto!', font=("Arial", text_char_height), bg='orangered').place(relx=0.5, rely=0.90, anchor=CENTER)
                
            ## Window updating
            window.update_idletasks()
            window.update()
            time.sleep(30)

    except:
        pass


if __name__ == "__main__":
    main()
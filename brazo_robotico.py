import serial
import time
import pyodbc
from datetime import datetime

# Configura la conexión serial con el Arduino
ser = serial.Serial('COM3', 9600)  # Cambia 'COM3' al puerto serial correcto
time.sleep(2)  # Espera a que la conexión serial se establezca

# Configura la conexión a SQL Server
conn = pyodbc.connect(driver='{ODBC Driver 17 for SQL Server}',
                      server=r'LAPTOP-JNOVSIJ2\SQLEXPRESS',
                      user='grupobdb',
                      password='grupobdb',
                      database='BrazoRobotico')
cursor = conn.cursor()

def enviar_angulos(angles):
    if len(angles) == 6:
        data = ','.join(map(str, angles)) + '\n'
        ser.write(data.encode())
        print(f"Enviado: {data.strip()}")

        # Almacenar datos en la base de datos
        timestamp = datetime.now()
        movimiento_id = 1  # ID de la secuencia de movimientos, ajustar según tu base de datos

        for servo_id, angulo in enumerate(angles, start=1):  # Cambié start=2 a start=1 para que sea más lógico
            cursor.execute("""
                INSERT INTO movimientos (servo_id, angulo, timestamp, movimiento_id) 
                VALUES (?, ?, ?, ?)
            """, (servo_id, angulo, timestamp, movimiento_id))
            conn.commit()
            print(f"Almacenado en la base de datos: Servo {servo_id}, Ángulo {angulo}")

# Ejemplo de cómo enviar ángulos y almacenarlos en la base de datos
enviar_angulos([90, 45, 120, 60, 90, 30])

try:
    while True:
        # Puedes implementar una interfaz aquí para recibir ángulos del usuario
        input_angles = input("Introduce los ángulos (ej. 90,45,120,60,90,30): ").strip()
        angles = list(map(int, input_angles.split(',')))
        enviar_angulos(angles)
except KeyboardInterrupt:
    print("Interrupción por teclado")
finally:
    ser.close()
    conn.close()

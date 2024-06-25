CREATE DATABASE BrazoRobotico;
GO
USE BrazoRobotico;
GO
CREATE TABLE servos (
    id INT PRIMARY KEY IDENTITY(1,1),
    nombre VARCHAR(255) NOT NULL,
    pin INT NOT NULL
);
GO
CREATE TABLE secuencia_movimientos (
    id INT PRIMARY KEY IDENTITY(1,1),
    nombre_secuencia VARCHAR(255) NOT NULL,
    descripcion TEXT,
    fecha_creacion DATETIME DEFAULT GETDATE()
);
GO
CREATE TABLE movimientos (
    id INT PRIMARY KEY IDENTITY(1,1),
    servo_id INT,
    angulo INT,
    timestamp DATETIME DEFAULT GETDATE(),
    movimiento_id INT,
    FOREIGN KEY (servo_id) REFERENCES servos(id),
    FOREIGN KEY (movimiento_id) REFERENCES secuencia_movimientos(id)
);
GO
INSERT INTO servos (nombre, pin) VALUES ('Servo 1', 2);
INSERT INTO servos (nombre, pin) VALUES ('Servo 2', 3);
INSERT INTO servos (nombre, pin) VALUES ('Servo 3', 4);
INSERT INTO servos (nombre, pin) VALUES ('Servo 4', 5);
INSERT INTO servos (nombre, pin) VALUES ('Servo 5', 6);
INSERT INTO servos (nombre, pin) VALUES ('Servo 6', 7);
INSERT INTO servos (nombre, pin) VALUES ('Servo 7', 8);
GO
INSERT INTO secuencia_movimientos (nombre_secuencia, descripcion) 
VALUES ('Pick and Place', 'Secuencia para recoger y colocar un objeto');
GO


[top]
components : dispositivo motor@Motor
in : deteccion_in
out : estado_puerta_out
%Conexiones del Top
Link : deteccion_in objdetectado_in@dispositivo
Link : orden@dispositivo orden@motor
Link : abrir_cerrar@motor estado_puerta_out

[dispositivo]
components : sensor@Sensor uc@UC
in : objdetectado_in
out : orden
%Conexiones del Dispositivo
Link : objdetectado_in deteccion@sensor
Link : aviso_deteccion@sensor aviso_deteccion@uc
Link : consulta@uc consulta@sensor
Link : orden@uc orden
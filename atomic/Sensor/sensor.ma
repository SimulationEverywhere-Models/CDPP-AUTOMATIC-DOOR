[top]
components : sensor@Sensor
in : objdetectado_in
in : consultar_in
out : aviso_out
%Conexiones del Top con el Sensor
Link : objdetectado_in deteccion@sensor
Link : consultar_in consulta@sensor
Link : aviso_deteccion@sensor aviso_out
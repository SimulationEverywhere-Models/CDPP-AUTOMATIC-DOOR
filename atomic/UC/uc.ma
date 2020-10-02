[top]
components : uc@UC
in : aviso_in
out : consulta_out
out : orden_out
%Conexiones del Top con la UC
Link : aviso_in aviso_deteccion@uc
Link : consulta@uc consulta_out
Link : orden@uc orden_out
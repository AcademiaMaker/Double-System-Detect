/* Estados Picker */
int contador_Picker;
bool estado_SensorOptico;
int estado_SensorDistancia;

/* Contadores Rutinas */
int miskpick;
int Long;
int early_double;

/* Sensores */
int sensor_Opticos = 1;
int sensor_Distancia = 2;

/* Salida de Motores */ 
int motor_picker = 3;
void setup()
{
	pinMode(sensor_Opticos, INPUT);
    pinMode(sensor_Distancia, INPUT);

    pinMode(motor_picker, OUTPUT);
}

void loop()
{   
    lectura_sensores();
    if (estado_SensorOptico == false)
    {
        if (estado_SensorDistancia <= 0)
        {
            motores_activos_feedshaft(estado_SensorOptico);
        }
        
    }
    
}

void lectura_sensores(){
    estado_SensorOptico = digitalRead(sensor_Opticos);
    estado_SensorDistancia = analogRead(sensor_Distancia);
}

void motores_activos_feedshaft(bool SensorOptico){
    bool estado_grosor;
    bool estado_largo;
    while (SensorOptico == false)
    {
        motor_picker = HIGH;
        lectura_sensores();
        estado_grosor = validacion_grosor_billetes(estado_SensorDistancia);
        estado_largo = validacion_largo_billetes(estado_SensorDistancia);
        SensorOptico = estado_SensorOptico;
    }
    motor_picker = LOW;
    condicionales_Funcionamiento(estado_grosor, estado_largo);
        
}


bool validacion_grosor_billetes(int grosor_billetes){
    bool estado;
    if (grosor_billetes <= 5 )
    {
        estado = true;
    }
    if (grosor_billetes >= 5)
    {
        estado = false;
    }
    
    return estado;
}

bool validacion_largo_billetes(int largo_billetes){
    bool estado;
    int estado_sensor;
    bool conversion;
    int contador;

    if (largo_billetes > 0)
    {
        conversion = true;
    }
    while (conversion == true)
    {
        contador = +1;
        lectura_sensores();
        estado_sensor = estado_SensorDistancia;
        if (estado_sensor <= 0)
        {
            conversion = false;
        } 
    }
    
    if (contador >= 5 and contador <= 7) 
    {
        estado = true;
    }
    else
    {
        estado = false;
    }
    return estado;
}

void condicionales_Funcionamiento(bool estado_grosor, bool estado_largo){
    if (estado_grosor == true and estado_largo == true)
    {
        contador_Picker = contador_Picker + 1;
    }
    if (estado_grosor == true and estado_largo == false)
    {
        contador_Picker = contador_Picker;
        Long = +1;
    }
    if (estado_grosor == false and estado_largo == true)
    {
        contador_Picker = contador_Picker;
        early_double = +1;
        miskpick = +1;
    }
    if (estado_grosor == false and estado_largo == false)
    {
        contador_Picker = contador_Picker;
        early_double = +1;
        miskpick = +1;
        Long = +1;
    }
    printf("Miskpick ", miskpick);
    printf("Early Double ", early_double);
    printf("Long ", Long);
    
}

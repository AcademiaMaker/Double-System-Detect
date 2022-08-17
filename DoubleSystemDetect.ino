/*
    Desarrollando la version V. 1.1
    Sistemas de doble deteccion para dispensadores de ATM
    Funcionamiento de un picker
*/
// Constantes de Entrada de Sensores
#define sensorDistancia 1
#define sensorOptico 2

//  Constantes de salida de Actuadores
#define motorSteep 3

//  Lecturas de Sensores leidos
int Distancia;
bool Optico;

// Estados de Validacion
int estado_validacion1;
bool estado_validacion2;

void setup(){

    pinMode(sensorDistancia, INPUT);
    pinMode(sensorOptico, INPUT);

    pinMode(motorSteep, OUTPUT);
}
void loop(){
    lectura_Sensores();
    feedShaft(Distancia, Optico);
    validacion_grosor(Distancia, Optico);
    validacion_alto(Distancia);
}

//  Se crearon las funciones para la rutina automatica del picker del dispensador del ATM
void lectura_Sensores(){
    Distancia = analogRead(sensorDistancia);
    Optico = digitalRead(sensorOptico);
}

void feedShaft(int DistanciaFS, bool OpticoFS){
    if (OpticoFS == !Optico)
    {
        while (DistanciaFS <= 0)
        {
            digitalWrite(motorSteep, HIGH);
            delayMicroseconds(5);
            lectura_Sensores();
            DistanciaFS = Distancia;

        }
        lectura_Sensores();

        if (DistanciaFS > 0 and Optico == false)
        {
            
        }
                
    }  
    digitalWrite(motorSteep, LOW);
    
}
//Sistema de validacion de grosor del Billete, si estas no se cumplen se suman a las rutinas de comportamiento
int validacion_grosor(int DistanciaVG, int OpticoVG){
    int estado_Rutina;
    if (DistanciaVG > 3 and DistanciaVG < 5)
    {
        estado_Rutina = 1;
    }
    else if (DistanciaVG > 5)
    {
        estado_Rutina = 2;
    }
    else if (DistanciaVG <= 0 and OpticoVG == true)
    {
        estado_Rutina = 3;
    }
    
    return estado_Rutina;
}

int validacion_alto(int DistanciaVA){
    static long tiempo;
    int valor_ideal = 64;
    int estado_Rutina;
    if (DistanciaVA > 0){
        tiempo = micros();
        if (DistanciaVA <= 0 and tiempo == valor_ideal)
        {
            estado_Rutina = 1;
        }
    }   

}
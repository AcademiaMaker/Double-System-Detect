/*
    Desarrollando la version V. 1.2
    Trabajando en rama Dev
    Sistema de Doble Detencion, en esta version se desarrollo y programo el uso
    de librerias multihilo para microcontroladores mononucleo con poca memoria
    RAM,
    Funcionamiento de un picker
*/

// Librerias
#include <pt.h>
struct pt thread_1;
struct pt thread_2;

// Constantes de Entrada de Sensores
#define sensorDistanceMatrix 1
#define sensorFeedShaft 2

//  Constantes de actuadores
#define motorPicker_1 6
#define motorPicker_2 7
#define motorPicker_3 8
#define motorPicker_4 9

static long timeExtraction = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(sensorDistanceMatrix, INPUT);
    pinMode(sensorFeedShaft, INPUT);
    pinMode(motorPicker_1, OUTPUT);

    PT_INIT(&thread_1);
    PT_INIT(&thread_2);
}
void loop()
{
    meditionMatrixLong(&thread_1);
    extractionnFeedShaft(&thread_2);
}

void extractionnFeedShaft(struct pt *pt)
{
    PT_BEGIN(pt)
    do
    {
        timeExtraction = 0;
        if (digitalRead(sensorFeedShaft) == true)
        {
            timeExtraction = millis();
            digitalWrite(motorPicker_1, HIGH);
            while (digitalRead(sensorFeedShaft) == false)
            {
                Serial.println("Motor Picker Extracting");
                Serial.println("Extraction time = " + timeExtraction);
            }
            digitalWrite(motorPicker_1, LOW);
        }
        else
        {
            homePositionFeedShaft();
        }
    } while (true);
    PT_END(pt);
}

void homePositionFeedShaft()
{
    digitalWrite(motorPicker_1, HIGH);
    while (digitalRead(sensorFeedShaft) == false)
    {
        Serial.println("Motor Picker move position home");
    }
    digitalWrite(motorPicker_1, LOW);
}

void meditionMatrixLong(struct pt *pt)
{
    PT_BEGIN(pt)
    do
    {
        float readHallSensor;
        readHallSensor = digitalRead(sensorDistanceMatrix);
        if ((readHallSensor > 0 && readHallSensor < 100) && (millis() - timeExtraction < 1000))
        {
            while (digitalRead(sensorDistanceMatrix) > 0 && digitalRead(sensorDistanceMatrix) < 100)
            {
                Serial.println("Weith note ok");
            }
            Serial.println("Note finished");
        }
    } while (true);
    PT_END(pt);
}
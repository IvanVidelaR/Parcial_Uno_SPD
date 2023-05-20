// C++ code
// Parcial 1 Sistema de Procesamiento de Datos
// Parte Práctica Domiciliaria
// Videla Ribodino Iván Agustín
// Div "D"
// Se nos pide armar un modelo de montacarga funcional como maqueta para un hospital. El
// objetivo es que implementes un sistema que pueda recibir ordenes de subir, bajar o pausar
// desde diferentes pisos y muestre el estado actual del montacargas en el display 7
// segmentos.

#define LED_ROJO 12
#define LED_VERDE 11
#define LED_A 10
#define LED_B 9
#define LED_C 8
#define LED_D 7
#define LED_E 6
#define LED_F 5
#define LED_G 4
#define PULSADOR_SUBIR A0
#define PULSADOR_PAUSAR A1
#define PULSADOR_BAJAR A2

int piso = 0;
bool sistemaPausado = true;
bool sistemaSubiendo = false;
bool sistemaBajando = false;
bool ledRojoPrendido = false;
bool ledVerdePrendido = false;

void setup()
{
    pinMode(LED_ROJO, OUTPUT);
    pinMode(LED_VERDE, OUTPUT);
    pinMode(PULSADOR_SUBIR, INPUT);
    pinMode(PULSADOR_PAUSAR, INPUT);  
    pinMode(PULSADOR_BAJAR, INPUT);
    pinMode(LED_A, OUTPUT);
    pinMode(LED_B, OUTPUT);
    pinMode(LED_C, OUTPUT);
    pinMode(LED_D, OUTPUT);
    pinMode(LED_E, OUTPUT);
    pinMode(LED_F, OUTPUT);
    pinMode(LED_G, OUTPUT);
    Serial.begin(9600);
}

void loop()
{   
    if(sistemaPausado == true)
    {
        prenderLed(LED_ROJO);
        apagarLed(LED_VERDE);
    }
    else
    {
        subirBajarPisos();
        if(sistemaPausado == false)
        {
            prenderLed(LED_VERDE);
            apagarLed(LED_ROJO);
        }
    }
    
    Serial.print("Esta en el piso: ");
    mostrarPisoVisualizador(piso);
    
    permitirCambioPisosPorTiempo(3000);
}

void cambiarEstadoMontacargas()
{
    int estadoPulsadorSubir = digitalRead(PULSADOR_SUBIR); 
    int estadoPulsadorBajar = digitalRead(PULSADOR_BAJAR); 
    int estadoPulsadorPausar = digitalRead(PULSADOR_PAUSAR);
    
    if(estadoPulsadorPausar == HIGH)
    {
        if(sistemaPausado == false)
        {
            Serial.println("MONTACARGAS PAUSADO");
        }
        sistemaSubiendo = false;
        sistemaBajando = false;
        sistemaPausado = true;
    }
    else
    {
        if(estadoPulsadorSubir == HIGH)
        {
            if(sistemaSubiendo == false)
            {
                Serial.println("MONTACARGAS SUBIENDO");
            }
            sistemaPausado = false;
            sistemaBajando = false;
            sistemaSubiendo = true;
        }
        else
        {
            if(estadoPulsadorBajar == HIGH)
            {
                if(sistemaBajando == false)
                {
                    Serial.println("MONTACARGAS BAJANDO");
                }
                sistemaPausado = false;
                sistemaSubiendo = false;
                sistemaBajando = true;
            }
        }
    }
}

void subirBajarPisos()
{
    if(sistemaSubiendo == true and piso != 9)
    {
        piso++;
    }
    else
    {
        if(sistemaBajando == true and piso != 0)
        {
            piso--;
        }
        else
        {
            sistemaPausado = true;
            Serial.println("MONTACARGAS PAUSADO");
        }
    }
}

void permitirCambioPisosPorTiempo(int tiempo)
{
    for(int i = 0; i < tiempo; i+=50)
    {
        delay(50);
        cambiarEstadoMontacargas();
    }
}

void prenderLed(int led)
{
    switch(led)
    {
        case LED_ROJO:
            if(ledRojoPrendido == false)
            {
                Serial.println("Led Rojo prendido");
                ledRojoPrendido = true;
                digitalWrite(led, HIGH);
            }
        break;
        case LED_VERDE:
            if(ledVerdePrendido == false)
            {
                Serial.println("Led Verde prendido");
                ledVerdePrendido = true;
                digitalWrite(led, HIGH);
            }
        break;
    }
}

void apagarLed(int led)
{
    switch(led)
    {
        case LED_ROJO:
            if(ledRojoPrendido == true)
            {
                Serial.println("Led Rojo apagado");
                ledRojoPrendido = false;
                digitalWrite(led, LOW);
            }
        break;
        case LED_VERDE:
            if(ledVerdePrendido == true)
            {
                Serial.println("Led Verde apagado");
                ledVerdePrendido = false;
                digitalWrite(led, LOW);
            }
        break;
    }
}

void encenderOApagarLedsSieteSegmentos(int a, int b, int c, int d, int e, int f, int g)
{
    digitalWrite(LED_A, a);
    digitalWrite(LED_B, b);
    digitalWrite(LED_C, c);
    digitalWrite(LED_D, d);
    digitalWrite(LED_E, e);
    digitalWrite(LED_F, f);
    digitalWrite(LED_G, g);
}

void mostrarPisoVisualizador(int piso)
{
    switch(piso)
    {
        case 0: 
            Serial.println("0");
            encenderOApagarLedsSieteSegmentos(1,1,1,1,1,1,0);
        break;
        
        case 1:
            Serial.println("1");
            encenderOApagarLedsSieteSegmentos(0,1,1,0,0,0,0);
        break;
        
        case 2:
            Serial.println("2");
            encenderOApagarLedsSieteSegmentos(1,1,0,1,1,0,1);
        break;

        case 3:
            Serial.println("3");
            encenderOApagarLedsSieteSegmentos(1,1,1,1,0,0,1);
        break;
        
        case 4:
            Serial.println("4");
            encenderOApagarLedsSieteSegmentos(0,1,1,0,0,1,1);
        break;
        
        case 5:
            Serial.println("5");
            encenderOApagarLedsSieteSegmentos(1,0,1,1,0,1,1);
        break;
        
        case 6:
            Serial.println("6");
            encenderOApagarLedsSieteSegmentos(1,0,1,1,1,1,1);
        break;
        
        case 7:
            Serial.println("7");
            encenderOApagarLedsSieteSegmentos(1,1,1,0,0,0,0);
        break;
        
        case 8:
            Serial.println("8");
            encenderOApagarLedsSieteSegmentos(1,1,1,1,1,1,1);
        break;
        
        case 9:
            Serial.println("9");
            encenderOApagarLedsSieteSegmentos(1,1,1,0,0,1,1);
        break;
    }
}

# PARCIAL 1 SPD - PARTE PRÁCTICA DOMICILIARIA - VIDELA R. IVÁN A.
![Tinkercad](./img/ArduinoTinkercad.jpg)

## Proyecto: Montacargas
![Tinkercad](./img/montacargas.png)

## Descripción 

Se nos pide armar un modelo de montacarga funcional como maqueta para un hospital. El
objetivo es que implementes un sistema que pueda recibir ordenes de subir, bajar o pausar
desde diferentes pisos y muestre el estado actual del montacargas en el display 7
segmentos.

### Requisitos del Proyecto:

1. Interfaz de usuario:
- Deberá haber 3 botones, uno para subir pisos, otro para bajar pisos y otro para detener el montacarga.
- Deberá tener 2 LEDs, uno verde que indicará cuando el montacarga este en movimiento, otro rojo que indique cuando el montacarga esté pausado.
- En el display 7 segmentos deberán informar en tiempo real en qué piso se encuentra el elevador.
- Se sabe que el tiempo de trayecto entre pisos es de 3 segundos (3000 ms).
- Se deberá informar por monitor serial el piso en el que se encuentra el montacarga, este en funcionamiento o en pausa.

2. Funcionamiento del montacarga:
- Implementa un algoritmo que permita que el elevador suba y baje o frene presionando los botones correspondientes.
- Deberán buscar una forma para pausar el montacargas cuando el usuario lo determine.

3. Documentación:
- Deberán presentar un diagrama esquemático del circuito y explicar el funcionamiento aplicado de cada componente.
- Presentar el código fuente del proyecto de Arduino listo para ser implementado.
- Deberán explicar el funcionamiento integral utilizando documentación MarkDown.

## Función principal

El código hace uso de varias funciones para controlar el visualizador 7 segmentos, las leds y los pulsadores. La función cambiarEstadoMontacargas se encarga de cambiar el estado del montacargas al presionar el pulsador correspondiente, además de mostrar en pantalla el estado actual del montacargas.

~~~ C (lenguaje en el que esta escrito)
void cambiarEstadoMontacargas(int estadoPulsadorPausar, int estadoPulsadorSubir, int estadoPulsadorBajar)
{
    if(estadoPulsadorPausar == HIGH)
    {
        if(sistemaPausado = false)
        {
            Serial.println("MONTACARGAS PAUSADO");
        }
        sistemaPausado = true;
    }
    else
    {
        if(estadoPulsadorSubir == HIGH)
        {
            sistemaPausado = false;
            if(subir == false)
            {
                Serial.println("MONTACARGAS SUBIENDO");
            }
            subir = true;
        }
        else
        {
            if(estadoPulsadorBajar == HIGH)
            {
                sistemaPausado = false;
                if(subir == true)
                {
                    Serial.println("MONTACARGAS BAJANDO");
                }
                subir = false;
            }
        }
    }
}
~~~
### Otras Funciones

La función subirBajarPisos se encarga de aumentar un piso si es que el usuario presiono el pulsador para subir, restar un piso si es que presiono el pulsador para bajar o pausar el sistema si es que ya llegó al ultimo o primer piso.

~~~ C (lenguaje en el que esta escrito)
void subirBajarPisos()
{
    if(subir == true and piso != 9)
    {
        piso++;
    }
    else
    {
        if(subir == false and piso != 0)
        {
            piso--;
        }
        else
        {
            sistemaPausado = true;
        }
    }
}
~~~

Las funciones prenderLed y apagarLed prenden o apagan la led correspondiente pasada por parámetro solo si esta led ya se encuentra prendida o apagada, además avisan que color de led fue prendido o apagado.

~~~ C (lenguaje en el que esta escrito)
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
~~~

La funcion encenderOApagarLedsSieteSegmentos controla todo el visualizados siete segmentos, pasandole por parametros las 7 secciones / 7 leds, pudiendo escribir con un HIGH/1 o LOW/0 si quiero que esa respectiva led este prendida o apagada.

~~~ C (lenguaje en el que esta escrito)
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
~~~

La función mostrarPisoVisualizador recibe el piso actual en el que se encuentra y enciende el visualizador 7 segmentos con el respectivo número de piso.

~~~ C (lenguaje en el que esta escrito)
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
~~~

En el loop principal del código se lee el estado de cada pulsador, se llama a la función cambiarEstadoMontacargas, para saber si el montacargas debe subir, bajar o pausarse, si el sistema esta pausado se prende la led roja y apaga la led verde, esto llamando a las funciones prenderLed y apagarLed, si no está pausado, se hace al revés y llama a la función subirBajarPisos, si se está subiendo se suma un piso, si no se resta y si se llega al ultimo piso o al primero se pausa el montacargas. También se muestra en que piso está por consola y por el visualizador, todo con un delay de 3000ms, que es el trayecto entre pisos. 

~~~ C (lenguaje en el que esta escrito)
void loop()
{ 
    int estadoPulsadorSubir = digitalRead(PULSADOR_SUBIR); 
    int estadoPulsadorBajar = digitalRead(PULSADOR_BAJAR); 
    int estadoPulsadorPausar = digitalRead(PULSADOR_PAUSAR);
    
    cambiarEstadoMontacargas(estadoPulsadorPausar, estadoPulsadorSubir, estadoPulsadorBajar);
    
    if(sistemaPausado == true)
    {
        prenderLed(LED_ROJO);
        apagarLed(LED_VERDE);
    }
    else
    {
        prenderLed(LED_VERDE);
        apagarLed(LED_ROJO);
        subirBajarPisos();
    }
    
    Serial.print("Esta en el piso: ");
    mostrarPisoVisualizador(piso);
    
    delay(3000);
}

~~~

## :robot: Link al proyecto
- [Proyecto](https://www.tinkercad.com/things/6mCJ3CanQ1V-videla-ribodino-ivan-agustin-parcial-1-spd-div-d)

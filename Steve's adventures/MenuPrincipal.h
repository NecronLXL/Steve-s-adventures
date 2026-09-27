#pragma once
#include "UtilidadesConsola.h"
#include <conio.h>  

using namespace System;
using namespace System::Threading;

class MenuPrincipal {
private:
    const int TOTAL_OPCIONES = 4;
    int seleccionActual;

    const int ANCHO_PANTALLA = 120;
    const int ALTO_PANTALLA = 32;

    static void pintarBloque(int col, int fila, ConsoleColor colorFondo, ConsoleColor colorTexto = ConsoleColor::White, String^ texto = "  ") {
        if (col >= 0 && col < 120 && fila >= 0 && fila < 32) {
            UtilidadesConsola::posicionarCursor(col, fila);
            Console::BackgroundColor = colorFondo;
            Console::ForegroundColor = colorTexto;
            Console::Write(texto);
        }
    }

    void dibujarArbol(int baseX, int baseY) const {
        for (int y = baseY - 4; y <= baseY - 1; y += 1) {
            for (int x = baseX - 6; x <= baseX + 6; x += 2) {
                if ((y == baseY - 4 || y == baseY - 1) && (x == baseX - 6 || x == baseX + 6)) continue;
                ConsoleColor colorHoja = ((x + y) % 4 == 0) ? ConsoleColor::Green : ConsoleColor::DarkGreen;
                pintarBloque(x, y, colorHoja);
            }
        }
        for (int y = baseY; y <= 17; y++) {
            pintarBloque(baseX, y, ConsoleColor::DarkRed);
        }
    }

    void dibujarArbusto(int x, int y) const {
        pintarBloque(x, y, ConsoleColor::DarkGreen);
        pintarBloque(x + 2, y, ConsoleColor::Green);
        pintarBloque(x + 4, y, ConsoleColor::DarkGreen);
        pintarBloque(x + 2, y - 1, ConsoleColor::DarkGreen);
    }

    void dibujarRoca(int x, int y, bool grande = false) const {
        if (grande) {
            pintarBloque(x, y, ConsoleColor::DarkGray);
            pintarBloque(x + 2, y, ConsoleColor::Gray);
            pintarBloque(x, y - 1, ConsoleColor::Gray);
            pintarBloque(x + 2, y - 1, ConsoleColor::DarkGray);
        }
        else {
            pintarBloque(x, y, ConsoleColor::Gray);
            pintarBloque(x + 2, y, ConsoleColor::DarkGray);
        }
    }

    void dibujarFondoEstatico() const {
        // 1. CIELO CELESTE AMPLIADO (Ocupa hasta la fila 17)
        for (int y = 0; y < 18; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) pintarBloque(x, y, ConsoleColor::Cyan);
        }

        // 2. SOL DE CUBOS
        for (int y = 1; y <= 5; y++) {
            for (int x = 6; x <= 16; x += 2) {
                if ((y == 1 || y == 5) && (x == 6 || x == 16)) continue;
                pintarBloque(x, y, ConsoleColor::Yellow);
            }
        }

        // 3. MONTAÑAS DE FONDO
        for (int y = 8; y < 18; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((y - 7) * 2 > Math::Abs(x - 30)) pintarBloque(x, y, ConsoleColor::DarkGray);
                if ((y - 5) * 2 > Math::Abs(x - 95)) pintarBloque(x, y, ConsoleColor::Gray);
            }
        }

        // 4. BOSQUE DE ROBLES
        dibujarArbol(8, 13);
        dibujarArbol(20, 14);
        dibujarArbol(32, 13);
        dibujarArbol(88, 13);
        dibujarArbol(100, 14);
        dibujarArbol(112, 13);

        // 5. EXTENSA PRADERA DE PASTO VERDE (Filas 18 a 31)
        for (int y = 18; y < ALTO_PANTALLA; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((x + y) % 5 == 0) {
                    pintarBloque(x, y, ConsoleColor::DarkGreen);
                }
                else {
                    pintarBloque(x, y, ConsoleColor::Green);
                }
            }
        }

        // 6. ARBUSTOS, ROCAS Y FLORES
        dibujarArbusto(10, 22);
        dibujarArbusto(26, 26);
        dibujarArbusto(84, 23);
        dibujarArbusto(104, 27);

        dibujarRoca(18, 24, true);
        dibujarRoca(4, 28, false);
        dibujarRoca(96, 25, true);
        dibujarRoca(112, 29, false);

        pintarBloque(14, 20, ConsoleColor::Green, ConsoleColor::Red, "♦ ");
        pintarBloque(34, 28, ConsoleColor::Green, ConsoleColor::Yellow, "♦ ");
        pintarBloque(78, 21, ConsoleColor::Green, ConsoleColor::Red, "♦ ");
        pintarBloque(90, 29, ConsoleColor::Green, ConsoleColor::Yellow, "♦ ");

        // 7. PANEL DEL MENÚ COMPACTO (Comienza en Y = 9 para dar espacio al cielo arriba)
        int menuX = 32, menuY = 9, menuAncho = 56, menuAlto = 15;
        for (int y = menuY; y < menuY + menuAlto; y++) {
            for (int x = menuX; x < menuX + menuAncho; x += 2) {
                if (y == menuY || y == menuY + menuAlto - 1 || x == menuX || x == menuX + menuAncho - 2) {
                    pintarBloque(x, y, ConsoleColor::DarkGray); // Borde
                }
                else {
                    pintarBloque(x, y, ConsoleColor::Black);   // Fondo del menú
                }
            }
        }
    }

    void animarNubes(int frame) const {
        for (int y = 2; y <= 5; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                // Protege el sol y el marco central reducido
                if ((y <= 5 && x >= 6 && x <= 16) || (x >= 32 && x <= 88 && y >= 9 && y <= 23)) continue;

                bool esNube = false;

                // Nube 1
                int n1X = (10 + frame) % ANCHO_PANTALLA;
                if ((y == 3 || y == 4) && x >= n1X && x < n1X + 18) esNube = true;
                if (y == 2 && x >= n1X + 4 && x < n1X + 14) esNube = true;

                // Nube 2
                int n2X = (70 + (frame / 2)) % ANCHO_PANTALLA;
                if (y >= 4 && y <= 5 && x >= n2X && x < n2X + 22) esNube = true;

                if (esNube) {
                    pintarBloque(x, y, ConsoleColor::White);
                }
                else {
                    if (y >= 8 && ((y - 7) * 2 > Math::Abs(x - 30) || (y - 5) * 2 > Math::Abs(x - 95))) {
                        // Conserva las montañas
                    }
                    else {
                        pintarBloque(x, y, ConsoleColor::Cyan); // Restaura el cielo
                    }
                }
            }
        }
    }

    void dibujarOpciones() const {
        const char* const OPCIONES[4] = {
            "INICIAR AVENTURA",
            "TUTORIAL DE RECURSOS",
            "SELECCION DE NIVELES",
            "SALIR DEL JUEGO"
        };
        int posY[4] = { 15, 17, 19, 21 }; // Posiciones dentro del nuevo panel compacto
        int centroX = 41;

        Console::BackgroundColor = ConsoleColor::Black;

        UtilidadesConsola::posicionarCursor(50, 12);
        Console::ForegroundColor = ConsoleColor::Green;
        Console::Write(" == J E E S S E ´ S");

        // Subtítulo
        UtilidadesConsola::posicionarCursor(48, 13);
        Console::ForegroundColor = ConsoleColor::White;
        Console::Write("== A D V E N T U R E S ==");

        // OPCIONES DE SELECCIÓN
        for (int i = 0; i < TOTAL_OPCIONES; i++) {
            UtilidadesConsola::posicionarCursor(centroX, posY[i]);

            if (i == seleccionActual) {
                Console::BackgroundColor = ConsoleColor::Green;
                Console::ForegroundColor = ConsoleColor::Black;
                Console::Write("  [■] > ");
                Console::Write(gcnew String(OPCIONES[i]));
                int padding = 24 - String(OPCIONES[i]).Length;
                for (int p = 0; p < padding; p++) Console::Write(" ");
                Console::Write("< [■]  ");
            }
            else {
                Console::BackgroundColor = ConsoleColor::DarkGray;
                Console::ForegroundColor = ConsoleColor::White;
                Console::Write("        ");
                Console::Write(gcnew String(OPCIONES[i]));
                int padding = 24 - String(OPCIONES[i]).Length;
                for (int p = 0; p < padding; p++) Console::Write(" ");
                Console::Write("       ");
            }
        }
        Console::BackgroundColor = ConsoleColor::Black;
    }

public:
    MenuPrincipal() {
        seleccionActual = 0;
    }

    void mostrarEntrada() const {
        Console::SetWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
        Console::SetBufferSize(ANCHO_PANTALLA, ALTO_PANTALLA);

        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();

        dibujarFondoEstatico();
    }

    int ejecutar() {
        mostrarEntrada();
        dibujarOpciones();

        bool elegido = false;
        int frameAnimacion = 0;

        while (!elegido) {
            animarNubes(frameAnimacion);
            frameAnimacion++;
            Thread::Sleep(50);

            if (_kbhit()) {
                int tecla = _getch();

                if (tecla == 224 || tecla == 0) {
                    tecla = _getch();
                    if (tecla == 72) tecla = 'w';
                    if (tecla == 80) tecla = 's';
                }

                if (tecla == 'w' || tecla == 'W') {
                    seleccionActual--;
                    if (seleccionActual < 0) seleccionActual = TOTAL_OPCIONES - 1;
                    dibujarOpciones();
                }
                else if (tecla == 's' || tecla == 'S') {
                    seleccionActual++;
                    if (seleccionActual >= TOTAL_OPCIONES) seleccionActual = 0;
                    dibujarOpciones();
                }
                else if (tecla == 13 || tecla == ' ') {
                    elegido = true;
                }
            }
        }

        return seleccionActual;
    }
};
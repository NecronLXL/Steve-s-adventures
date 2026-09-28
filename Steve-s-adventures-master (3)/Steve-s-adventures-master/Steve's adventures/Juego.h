#pragma once
#include "MenuPrincipal.h"
#include "UtilidadesConsola.h"
#include "Nivel1.h"
#include <iostream>
#include <conio.h>

using namespace std;
using namespace System;
using namespace System::Threading;

class Juego {
private:
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

    void dibujarFondoEstatico() const {
        for (int y = 0; y < 18; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) pintarBloque(x, y, ConsoleColor::Cyan);
        }
        for (int y = 1; y <= 5; y++) {
            for (int x = 6; x <= 16; x += 2) {
                if ((y == 1 || y == 5) && (x == 6 || x == 16)) continue;
                pintarBloque(x, y, ConsoleColor::Yellow);
            }
        }
        for (int y = 8; y < 18; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((y - 7) * 2 > Math::Abs(x - 30)) pintarBloque(x, y, ConsoleColor::DarkGray);
                if ((y - 5) * 2 > Math::Abs(x - 95)) pintarBloque(x, y, ConsoleColor::Gray);
            }
        }
        for (int y = 18; y < ALTO_PANTALLA; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((x + y) % 5 == 0) pintarBloque(x, y, ConsoleColor::DarkGreen);
                else pintarBloque(x, y, ConsoleColor::Green);
            }
        }
    }

    void animarNubes(int frame) const {
        for (int y = 2; y <= 5; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if (y <= 5 && x >= 6 && x <= 16) continue;

                bool esNube = false;
                int n1X = (10 + frame) % ANCHO_PANTALLA;
                if ((y == 3 || y == 4) && x >= n1X && x < n1X + 18) esNube = true;
                if (y == 2 && x >= n1X + 4 && x < n1X + 14) esNube = true;

                int n2X = (70 + (frame / 2)) % ANCHO_PANTALLA;
                if (y >= 4 && y <= 5 && x >= n2X && x < n2X + 22) esNube = true;

                if (esNube) {
                    pintarBloque(x, y, ConsoleColor::White);
                }
                else {
                    if (y >= 8 && ((y - 7) * 2 > Math::Abs(x - 30) || (y - 5) * 2 > Math::Abs(x - 95))) {
                        // Montana
                    }
                    else {
                        pintarBloque(x, y, ConsoleColor::Cyan);
                    }
                }
            }
        }
    }

    void dibujarPanelGUI(int x, int y, int ancho, int alto) const {
        for (int j = y; j < y + alto; j++) {
            for (int i = x; i < x + ancho; i += 2) {
                if (j == y || j == y + alto - 1 || i == x || i == x + ancho - 2) {
                    pintarBloque(i, j, ConsoleColor::DarkGray);
                }
                else {
                    pintarBloque(i, j, ConsoleColor::Black);
                }
            }
        }
    }

    void dibujarMochilaInventario(bool abierta, bool tieneMochilaItem, bool tieneDiamante) const {
        if (!abierta) {
            for (int y = 2; y <= 10; y++) {
                for (int x = 88; x <= 118; x += 2) {
                    pintarBloque(x, y, ConsoleColor::Cyan);
                }
            }
            return;
        }

        int mx = 88;
        int my = 2;
        for (int y = my; y < my + 9; y++) {
            for (int x = mx; x < mx + 30; x += 2) {
                if (y == my || y == my + 8 || x == mx || x == mx + 28) {
                    pintarBloque(x, y, ConsoleColor::DarkGray);
                }
                else {
                    pintarBloque(x, y, ConsoleColor::Black);
                }
            }
        }

        UtilidadesConsola::posicionarCursor(mx + 3, my + 1);
        Console::BackgroundColor = ConsoleColor::Black;
        Console::ForegroundColor = ConsoleColor::Yellow;
        Console::Write("=== MOCHILA DE JESSE ===");

        UtilidadesConsola::posicionarCursor(mx + 3, my + 3);
        if (tieneMochilaItem) {
            Console::ForegroundColor = ConsoleColor::Green;
            Console::Write(" [M] Mochila Equipada   ");
        }
        else {
            Console::ForegroundColor = ConsoleColor::DarkGray;
            Console::Write(" [ ] Mochila (Falta)    ");
        }

        UtilidadesConsola::posicionarCursor(mx + 3, my + 5);
        if (tieneDiamante) {
            Console::ForegroundColor = ConsoleColor::Cyan;
            Console::Write(" [<> Diamante Guardado] ");
        }
        else {
            Console::ForegroundColor = ConsoleColor::DarkGray;
            Console::Write(" [   ] Slot Vacio     ");
        }
    }

    // Animación corta de partículas cerca del jugador al recoger un objeto
    void animarRecoleccion(int x, int y) const {
        for (int i = 0; i < 3; i++) {
            pintarBloque(x - 2, y - 1, ConsoleColor::Yellow, ConsoleColor::DarkYellow, " *");
            pintarBloque(x + 4, y - 1, ConsoleColor::Yellow, ConsoleColor::DarkYellow, ". ");
            pintarBloque(x + 2, y + 2, ConsoleColor::Cyan, ConsoleColor::Blue, "* ");
            Thread::Sleep(70);
            pintarBloque(x - 2, y - 1, ConsoleColor::Green, ConsoleColor::Green, "  ");
            pintarBloque(x + 4, y - 1, ConsoleColor::Green, ConsoleColor::Green, "  ");
            pintarBloque(x + 2, y + 2, ConsoleColor::Green, ConsoleColor::Green, "  ");
            Thread::Sleep(70);
        }
    }

    // ------------------------------------------------------------------------
    // TUTORIAL DETALLADO, COMPLEJO Y CON RECOLECCIÓN DE MOCHILA
    // ------------------------------------------------------------------------
    void mostrarTutorial() const {
        Console::SetWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
        Console::SetBufferSize(ANCHO_PANTALLA, ALTO_PANTALLA);

        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();

        // 1. Cielo superior detallado
        for (int y = 0; y <= 7; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) pintarBloque(x, y, ConsoleColor::Cyan);
        }
        for (int y = 1; y <= 4; y++) {
            for (int x = 6; x <= 14; x += 2) pintarBloque(x, y, ConsoleColor::Yellow);
        }

        // 2. Pradera verde inferior
        for (int y = 8; y < ALTO_PANTALLA; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((x + y) % 5 == 0) pintarBloque(x, y, ConsoleColor::DarkGreen);
                else pintarBloque(x, y, ConsoleColor::Green);
            }
        }

        // 3. Cabaña de madera detallada (Techo, paredes, puerta y ventanas)
        for (int y = 3; y <= 5; y++) {
            for (int x = 14; x <= 48; x += 2) pintarBloque(x, y, ConsoleColor::Yellow); // Techo de paja
        }
        for (int y = 6; y <= 11; y++) {
            for (int x = 16; x <= 46; x += 2) pintarBloque(x, y, ConsoleColor::DarkYellow); // Paredes
        }
        // Ventanas y puerta de la cabaña
        pintarBloque(22, 8, ConsoleColor::Cyan, ConsoleColor::Blue, "[]");
        pintarBloque(38, 8, ConsoleColor::Cyan, ConsoleColor::Blue, "[]");
        pintarBloque(30, 9, ConsoleColor::DarkRed, ConsoleColor::Black, "||");

        // 4. Corral de vallas con heno a la izquierda
        for (int x = 4; x <= 16; x += 2) {
            pintarBloque(x, 9, ConsoleColor::DarkGray);
            pintarBloque(x, 15, ConsoleColor::DarkGray);
        }
        for (int y = 9; y <= 15; y++) {
            pintarBloque(4, y, ConsoleColor::DarkGray);
        }
        // Montón de heno en el corral
        pintarBloque(8, 12, ConsoleColor::Yellow, ConsoleColor::DarkYellow, "/\\");
        pintarBloque(8, 13, ConsoleColor::Yellow, ConsoleColor::DarkYellow, "MM");

        // 5. Pozo de agua decorativo
        pintarBloque(16, 20, ConsoleColor::DarkGray, ConsoleColor::Blue, "OO");

        // 6. Camino de tierra complejo que serpentea por el mapa
        for (int y = 12; y < ALTO_PANTALLA; y++) {
            for (int x = 28; x <= 36; x += 2) pintarBloque(x, y, ConsoleColor::DarkGray);
        }
        for (int x = 36; x <= 64; x += 2) {
            for (int y = 18; y <= 22; y++) pintarBloque(x, y, ConsoleColor::DarkGray);
        }

        // 7. Bosque y árboles complejos a la derecha y abajo
        for (int arbolY = 8; arbolY < 28; arbolY += 4) {
            for (int arbolX = 75; arbolX < 118; arbolX += 6) {
                pintarBloque(arbolX, arbolY, ConsoleColor::DarkGreen);
                pintarBloque(arbolX + 2, arbolY, ConsoleColor::Green);
                pintarBloque(arbolX + 1, arbolY + 1, ConsoleColor::DarkRed);
            }
        }

        int jesseX = 30;
        int jesseY = 24;
        int mochilaX = 42;
        int mochilaY = 20;
        int diamanteX = 66;
        int diamanteY = 20;

        bool mochilaAgarrada = false;
        bool diamanteAgarrado = false;
        bool mochilaAbierta = false;
        bool salir = false;

        while (!salir) {
            // Dibujar la Mochila en el suelo si no ha sido recogida
            if (!mochilaAgarrada) {
                pintarBloque(mochilaX, mochilaY, ConsoleColor::DarkYellow, ConsoleColor::White, "[M]");
            }

            // Dibujar el Diamante si la mochila ya fue agarrada y el diamante no
            if (mochilaAgarrada && !diamanteAgarrado) {
                pintarBloque(diamanteX, diamanteY, ConsoleColor::Cyan, ConsoleColor::Blue, "<>");
            }

            // Dibujar a Jesse
            pintarBloque(jesseX, jesseY, ConsoleColor::Yellow, ConsoleColor::Black, "JJ");
            pintarBloque(jesseX, jesseY + 1, ConsoleColor::Blue, ConsoleColor::Black, "HH");

            // Actualizar panel de mochila
            dibujarMochilaInventario(mochilaAbierta, mochilaAgarrada, diamanteAgarrado);

            // Instrucciones superiores
            UtilidadesConsola::posicionarCursor(12, 1);
            Console::BackgroundColor = ConsoleColor::Black;
            Console::ForegroundColor = ConsoleColor::Yellow;
            Console::Write(" [W][A][S][D]: Mover | [E]: Agarrar Objeto | [C]: Ver Mochila | [ESC]: Salir ");

            // Mensajes guía inferiores dinámicos
            UtilidadesConsola::posicionarCursor(18, 29);
            Console::BackgroundColor = ConsoleColor::DarkGreen;
            Console::ForegroundColor = ConsoleColor::White;
            if (!mochilaAgarrada) {
                if (Math::Abs(jesseX - mochilaX) <= 3 && Math::Abs(jesseY - mochilaY) <= 1) {
                    Console::Write(" ¡Estas sobre la Mochila! Presiona [ E ] para recogerla y equiparla ");
                }
                else {
                    Console::Write(" Paso 1: Camina hacia la izquierda y busca la Mochila [M] en el suelo ");
                }
            }
            else if (!diamanteAgarrado) {
                if (Math::Abs(jesseX - diamanteX) <= 3 && Math::Abs(jesseY - diamanteY) <= 1) {
                    Console::Write(" ¡Genial! Presiona [ E ] para recoger el Diamante y guardarlo ");
                }
                else {
                    Console::Write(" Paso 2: Sigue el camino hacia la derecha y encuentra el Diamante (<>) ");
                }
            }
            else {
                Console::Write(" ¡TUTORIAL COMPLETADO! Presiona [C] para revisar tu mochila o [ESC] para salir ");
            }

            // Controles
            if (_kbhit()) {
                int tecla = _getch();
                if (tecla == 224 || tecla == 0) tecla = _getch();

                int prevX = jesseX;
                int prevY = jesseY;

                if (tecla == 'w' || tecla == 'W' || tecla == 72) {
                    if (jesseY > 10) jesseY--;
                }
                else if (tecla == 's' || tecla == 'S' || tecla == 80) {
                    if (jesseY < 26) jesseY++;
                }
                else if (tecla == 'a' || tecla == 'A' || tecla == 75) {
                    if (jesseX > 6) jesseX -= 2;
                }
                else if (tecla == 'd' || tecla == 'D' || tecla == 77) {
                    if (jesseX < 75) jesseX += 2;
                }
                else if (tecla == 'e' || tecla == 'E') {
                    if (!mochilaAgarrada && Math::Abs(jesseX - mochilaX) <= 3 && Math::Abs(jesseY - mochilaY) <= 1) {
                        animarRecoleccion(jesseX, jesseY);
                        mochilaAgarrada = true;
                    }
                    else if (mochilaAgarrada && !diamanteAgarrado && Math::Abs(jesseX - diamanteX) <= 3 && Math::Abs(jesseY - diamanteY) <= 1) {
                        animarRecoleccion(jesseX, jesseY);
                        diamanteAgarrado = true;
                        mochilaAbierta = true; // Abre automáticamente la mochila para mostrar que se guardó
                    }
                }
                else if (tecla == 'c' || tecla == 'C') {
                    mochilaAbierta = !mochilaAbierta;
                }
                else if (tecla == 27) { // ESC
                    salir = true;
                }

                // Borrar rastro anterior de Jesse
                for (int cy = prevY; cy <= prevY + 1; cy++) {
                    for (int cx = prevX; cx <= prevX + 2; cx += 2) {
                        if ((cx >= 28 && cx <= 36) || (cx >= 36 && cx <= 64 && cy >= 18 && cy <= 22)) {
                            pintarBloque(cx, cy, ConsoleColor::DarkGray); // Camino
                        }
                        else {
                            if ((cx + cy) % 5 == 0) pintarBloque(cx, cy, ConsoleColor::DarkGreen);
                            else pintarBloque(cx, cy, ConsoleColor::Green); // Pradera
                        }
                    }
                }
            }

            Thread::Sleep(30);
        }
    }

    // ------------------------------------------------------------------------
    // SELECCIÓN DE NIVELES
    // ------------------------------------------------------------------------
    void mostrarSeleccionNiveles() const {
        Console::SetWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
        Console::SetBufferSize(ANCHO_PANTALLA, ALTO_PANTALLA);

        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();
        dibujarFondoEstatico();
        dibujarPanelGUI(30, 7, 60, 18);

        int seleccion = 0;
        bool elegido = false;
        int frame = 0;
        const char* const NIVELES[3] = {
            "NIVEL 1: El Bosque de Jesse",
            "NIVEL 2: El Desfiladero de Lukas",
            "NIVEL 3: La Redencion de Ivor"
        };

        while (!elegido) {
            animarNubes(frame);
            frame++;

            for (int i = 0; i < 3; i++) {
                UtilidadesConsola::posicionarCursor(36, 12 + (i * 2));

                if (i == seleccion) {
                    Console::BackgroundColor = ConsoleColor::Green;
                    Console::ForegroundColor = ConsoleColor::Black;
                    Console::Write("  > ");
                    Console::Write(gcnew String(NIVELES[i]));
                    Console::Write(" <  ");
                }
                else {
                    Console::BackgroundColor = ConsoleColor::DarkGray;
                    Console::ForegroundColor = ConsoleColor::White;
                    Console::Write("    ");
                    Console::Write(gcnew String(NIVELES[i]));
                    Console::Write("    ");
                }
            }

            UtilidadesConsola::posicionarCursor(38, 20);
            Console::BackgroundColor = ConsoleColor::Black;
            Console::ForegroundColor = ConsoleColor::Gray;
            Console::Write("[W/S] Navegar | [Enter] Jugar | [ESC] Volver");

            if (_kbhit()) {
                int tecla = _getch();
                if (tecla == 224 || tecla == 0) tecla = _getch();

                if (tecla == 'w' || tecla == 'W' || tecla == 72) {
                    seleccion--;
                    if (seleccion < 0) seleccion = 2;
                }
                else if (tecla == 's' || tecla == 'S' || tecla == 80) {
                    seleccion++;
                    if (seleccion > 2) seleccion = 0;
                }
                else if (tecla == 13 || tecla == ' ') {
                    elegido = true;
                }
                else if (tecla == 27) {
                    return;
                }
            }

            Thread::Sleep(50);
        }

        if (seleccion == 0) {
            Nivel1::iniciar();
        }
        else {
            UtilidadesConsola::limpiarPantalla();
            Console::ForegroundColor = ConsoleColor::Yellow;
            Console::WriteLine("\n\n   Cargando Nivel... (Desbloqueado en los siguientes hitos)");
            _getch();
        }
    }

    // ------------------------------------------------------------------------
    // CRÉDITOS
    // ------------------------------------------------------------------------
    void mostrarCreditos() const {
        Console::SetWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
        Console::SetBufferSize(ANCHO_PANTALLA, ALTO_PANTALLA);

        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();
        dibujarFondoEstatico();
        dibujarPanelGUI(32, 7, 56, 18);

        Console::BackgroundColor = ConsoleColor::Black;
        UtilidadesConsola::posicionarCursor(42, 9);
        Console::ForegroundColor = ConsoleColor::Yellow;
        Console::Write("=== JESSE'S ADVENTURES ===");

        UtilidadesConsola::posicionarCursor(45, 11);
        Console::ForegroundColor = ConsoleColor::Green;
        Console::Write("DESARROLLADORES:");

        UtilidadesConsola::posicionarCursor(42, 13);
        Console::ForegroundColor = ConsoleColor::White;
        Console::Write("Hans J. Velasco");

        UtilidadesConsola::posicionarCursor(42, 14);
        Console::ForegroundColor = ConsoleColor::White;
        Console::Write("Stephen S. Barbaran");

        UtilidadesConsola::posicionarCursor(42, 15);
        Console::ForegroundColor = ConsoleColor::White;
        Console::Write("Fabritzio M. Sierra");

        UtilidadesConsola::posicionarCursor(38, 17);
        Console::ForegroundColor = ConsoleColor::DarkYellow;
        Console::Write("Curso: Algoritmos (UPC 2026)");

        UtilidadesConsola::posicionarCursor(36, 21);
        Console::ForegroundColor = ConsoleColor::Gray;
        Console::Write("Presiona cualquier tecla para volver...");

        int frame = 0;
        while (!_kbhit()) {
            animarNubes(frame);
            frame++;
            Thread::Sleep(50);
        }
        _getch();
    }

public:
    void ejecutar() {
        MenuPrincipal menu;
        bool salir = false;

        while (!salir) {
            int opcion = menu.ejecutar();

            switch (opcion) {
            case 0:
                Nivel1::iniciar();
                break;
            case 1:
                mostrarTutorial();
                break;
            case 2:
                mostrarSeleccionNiveles();
                break;
            case 3:
                salir = true;
                break;
            }
        }
    }
};
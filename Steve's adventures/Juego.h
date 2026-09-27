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

    static const int PANEL_MOCHILA_X = 84;
    static const int PANEL_MOCHILA_Y = 2;
    static const int PANEL_MOCHILA_ANCHO = 34;
    static const int PANEL_MOCHILA_ALTO = 19;
    static const int CAPACIDAD_MOCHILA = 8;

    static void pintarBloque(int col, int fila, ConsoleColor colorFondo, ConsoleColor colorTexto = ConsoleColor::White, String^ texto = "  ") {
        if (col >= 0 && col < 120 && fila >= 0 && fila < 32) {
            UtilidadesConsola::posicionarCursor(col, fila);
            Console::BackgroundColor = colorFondo;
            Console::ForegroundColor = colorTexto;
            Console::Write(texto);
        }
    }

    ConsoleColor colorTerrenoBase(int x, int y) const {
        bool enCaminoVertical = (x >= 28 && x <= 36);
        bool enCaminoHorizontal = (x >= 36 && x <= 64 && y >= 18 && y <= 22);
        if (enCaminoVertical || enCaminoHorizontal) {
            return ((x + y) % 6 == 0) ? ConsoleColor::Gray : ConsoleColor::DarkGray;
        }
        return ((x + y) % 5 == 0) ? ConsoleColor::DarkGreen : ConsoleColor::Green;
    }

    bool esPosicionSolida(int x, int y) const {
        bool paredCabana = (x >= 16 && x <= 46 && y >= 10 && y <= 11);
        bool cercaCorral = (x >= 4 && x <= 16 && y >= 9 && y <= 15);
        bool estructuraPozo = (x >= 14 && x <= 18 && y >= 18 && y <= 20);
        return paredCabana || cercaCorral || estructuraPozo;
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

    void dibujarMochilaInventario(bool abierta, bool tieneMochilaItem, array<String^>^ objetos, array<ConsoleColor>^ coloresObjetos) const {
        int mx = PANEL_MOCHILA_X;
        int my = PANEL_MOCHILA_Y;
        int anchoPanel = PANEL_MOCHILA_ANCHO;
        int altoPanel = PANEL_MOCHILA_ALTO;

        if (!abierta) {
            for (int y = my; y < my + altoPanel; y++) {
                for (int x = mx; x < mx + anchoPanel; x += 2) {
                    pintarBloque(x, y, ConsoleColor::Cyan);
                }
            }
            return;
        }

        for (int y = my; y < my + altoPanel; y++) {
            for (int x = mx; x < mx + anchoPanel; x += 2) {
                if (y == my || y == my + altoPanel - 1 || x == mx || x == mx + anchoPanel - 2) {
                    pintarBloque(x, y, ConsoleColor::DarkGray);
                }
                else {
                    pintarBloque(x, y, ConsoleColor::Black);
                }
            }
        }

        Console::BackgroundColor = ConsoleColor::Black;

        UtilidadesConsola::posicionarCursor(mx + 3, my + 1);
        Console::ForegroundColor = ConsoleColor::Yellow;
        Console::Write("=== MOCHILA DE JESSE ===");

        UtilidadesConsola::posicionarCursor(mx + 3, my + 3);
        if (tieneMochilaItem) {
            Console::ForegroundColor = ConsoleColor::Green;
            Console::Write("Estado: Equipada         ");
        }
        else {
            Console::ForegroundColor = ConsoleColor::DarkGray;
            Console::Write("Estado: Sin conseguir    ");
        }

        int capacidad = objetos->Length;
        int ocupados = 0;
        for (int i = 0; i < capacidad; i++) {
            if (objetos[i] != nullptr) ocupados++;
        }

        UtilidadesConsola::posicionarCursor(mx + 3, my + 5);
        Console::ForegroundColor = ConsoleColor::White;
        Console::Write(String::Format("Inventario ({0}/{1} objetos):", ocupados, capacidad));

        for (int i = 0; i < capacidad; i++) {
            UtilidadesConsola::posicionarCursor(mx + 3, my + 7 + i);
            if (objetos[i] != nullptr) {
                Console::ForegroundColor = coloresObjetos[i];
                Console::Write(String::Format(" [{0}] {1}", i + 1, objetos[i]->PadRight(20)));
            }
            else {
                Console::ForegroundColor = ConsoleColor::DarkGray;
                Console::Write(String::Format(" [{0}] -- vacio --         ", i + 1));
            }
        }

        UtilidadesConsola::posicionarCursor(mx + 3, my + altoPanel - 2);
        Console::ForegroundColor = ConsoleColor::Gray;
        Console::Write("[C] Cerrar mochila");
    }

    void animarRecoleccion(int x, int y, String^ nombreObjeto, ConsoleColor colorTexto) const {
        int tx = x - 4;
        int ty = y - 2;
        String^ mensaje = String::Concat("+1 ", nombreObjeto);
        ConsoleColor fondoTexto = colorTerrenoBase(x, y);

        for (int i = 0; i < 4; i++) {
            pintarBloque(x - 2, y - 1, ConsoleColor::Yellow, ConsoleColor::DarkYellow, "* ");
            pintarBloque(x + 4, y - 1, ConsoleColor::Yellow, ConsoleColor::DarkYellow, " *");
            pintarBloque(x + 1, y + 2, ConsoleColor::Cyan, ConsoleColor::Blue, "* ");
            pintarBloque(x - 3, y + 1, ConsoleColor::White, ConsoleColor::Gray, ". ");

            UtilidadesConsola::posicionarCursor(tx, ty);
            Console::BackgroundColor = ConsoleColor::Black;
            Console::ForegroundColor = colorTexto;
            Console::Write(mensaje);

            Thread::Sleep(90);

            pintarBloque(x - 2, y - 1, colorTerrenoBase(x - 2, y - 1));
            pintarBloque(x + 4, y - 1, colorTerrenoBase(x + 4, y - 1));
            pintarBloque(x + 1, y + 2, colorTerrenoBase(x + 1, y + 2));
            pintarBloque(x - 3, y + 1, colorTerrenoBase(x - 3, y + 1));

            UtilidadesConsola::posicionarCursor(tx, ty);
            Console::BackgroundColor = fondoTexto;
            Console::ForegroundColor = fondoTexto;
            Console::Write(gcnew String(' ', mensaje->Length));

            Thread::Sleep(60);
        }
    }

    void mostrarTutorial() const {
        Console::SetWindowSize(ANCHO_PANTALLA, ALTO_PANTALLA);
        Console::SetBufferSize(ANCHO_PANTALLA, ALTO_PANTALLA);

        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();

        for (int y = 0; y <= 7; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) pintarBloque(x, y, ConsoleColor::Cyan);
        }
        for (int y = 1; y <= 4; y++) {
            for (int x = 6; x <= 14; x += 2) pintarBloque(x, y, ConsoleColor::Yellow);
        }

        for (int y = 8; y < ALTO_PANTALLA; y++) {
            for (int x = 0; x < ANCHO_PANTALLA; x += 2) {
                if ((x + y) % 5 == 0) pintarBloque(x, y, ConsoleColor::DarkGreen);
                else pintarBloque(x, y, ConsoleColor::Green);
            }
        }

        for (int y = 3; y <= 5; y++) {
            for (int x = 14; x <= 48; x += 2) pintarBloque(x, y, ConsoleColor::Yellow);
        }
        for (int y = 6; y <= 11; y++) {
            for (int x = 16; x <= 46; x += 2) pintarBloque(x, y, ConsoleColor::DarkYellow);
        }
        pintarBloque(22, 8, ConsoleColor::Cyan, ConsoleColor::Blue, "[]");
        pintarBloque(38, 8, ConsoleColor::Cyan, ConsoleColor::Blue, "[]");
        pintarBloque(30, 9, ConsoleColor::DarkRed, ConsoleColor::Black, "||");
        pintarBloque(40, 2, ConsoleColor::DarkGray, ConsoleColor::Gray, "[]");
        pintarBloque(40, 1, ConsoleColor::Cyan, ConsoleColor::White, ". ");
        pintarBloque(42, 0, ConsoleColor::Cyan, ConsoleColor::White, ". ");
        pintarBloque(26, 11, ConsoleColor::DarkYellow, ConsoleColor::Red, "o ");
        pintarBloque(34, 11, ConsoleColor::DarkYellow, ConsoleColor::Red, "o ");

        for (int x = 4; x <= 16; x += 2) {
            pintarBloque(x, 9, ConsoleColor::DarkGray);
            pintarBloque(x, 15, ConsoleColor::DarkGray);
        }
        for (int y = 9; y <= 15; y++) {
            pintarBloque(4, y, ConsoleColor::DarkGray);
            pintarBloque(16, y, ConsoleColor::DarkGray);
        }
        pintarBloque(8, 12, ConsoleColor::Yellow, ConsoleColor::DarkYellow, "/\\");
        pintarBloque(8, 13, ConsoleColor::Yellow, ConsoleColor::DarkYellow, "MM");
        pintarBloque(12, 13, ConsoleColor::Gray, ConsoleColor::White, "oo");

        pintarBloque(14, 18, ConsoleColor::DarkGray, ConsoleColor::DarkGray, "  ");
        pintarBloque(16, 18, ConsoleColor::DarkGray, ConsoleColor::DarkGray, "  ");
        pintarBloque(18, 18, ConsoleColor::DarkGray, ConsoleColor::DarkGray, "  ");
        pintarBloque(14, 19, ConsoleColor::DarkGray, ConsoleColor::DarkGray, "  ");
        pintarBloque(18, 19, ConsoleColor::DarkGray, ConsoleColor::DarkGray, "  ");
        pintarBloque(14, 20, ConsoleColor::Gray, ConsoleColor::Gray, "  ");
        pintarBloque(16, 20, ConsoleColor::DarkGray, ConsoleColor::Blue, "OO");
        pintarBloque(18, 20, ConsoleColor::Gray, ConsoleColor::Gray, "  ");

        for (int y = 12; y < ALTO_PANTALLA; y++) {
            for (int x = 28; x <= 36; x += 2) pintarBloque(x, y, colorTerrenoBase(x, y));
        }
        for (int x = 36; x <= 64; x += 2) {
            for (int y = 18; y <= 22; y++) pintarBloque(x, y, colorTerrenoBase(x, y));
        }

        Random^ rngBosque = gcnew Random(7);
        for (int arbolY = 8; arbolY < ALTO_PANTALLA - 2; arbolY += 4) {
            for (int arbolX = 76; arbolX < ANCHO_PANTALLA - 2; arbolX += 6) {
                if (arbolX >= PANEL_MOCHILA_X && arbolY <= PANEL_MOCHILA_Y + PANEL_MOCHILA_ALTO) continue;

                int bx = arbolX + (rngBosque->Next(0, 2) * 2);
                int by = arbolY + rngBosque->Next(0, 2);

                pintarBloque(bx, by, ConsoleColor::DarkGreen, ConsoleColor::DarkGreen, "  ");
                pintarBloque(bx + 2, by, ConsoleColor::Green, ConsoleColor::Green, "  ");
                pintarBloque(bx, by + 1, ConsoleColor::Green, ConsoleColor::Green, "  ");
                pintarBloque(bx + 2, by + 1, ConsoleColor::DarkGreen, ConsoleColor::DarkGreen, "  ");
                pintarBloque(bx + 1, by + 2, ConsoleColor::DarkRed, ConsoleColor::DarkRed, "  ");
            }
        }

        pintarBloque(58, 12, ConsoleColor::Green, ConsoleColor::Magenta, "* ");
        pintarBloque(50, 26, ConsoleColor::Green, ConsoleColor::Red, "* ");
        pintarBloque(20, 22, ConsoleColor::Green, ConsoleColor::Yellow, "* ");
        pintarBloque(70, 14, ConsoleColor::DarkGreen, ConsoleColor::Green, "()");

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

        array<String^>^ inventario = gcnew array<String^>(CAPACIDAD_MOCHILA);
        array<ConsoleColor>^ coloresInventario = gcnew array<ConsoleColor>(CAPACIDAD_MOCHILA);

        while (!salir) {
            if (!mochilaAgarrada) {
                pintarBloque(mochilaX, mochilaY, ConsoleColor::DarkYellow, ConsoleColor::White, "[M]");
            }

            if (mochilaAgarrada && !diamanteAgarrado) {
                pintarBloque(diamanteX, diamanteY, ConsoleColor::Cyan, ConsoleColor::Blue, "<>");
            }

            pintarBloque(jesseX, jesseY, ConsoleColor::Yellow, ConsoleColor::Black, "JJ");
            pintarBloque(jesseX, jesseY + 1, ConsoleColor::Blue, ConsoleColor::Black, "HH");

            dibujarMochilaInventario(mochilaAbierta, mochilaAgarrada, inventario, coloresInventario);

            UtilidadesConsola::posicionarCursor(12, 1);
            Console::BackgroundColor = ConsoleColor::Black;
            Console::ForegroundColor = ConsoleColor::Yellow;
            Console::Write(" [W][A][S][D]: Mover | [E]: Agarrar Objeto | [C]: Ver Mochila | [ESC]: Salir ");

            UtilidadesConsola::posicionarCursor(18, 29);
            Console::BackgroundColor = ConsoleColor::DarkGreen;
            Console::ForegroundColor = ConsoleColor::White;
            if (!mochilaAgarrada) {
                if (Math::Abs(jesseX - mochilaX) <= 3 && Math::Abs(jesseY - mochilaY) <= 1) {
                    Console::Write(" Estas sobre la Mochila! Presiona [ E ] para recogerla y equiparla ");
                }
                else {
                    Console::Write(" Paso 1: Camina hacia la izquierda y busca la Mochila [M] en el suelo ");
                }
            }
            else if (!diamanteAgarrado) {
                if (Math::Abs(jesseX - diamanteX) <= 3 && Math::Abs(jesseY - diamanteY) <= 1) {
                    Console::Write(" Genial! Presiona [ E ] para recoger el Diamante y guardarlo ");
                }
                else {
                    Console::Write(" Paso 2: Sigue el camino hacia la derecha y encuentra el Diamante (<>) ");
                }
            }
            else {
                Console::Write(" TUTORIAL COMPLETADO! Presiona [C] para revisar tu mochila o [ESC] para salir ");
            }

            if (_kbhit()) {
                int tecla = _getch();
                if (tecla == 224 || tecla == 0) tecla = _getch();

                int prevX = jesseX;
                int prevY = jesseY;
                int nuevoX = jesseX;
                int nuevoY = jesseY;

                if (tecla == 'w' || tecla == 'W' || tecla == 72) {
                    if (jesseY > 10) nuevoY = jesseY - 1;
                }
                else if (tecla == 's' || tecla == 'S' || tecla == 80) {
                    if (jesseY < 26) nuevoY = jesseY + 1;
                }
                else if (tecla == 'a' || tecla == 'A' || tecla == 75) {
                    if (jesseX > 6) nuevoX = jesseX - 2;
                }
                else if (tecla == 'd' || tecla == 'D' || tecla == 77) {
                    if (jesseX < 75) nuevoX = jesseX + 2;
                }
                else if (tecla == 'e' || tecla == 'E') {
                    if (!mochilaAgarrada && Math::Abs(jesseX - mochilaX) <= 3 && Math::Abs(jesseY - mochilaY) <= 1) {
                        animarRecoleccion(jesseX, jesseY, "Mochila", ConsoleColor::Yellow);
                        mochilaAgarrada = true;
                    }
                    else if (mochilaAgarrada && !diamanteAgarrado && Math::Abs(jesseX - diamanteX) <= 3 && Math::Abs(jesseY - diamanteY) <= 1) {
                        animarRecoleccion(jesseX, jesseY, "Diamante", ConsoleColor::Cyan);
                        diamanteAgarrado = true;
                        inventario[0] = "Diamante";
                        coloresInventario[0] = ConsoleColor::Cyan;
                        mochilaAbierta = true;
                    }
                }
                else if (tecla == 'c' || tecla == 'C') {
                    mochilaAbierta = !mochilaAbierta;
                }
                else if (tecla == 27) {
                    salir = true;
                }

                if (!esPosicionSolida(nuevoX, nuevoY) && !esPosicionSolida(nuevoX, nuevoY + 1)) {
                    jesseX = nuevoX;
                    jesseY = nuevoY;
                }

                if (jesseX != prevX || jesseY != prevY) {
                    pintarBloque(prevX, prevY, colorTerrenoBase(prevX, prevY));
                    pintarBloque(prevX, prevY + 1, colorTerrenoBase(prevX, prevY + 1));
                }
            }

            Thread::Sleep(30);
        }
    }

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
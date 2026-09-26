#pragma once
#include "UtilidadesConsola.h"
using namespace System;

namespace DetalleMenu {
    const char* const TITULO = "JESSE'S ADVENTURES";
    const char* const OPCIONES[4] = { "INICIO", "TUTORIAL", "NIVELES", "CREDITOS" };
    const int POSICION_Y_OPCIONES[4] = { 10, 12, 14, 16 };
    const int CENTRO_X = 30;

    void deslizarTexto(const char* texto, int columnaInicial, int filaInicial, int columnaFinal, int filaFinal, int pasos) {
        String^ textoManejado = gcnew String(texto);
        int columnaAnterior = columnaInicial;
        int filaAnterior = filaInicial;

        for (int i = 0; i <= pasos; i++) {
            int columna = columnaInicial + (columnaFinal - columnaInicial) * i / pasos;
            int fila = filaInicial + (filaFinal - filaInicial) * i / pasos;

            UtilidadesConsola::posicionarCursor(columnaAnterior, filaAnterior);
            for (int k = 0; k < textoManejado->Length; k++) Console::Write(" ");

            UtilidadesConsola::posicionarCursor(columna, fila);
            Console::Write(textoManejado);

            columnaAnterior = columna;
            filaAnterior = fila;
            UtilidadesConsola::esperar(15);
        }
    }
}

class MenuPrincipal {
private:
    const int TOTAL_OPCIONES = 4;
    int seleccionActual;

    void animarTitulo() const {
        using namespace DetalleMenu;
        deslizarTexto(TITULO, CENTRO_X - 9, 0, CENTRO_X - 9, 3, 10);
    }

    void animarOpciones() const {
        using namespace DetalleMenu;
        deslizarTexto(OPCIONES[0], 0, POSICION_Y_OPCIONES[0], CENTRO_X, POSICION_Y_OPCIONES[0], 10);
        deslizarTexto(OPCIONES[1], 60, POSICION_Y_OPCIONES[1], CENTRO_X, POSICION_Y_OPCIONES[1], 10);
        deslizarTexto(OPCIONES[2], CENTRO_X, 24, CENTRO_X, POSICION_Y_OPCIONES[2], 10);
        deslizarTexto(OPCIONES[3], 60, POSICION_Y_OPCIONES[3], CENTRO_X, POSICION_Y_OPCIONES[3], 10);
    }

    void dibujarOpciones() const {
        using namespace DetalleMenu;
        for (int i = 0; i < TOTAL_OPCIONES; i++) {
            UtilidadesConsola::posicionarCursor(CENTRO_X - 2, POSICION_Y_OPCIONES[i]);
            Console::Write(gcnew String(i == seleccionActual ? "> " : "  "));
            Console::Write(gcnew String(OPCIONES[i]));
            Console::Write(gcnew String("   "));
        }
    }

public:
    MenuPrincipal() {
        seleccionActual = 0;
    }

    void mostrarEntrada() const {
        UtilidadesConsola::limpiarPantalla();
        UtilidadesConsola::ocultarCursor();
        animarTitulo();
        animarOpciones();
    }

    int ejecutar() {
        mostrarEntrada();

        bool elegido = false;
        while (!elegido) {
            dibujarOpciones();
            ConsoleKey tecla = UtilidadesConsola::obtenerTecla();

            if (tecla == ConsoleKey::UpArrow) {
                seleccionActual = seleccionActual - 1;
                if (seleccionActual < 0) seleccionActual = TOTAL_OPCIONES - 1;
            }
            else if (tecla == ConsoleKey::DownArrow) {
                seleccionActual = seleccionActual + 1;
                if (seleccionActual >= TOTAL_OPCIONES) seleccionActual = 0;
            }
            else if (tecla == ConsoleKey::Enter) {
                elegido = true;
            }
        }

        return seleccionActual;
    }
};


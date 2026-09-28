#pragma once
using namespace System;
using namespace System::Threading; 

namespace UtilidadesConsola {

    void posicionarCursor(int columna, int fila) {
        Console::SetCursorPosition(columna, fila);
    }

    void ocultarCursor() {
        Console::CursorVisible = false;
    }

    void limpiarPantalla() {
        Console::Clear();

    }

    void establecerColor(ConsoleColor color) {
        Console::ForegroundColor = color;
    }

    void esperar(int milisegundos) {
        Thread::Sleep(milisegundos);
    }

    bool teclaPresionada() {
        return Console::KeyAvailable;
    }

    ConsoleKey obtenerTecla() {
        return Console::ReadKey(true).Key;
    }
}
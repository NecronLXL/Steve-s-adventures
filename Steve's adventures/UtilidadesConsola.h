#pragma once
using namespace System;
using namespace System::Threading;

namespace UtilidadesConsola {

    inline void posicionarCursor(int columna, int fila) {
        Console::SetCursorPosition(columna, fila);
    }

    inline void ocultarCursor() {
        Console::CursorVisible = false;
    }

    inline void limpiarPantalla() {
        Console::Clear();
    }

    inline void establecerColor(ConsoleColor color) {
        Console::ForegroundColor = color;
    }

    inline void esperar(int milisegundos) {
        Thread::Sleep(milisegundos);
    }

    inline bool teclaPresionada() {
        return Console::KeyAvailable;
    }

    inline ConsoleKey obtenerTecla() {
        return Console::ReadKey(true).Key;
    }
}

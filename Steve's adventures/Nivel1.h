#pragma once
#include "GestorNivel.h"
#include "DisenoPersonajes.h"

namespace Nivel1 {
    
    inline void fase1_1(GestorNivel& gestor) {
    }

    inline void fase1_2(GestorNivel& gestor) {
    }

    inline void iniciar() {
        GestorNivel gestor(20, 20);
        Jugador* jesse = new Jugador(0, 0, "Jesse");
        gestor.agregarEntidad(jesse);

        fase1_1(gestor);
        fase1_2(gestor);
    }
}

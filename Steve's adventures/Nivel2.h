#pragma once
#include "GestorNivel.h"
#include "DisenoPersonajes.h"

namespace Nivel2 {
    
    inline void fase2_1(GestorNivel& gestor) {
    }

    inline void fase2_2(GestorNivel& gestor) {
    }

    inline void iniciar() {
        GestorNivel gestor(20, 20);
        Jugador* lukas = new Jugador(0, 0, "Lukas");
        gestor.agregarEntidad(lukas);

        fase2_1(gestor);
        fase2_2(gestor);
    }
}

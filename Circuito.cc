#include "Circuito.hh"

Circuito::Circuito() {}

void Circuito::anadir_categoria(Categoria c) { vec_categorias.push_back(c); }

void Circuito::anadir_torneo(Torneo t) { 
    list_torneos.push_back(t);
    list_torneos.sort(cmp);
}

void Circuito::anadir_niveles(int i, vector<int>& v) { vec_categorias[i - 1].anadir_pts_nivel(v); }

void Circuito::eliminar_torneo(string t) {
    list<Torneo>::iterator it = list_torneos.begin();
    while ((*it).consultar_nombre() != t) ++it;
    list_torneos.erase(it);
}

//void Circuito::anadir_participante(string p) {}

void Circuito::iniciar_torneo(string t, const Cjn_Jugadores& j) {
    list<Torneo>::iterator it = list_torneos.begin();
    while ((*it).consultar_nombre() != t) ++it;
    (*it).anadir_participantes(j);
    (*it).crear_emparejamientos();
}

Torneo Circuito::torneo(string s) const {
    list<Torneo>::const_iterator it = list_torneos.begin();
    while ((*it).consultar_nombre() != s) ++it;
    return (*it);
}

int Circuito::num_categorias() const { return vec_categorias.size(); }

int Circuito::num_torneos() const { return list_torneos.size(); }

bool Circuito::existe_torneo(string s) const {
    list<Torneo>::const_iterator it = list_torneos.begin();
    while (it != list_torneos.end() and (*it).consultar_nombre() != s) ++it;
    return (it != list_torneos.end());
}

void Circuito::escribir_categorias() const {
    int n_nvl = vec_categorias[0].num_niveles();
    cout << vec_categorias.size() << " " << n_nvl << endl;
    for (int i = 0; i < vec_categorias.size(); ++i) {
        cout << vec_categorias[i].consultar_nombre();
        for (int j = 0; j < n_nvl; ++j) cout << " " << vec_categorias[i].consultar_pts_nivel(j);
        cout << endl;
    }
}

void Circuito::escribir_torneos() const {
    list<Torneo>::const_iterator it = list_torneos.begin();
    cout << list_torneos.size() << endl;
    while (it != list_torneos.end()) {
        cout << (*it).consultar_nombre() << " " << vec_categorias[(*it).consultar_categoria() - 1].consultar_nombre() << endl;
        ++it;
    }
}

bool Circuito::cmp(Torneo a, Torneo b) { return (a.consultar_nombre() < b.consultar_nombre()); }
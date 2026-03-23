#include "grid.hpp"
#include "solver.hpp"

int main(int argc, char **argv) {
    // TODO(Integracao): carregar grid via load_grid.
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <grid_file>" << std::endl;
        return 1;
    }
    Grid *g = load_grid(argv[1]);
    if (!g) {
        std::cerr << "Error loading grid" << std::endl;
        return 1;
    }
    // TODO(Integracao): chamar solve.
    if (solve(g)) {
        print_grid(g);
    } else {
        std::cout << "No solution found" << std::endl;
    }
    // TODO(Integracao): imprimir resultado com print_grid.

    // TODO(Integracao): libertar memoria com free_grid.
    free_grid(g);
    return 0;
}

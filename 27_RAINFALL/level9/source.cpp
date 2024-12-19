#include <iostream>
#include <cstring>
#include <cstdlib>


class N {
public:
    N(int value) : value(value) {
        memset(annotation, 0, sizeof(annotation));
    }

    void setAnnotation(char* input) {
        memcpy(annotation, input, strlen(input));
    }

    void operator+(N& other) {
        std::cout << "Adding: " << value << " + " << other.value << std::endl;
    }

    void operator-(N& other) {
        std::cout << "Subtracting: " << value << " - " << other.value << std::endl;
    }

private:
    char annotation[104];
    int value;
};

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        std::cerr << "Usage: " << argv[0] << " <annotation>" << std::endl;
        exit(1);
    }

    // Allocation de deux objets N dynamiquement
    N* n1 = new N(5);
    N* n2 = new N(6);

    // Remplit l'annotation avec argv[1]
    n1->setAnnotation(argv[1]);

    // Opération arbitraire via un pointeur indirect
    (*n2) + (*n1);

    delete n1;
    delete n2;

    return 0;
}

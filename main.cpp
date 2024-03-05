#include <iostream>

using namespace std;

const string SECRET_WORD = "MELANCIA";

bool existsInSecretWord(char chute) {
    for(char c: SECRET_WORD) {
        if(c == chute) {
            return true;
        }
    }
    return false;
}

int main() {
    cout << "Bem Vindo ao Jogo da Forca" << endl;
    bool win = false;
    bool dead = false;
    while (!win && !dead) {
        char chute;  
        cout << "Digite o seu chute: ";
        cin >> chute;
        if(existsInSecretWord(chute)) {
            cout << "A palavra secreta contem o chute " << chute << endl;
        };
    }
    
}
#include <iostream>

using namespace std;

const string SECRET_WORD = "MELANCIA";

bool existsInSecretWord(char chute) {
    for (int i = 0; i < SECRET_WORD.length(); i++)
    {
        char c = SECRET_WORD[i];
        if(c == chute) {
            return true;
        }
    }
    for(char c: SECRET_WORD) {
        cout << c;
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
/* * Universidad de La Laguna
* * Escuela Superior de Ingeniería y Tecnología
* * Grado en Ingeniería Informática
* * Asignatura: Informática Básica
* * Curso: 1º
* * Práctica 8 - Funciones
* * Endika Pradera Touzani <alu0101411521@ull.edu.es>
* * Práctica8 - Funcionces.*/



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using String = std::string;


//Utilizo la misma funcion para encriptar/desencriptar porque es lo mismo basicamente
//Cojo el vector, le voy aplicando el xor a cada caracter de cada palabra, lo voy metiendo en otro vector y lo retorno. Se puede hacer mucho mas sencillo pero me da pereza xd
std::vector<String> XOREncDec(std::vector<String> vec){
    std::vector<String> output_vec;
    for(auto &sentence: vec){
        String input_sentence;
        for(auto &word: sentence){
            int xored_word = word ^ 128;  //  El 128 es solo un ejemplo, donde esta el 128 habra que poner un bucle ciclico
            input_sentence += xored_word; //  que vaya por cada caracter de la clave(antes se hara el xor a cada caracter de la clave con 128, supongo ¯\_(ツ)_/¯);
        }
        output_vec.emplace_back(input_sentence);
    }
    return output_vec;
}

/*Utilizo la misma funcion para encriptar/desencriptar pero añadi "mode" en los argumentos para saber cuando
encriptar o desencriptar (No hagan esto lo del mode, es una mierda de solucion, es solo para el ejemplo)*/

//Lo mismo que antes
std::vector<String> CesarsEncDec(std::vector<String> vec, int mode){
    std::vector<String> output_vec;
    for(auto sentence: vec){
        String input_sentence;
        for(auto word: sentence){
            if(mode == 1){              // Mode 1 : Encriptar
                int xored_word = word + 3;
                input_sentence += xored_word;
            } else if (mode == 0){      // Mode 0: Desencriptar
                int xored_word = word - 3;
                input_sentence += xored_word;
            }
        }
        output_vec.emplace_back(input_sentence);
    }
    return output_vec;
}

//Esto nada :)


void MakingOutputFile(String file_name){
    std::ofstream output_file;
    output_file.open(file_name);
}

//Esto es el input handler para saber si encuentra el archivo, el numero de argumentos, -- help etc

void InputHandler(int argc, char* argv[]){
    if(argc == 2 && strcmp(argv[1], "--help") == 0){
        std::cout << "Info del programa, estoy aburrido ahora no lo hare. . .\n";
        exit(EXIT_SUCCESS);
    }
    if(argc != 6){
        std::cout << "Error en el numero de argumentos, pruebe --help para mayor informacion\n";
        exit(EXIT_SUCCESS);
    }
    String input_file_name = argv[1];
    std::ifstream input_file(input_file_name);
    if(input_file.is_open()){
        std::cout << "Found file" << std::endl;
    } else {
        std::cout << "Couldnt open/find file" << std::endl;
        exit(EXIT_SUCCESS);
    }
    int method = atoi(argv[3]);
    if(method != 1 || method != 0){
        std::cout << "Wrong method. Try --help for more information.";
        exit(EXIT_SUCCESS);
    }
    if(strcmp(argv[1], "+") != 0 || strcmp(argv[1], "-") != 0){
        std::cout << "Wrong operation. Try --help for more information.";
        exit(EXIT_SUCCESS);
    }
}


int main(int argc, char* argv[]){
    //InputHandler(argc, argv);
    std::vector<String> input_file_sentences_vec;
    String str;

    //Esto de aqui es para abrir un archivo e ir asignandole el contenido al vector input_file_sentences_vec, esta hecho de una forma de mierda pero funciona ¯\_(ツ)_/¯

    std::ifstream myfile("nose.txt"); //Pongan aqui el nombre del .txt, si no, no funcionara
    if(myfile.is_open()){
        while(getline(myfile, str)) input_file_sentences_vec.emplace_back(str);
        myfile.close();
    } else std::cout << "Unable to open file.\n";

    std::cout << "\n- - - - Original file content - - - -\n" << std::endl;
    for(auto &element: input_file_sentences_vec){
        std::cout << element << std::endl;
    }

    std::cout << "\n- - - - XOR encrypted file content - - - -\n" << std::endl;
    std::vector<String> xor_encrypted_vec = XOREncDec(input_file_sentences_vec);
    for(auto &element: xor_encrypted_vec){
        std::cout << element << std::endl;
    }

    std::cout << "\n- - - - XOR decrypted file content - - - -\n" << std::endl;
    std::vector<String> xor_dencrypted_vec = XOREncDec(xor_encrypted_vec);
    for(auto &element: xor_dencrypted_vec){
        std::cout << element << std::endl;
    }

    std::cout << "\n- - - - Cesar encrypted file content - - - -\n" << std::endl;
    std::vector<String> cesar_encrypted_vec = CesarsEncDec(input_file_sentences_vec, 1);
    for(auto &element: cesar_encrypted_vec){
        std::cout << element << std::endl;
    }
    std::vector<String> cesar_dencrypted_vec = XOREncDec(xor_encrypted_vec);

    std::cout << "\n- - - - Cesar decrypted file content - - - -\n" << std::endl;
    CesarsEncDec(cesar_dencrypted_vec, 0);
    for(auto &element: cesar_dencrypted_vec){
        std::cout << element << std::endl;
    }


    int counter = 0;
    counter++;
    std::cout << counter;
}

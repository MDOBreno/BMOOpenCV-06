//
//  main.cpp
//  BMOOpenCV-06
//
//  Created by Breno Medeiros on 29/03/20.
//  Copyright © 2020 ProgramasBMO. All rights reserved.
//

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

void capturarDFT(Mat& fonte, Mat& destino) {
    Mat originalComplexo[2] = {fonte, Mat::zeros(fonte.size(), CV_32F)};
    Mat prontoParaDft;
    merge(originalComplexo, 2, prontoParaDft);
    
    dft(prontoParaDft, destino, DFT_COMPLEX_OUTPUT);
}

void exibeDFT(Mat& fonte) {
    Mat arrayDividido[2] = {Mat::zeros(fonte.size(), CV_32F), Mat::zeros(fonte.size(), CV_32F)};
    split(fonte, arrayDividido);
    
    // Magnetude: "Equivalente" a tirar o modulo(raiz da soma dos quadrados) do numero Real com o Imaginario
    Mat magnetudeDft;
    magnitude(arrayDividido[0], arrayDividido[1], magnetudeDft);
    magnetudeDft += Scalar::all(1);
    
    log(magnetudeDft, magnetudeDft);        //Calcula o log e insere na mesma matriz
    normalize(magnetudeDft, magnetudeDft, 0, 1, CV_MINMAX);  //Normalizar: significa multiplicar cada valor da matriz por um numero especifico.
    imshow("DFT", magnetudeDft);
    waitKey();
}

int main(int argc, const char * argv[]) {
    // insert code here...
    String caminho = "/Users/brenomedeiros/Documents/ProgramasBMO/Cpp/BMOOpenCV-06/BMOOpenCV-06/";
    String caminhoImagens = "/Users/brenomedeiros/Documents/ProgramasBMO/Cpp/BMOOpenCV-06/BMOOpenCV-06/Images/";
    
    Mat original = imread(caminhoImagens+"Me.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    
    Mat originalFloat;
    original.convertTo(originalFloat, CV_32FC1, 1.0/255.0);
    
    Mat dftDoOriginal;
    capturarDFT(originalFloat, dftDoOriginal);
    
    exibeDFT(dftDoOriginal);
    
    
    return 0;
}

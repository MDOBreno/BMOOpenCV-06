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

void recentralizarDFT(Mat& fonte) {
    int centroX = fonte.cols / 2;
    int centroY = fonte.rows / 2;
    
    Mat q1(fonte, Rect(0,0, centroX, centroY));
    Mat q2(fonte, Rect(centroX,0, centroX, centroY));
    Mat q3(fonte, Rect(0,centroY, centroX, centroY));
    Mat q4(fonte, Rect(centroX,centroY, centroX, centroY));
    
    Mat mapaDeTroca;
    
    q1.copyTo(mapaDeTroca);
    q4.copyTo(q1);
    mapaDeTroca.copyTo(q4);
    
    q2.copyTo(mapaDeTroca);
    q3.copyTo(q2);
    mapaDeTroca.copyTo(q3);
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
    
    recentralizarDFT(magnetudeDft);
    
    namedWindow("DFT", CV_WINDOW_AUTOSIZE);
    imshow("DFT", magnetudeDft);
    moveWindow("DFT", 0, 1080);
    waitKey();
}

void inverterDFT(Mat& fonte, Mat& destino) {
    dft(fonte, destino, DFT_INVERSE | DFT_REAL_OUTPUT | DFT_SCALE);
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
    
    Mat dftInvertido;
    inverterDFT(dftDoOriginal, dftInvertido);
    namedWindow("DFT Invertido", CV_WINDOW_AUTOSIZE);
    imshow("DFT Invertido", dftInvertido);
    moveWindow("DFT Invertido", (dftInvertido.cols/2), 1080);
    waitKey();
    
    return 0;
}

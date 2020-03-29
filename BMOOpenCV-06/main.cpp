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


int main(int argc, const char * argv[]) {
    // insert code here...
    String caminho = "/Users/brenomedeiros/Documents/ProgramasBMO/Cpp/BMOOpenCV-06/BMOOpenCV-06/";
    String caminhoImagens = "/Users/brenomedeiros/Documents/ProgramasBMO/Cpp/BMOOpenCV-06/BMOOpenCV-06/Images/";
    
    Mat original = imread(caminhoImagens+"Me.jpeg", CV_LOAD_IMAGE_GRAYSCALE);
    
    Mat originalFloat;
    original.convertTo(originalFloat, CV_32FC1, 1.0/255.0);
    
    Mat originalComplexo[2] = {originalFloat, Mat::zeros(originalFloat.size(), CV_32F)};
    Mat prontoParaDft;
    merge(originalComplexo, 2, prontoParaDft);
    
    Mat dftDoOriginal;
    dft(prontoParaDft, dftDoOriginal, DFT_COMPLEX_OUTPUT);
    
    
    
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
    ofstream fout("inp_zoom.txt(Rename to inp.txt)");
    double aim_left,aim_right,aim_bottom,aim_top;
    double topi = 1, bottomi = -1, lefti = -2, righti = 1.55;
    double top=topi,bottom=bottomi,left=lefti,right=righti;
    int iters,red,green,blue,frames;
    cout<<"Enter lower bound of real axis: ";
    cin>>aim_left;
    cout<<"Enter upper bound of real axis: ";
    cin>>aim_right;
    cout<<"Enter lower bound of imag. axis: ";
    cin>>aim_bottom;
    cout<<"Enter upper bound of imag. axis: ";
    cin>>aim_top;
    cout<<"Enter number of iterations: ";
    cin>>iters;
    cout<<"Enter Red value: ";
    cin>>red;
    cout<<"Enter Green value: ";
    cin>>green;
    cout<<"Enter Blue value: ";
    cin>>blue;
    cout<< "Enter number of frames: ";
    cin>>frames;
    double fact;
    int i=0;
    for(i=0;(top-aim_top)>=(aim_top-aim_bottom)*0.01 && i<frames;i++){
        fact = exp(-(double)i/200.0);
        top = (topi-aim_top)*fact + aim_top;
        left = (lefti-aim_left)*fact + aim_left;
        right = (righti-aim_right)*fact + aim_right;
        bottom = (bottomi-aim_bottom)*fact + aim_bottom;
        fout<<"zoom"<<i<<".bmp 1920 1080 "<<left<<" "<<right<<" "<<bottom<<" "<<top<<" "<<iters<<" 255 255 255\n";
    }
    cout<<"Created instructions for "<<i<<" frames!";
}

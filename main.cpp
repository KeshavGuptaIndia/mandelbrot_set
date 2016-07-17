#include <iostream>
#include <fstream>
#include <string>
using namespace std;

double maptoreal(double x,double minr,double maxr,int imagewidth)
{
    return (x/(double)imagewidth)*(maxr-minr) + minr;
}

double maptoimag(double y,double mini,double maxi,int imageheight)
{
    return (y/(double)imageheight)*(maxi-mini) + mini;
}

int finditers(double r,double i, int maxiter)
{
    int n = 0;
    double tempr,tempi;
    double ci =0,cr=0;
    for(n = 0; n<maxiter; n++)
    {
        tempr = cr*cr - ci*ci + r;
        tempi = 2*cr*ci + i;
        cr = tempr;
        ci = tempi;
        if(cr*cr + ci*ci > 4.0)
        {
            return n;
        }
    }
    return 0;
}

int main(int argc, const char * argv[])
{
    cout<<"Enter one command per line in the format:\n"
        <<"<output file> <width> <height> <min real> <max real> <min imag> <max imag> <iterations> <red> <blue> <green>\n\n";
    ifstream incmd("inp.txt",ios::binary);
    if(!incmd)
    {
        cout<<"Failed to open input commands file!";
        return 0;
    }

    ofstream outppm;
    int imageheight;
    int imagewidth;
    int maxiters;
    double minreal;
    double maxreal;
    double minimag;
    double maximag;
    string filename;
    double cr;
    double ci;
    int iters;
    char r;
    char g;
    char b;
    int paddedwidth;
    int padcells;
    int sizeImg;
    char padding = 0;
    double t;
    int r_max=0,g_max=0,b_max=255;

    while(!incmd.eof())
    {
        incmd>>filename;
        outppm.open(filename);

        incmd>>imagewidth;
        incmd>>imageheight;
        paddedwidth = (imagewidth*3)+((imagewidth*3)%4?((-imagewidth*3)%4+4):0);
        padcells = paddedwidth-3*imagewidth;
        sizeImg = paddedwidth*imageheight + 54;
        incmd>>minreal;
        incmd>>maxreal;
        incmd>>minimag;
        incmd>>maximag;
        incmd>>maxiters;
        incmd>>r_max>>g_max>>b_max;

        char bmpHdr[54]=   {66,  77,  sizeImg%256,  (sizeImg/256)%256,   (sizeImg/65536)%256,   (sizeImg/16777216)%256,   0,   0,   0,   0,  54,   0,   0,   0,  40,   0,
                            0,   0,   imagewidth%256,   imagewidth/256,   0,   0,   imageheight%256,   imageheight/256,   0,   0,   1,   0,  24,   0,   0,   0,
                            0,   0,   (sizeImg-54)%256,  ((sizeImg-54)/256)%256,   ((sizeImg-54)/65536)%256,   ((sizeImg-54)/16777216)%256,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                            0,   0,   0,   0,   0,   0
                           };

        if(!outppm)
        {
            cout<<"Enable to open output file "<<filename<<"!"<<endl;
            continue;
        }

        outppm.write((char*)bmpHdr,sizeof(bmpHdr));

        for(int y=0; y<imageheight; y++)
        {
            for(int x=0; x<imagewidth; x++)
            {
                cr = maptoreal(x,minreal,maxreal,imagewidth);
                ci = maptoimag(y,minimag,maximag,imageheight);
                iters = finditers(cr,ci,maxiters);
                t=(double)iters/(double)maxiters;
                b=t*b_max;
                t*=t;
                r=t*r_max;
                t*=t;
                g=t*g_max;
                if(r==10 or r==13) r-=1;
                if(g==10 or g==13) g-=1;
                if(b==10 or b==13) b-=1;
                outppm.write(&b,1);
                outppm.write(&g,1);
                outppm.write(&r,1);
            }
            cout<<"computing row number "<<y<<endl;
            for(int i=0; i<padcells; i++)
            {
                outppm.write(&padding,1);
            }
        }
    outppm.close();
    }
    incmd.close();
    return 0;
}

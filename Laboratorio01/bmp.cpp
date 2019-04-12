#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

unsigned char* ReadBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");

    //Se lee la cabecera que es de 54 bytes
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    // Se extrae el ancho y alto de la imagen
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];

    cout << endl;
    cout << "Name: " << filename << endl;
    cout << " Width: " << width << endl;
    cout << " Height: " << height << endl;

    int size = 3 * width * height;
    unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
    fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
    fclose(f);

    for(i = 0; i < size; i += 3)
    {
        unsigned char tmp = data[i];
        data[i] = data[i+2];
        data[i+2] = tmp;
        // cout << "R: "<< (int)data[i] << " G: " << (int)data[i+1]<< " B: " << (int)data[i+2]<< endl;
    }

    // cv::Mat image(height, width, CV_8UC3,data);
    cv::Mat image(height, width, CV_8UC3);

    for(int i=0; i<width; i++)
    {
      int c=0;
      for(int j=0; j<height*3; j+=3)
      {
        cout<<"C: "<<c<<endl;
        Vec3b color = image.at<Vec3b>(Point(i,c));
        color[0]=(int)data[width*i+j];
        cout<<(int)data[width*i+j]<<endl;
        color[1]=(int)data[width*i+j+ 1];
        cout<<(int)data[width*i+j+1]<<endl;
        color[2]=(int)data[width*i+j+ 2];
        cout<<(int)data[width*i+j+2]<<endl;
        image.at<Vec3b>(Point(i,c)) = color;
        c++;
      }
    }

    // for(int y=0;y<height;y++)
    // {
    //   // cout<<"y: "<<y<<endl;
    //     for(int x=0; x<width; x += 3)
    //     {
    //         // cout<<"x: "<<x<<endl;
    //         // get pixel
    //         Vec3b color = image.at<Vec3b>(Point(x,y));
    //
    //         color[0]=(int)data[3*(y*width+x)];
    //         // color[0]=240;
    //         // color[1]=(;
    //         color[1]=(int)data[3 * (y * width + x) + 1];
    //         // color[2]=(int)data[x+2];
    //         color[2]=(int)data[3 * (y * width + x) + 2];
    //
    //         // set pixel
    //         image.at<Vec3b>(Point(x,y)) = color;
    //     }
    // }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image );                   // Show our image inside it.
    cv::waitKey(0);

    return data;
}

int main(){
  cout<<"Hola"<<endl;
  // unsigned char* data = readBMP("Perro.bmp");
  unsigned char* data = ReadBMP("imagen.bmp");
  // cout<<(int)(&data)<<endl;
  cout<<"mundo"<<endl;
}

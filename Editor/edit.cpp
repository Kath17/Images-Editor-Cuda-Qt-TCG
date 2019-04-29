#include "edit.h"

void show_Image(string direccion)
{
    Mat image;
    image = imread(direccion, CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
    }

//    namedWindow( "Imagen original", WINDOW_AUTOSIZE );// Create a window for display.
//    imshow( "Imagen original", image );                   // Show our image inside it.

//    waitKey(0);                                          // Wait for a keystroke in the window
}

Mat Suma(string direccion, double numero)
{
    Mat image;
    image= imread(direccion, CV_LOAD_IMAGE_COLOR);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            double b = image.at<Vec3b>(i, j)[0] + numero;
            if(b > 255)
                image.at<Vec3b>(i,j)[0] = 255;
            else if(b < 0)
                image.at<Vec3b>(i,j)[0] = 0;
            else
                image.at<Vec3b>(i,j)[0] += numero;

            double g = image.at<Vec3b>(i, j)[1] + numero;
            if(g > 255)
                image.at<Vec3b>(i,j)[1] = 255;
            else if (g<0)
                image.at<Vec3b>(i,j)[1] = 0;
            else
                image.at<Vec3b>(i,j)[1] += numero;

            double r = image.at<Vec3b>(i, j)[2] + numero;
            if(r > 255)
                image.at<Vec3b>(i,j)[2] = 255;
            else if(r<0)
                image.at<Vec3b>(i,j)[2] = 0;
            else
                image.at<Vec3b>(i,j)[2] += numero;
        }
    }
//    namedWindow( "Imagen modificada", WINDOW_AUTOSIZE );
//    normalize(image, image, 0, 1, cv::NORM_MINMAX);
//    imshow("Imagen modificada", image);
    return image;
}

Mat Multiplicacion(string direccion, double numero)
{
    Mat image;
    image= imread(direccion, CV_LOAD_IMAGE_COLOR);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            double b = image.at<Vec3b>(i, j)[0] * numero;
            if(b > 255)
                image.at<Vec3b>(i,j)[0] = 255;
            else if(b < 0)
                image.at<Vec3b>(i,j)[0] = 0;
            else
                image.at<Vec3b>(i,j)[0] *= numero;

            double g = image.at<Vec3b>(i, j)[1] * numero;
            if(g > 255)
                image.at<Vec3b>(i,j)[1] = 255;
            else if (g<0)
                image.at<Vec3b>(i,j)[1] = 0;
            else
                image.at<Vec3b>(i,j)[1] *= numero;

            double r = image.at<Vec3b>(i, j)[2] * numero;
            if(r > 255)
                image.at<Vec3b>(i,j)[2] = 255;
            else if(r<0)
                image.at<Vec3b>(i,j)[2] = 0;
            else
                image.at<Vec3b>(i,j)[2] *= numero;
        }
    }
//    namedWindow( "Imagen modificada", WINDOW_AUTOSIZE );
//    normalize(image, image, 0, 1, cv::NORM_MINMAX);
//    imshow("Imagen modificada", image);
    return image;
}

Mat Division(string direccion, double numero)
{
    Mat image;
    image= imread(direccion, CV_LOAD_IMAGE_COLOR);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            double b = image.at<Vec3b>(i, j)[0] / numero;
            if(b > 255)
                image.at<Vec3b>(i,j)[0] = 255;
            else if(b < 0)
                image.at<Vec3b>(i,j)[0] = 0;
            else
                image.at<Vec3b>(i,j)[0] /= numero;

            double g = image.at<Vec3b>(i, j)[1] / numero;
            if(g > 255)
                image.at<Vec3b>(i,j)[1] = 255;
            else if (g<0)
                image.at<Vec3b>(i,j)[1] = 0;
            else
                image.at<Vec3b>(i,j)[1] /= numero;

            double r = image.at<Vec3b>(i, j)[2] / numero;
            if(r > 255)
                image.at<Vec3b>(i,j)[2] = 255;
            else if(r<0)
                image.at<Vec3b>(i,j)[2] = 0;
            else
                image.at<Vec3b>(i,j)[2] /= numero;
        }
    }
//    namedWindow( "Imagen modificada", WINDOW_AUTOSIZE );
//    normalize(image, image, 0, 1, cv::NORM_MINMAX);
//    imshow("Imagen modificada", image);
    return image;
}

Mat to_Gris(string direccion)
{
    Mat image;
    image= imread(direccion, CV_LOAD_IMAGE_COLOR);
    Mat image2(image.rows, image.cols, CV_8UC1);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            double b = image.at<Vec3b>(i, j)[0];
            double g = image.at<Vec3b>(i, j)[1];
            double r = image.at<Vec3b>(i, j)[2];

            image2.at<uchar>(i,j) = (0.21)*r + (0.72)*g + (0.07)*b;
        }
    }
//    namedWindow( "Imagen modificada", WINDOW_AUTOSIZE );
//    imshow("Imagen modificada", image2);
    return image2;
}

Mat Histograma(Mat src)
{
//    Mat src = imread( direccion, IMREAD_COLOR );

    vector<Mat> bgr_planes;
    split( src, bgr_planes );
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;

    calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
    calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 255,255,255) );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    for( int i = 1; i < histSize; i++ )
    {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ),
              Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }
    return histImage;
}

Mat Histograma_grises(Mat image)
{
    // allcoate memory for no of pixels for each intensity value
    int histogram[256];

    // initialize all intensity values to 0
    for(int i = 0; i < 255; i++)
    {
        histogram[i] = 0;
    }

    // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;

    for(int i = 0; i < 256; i++)
        cout<<histogram[i]<<" ";

    // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double) hist_w/256);

    Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(255, 255, 255));

    // find the maximum intensity element from histogram
    int max = histogram[0];
    for(int i = 1; i < 256; i++){
        if(max < histogram[i]){
            max = histogram[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows

    for(int i = 0; i < 255; i++){
        histogram[i] = ((double)histogram[i]/max)*histImage.rows;
    }

    // draw the intensity line for histogram
    for(int i = 0; i < 255; i++)
    {
        line(histImage, Point(bin_w*(i), hist_h),
                              Point(bin_w*(i), hist_h - histogram[i]),
             Scalar(0,0,0), 1, 8, 0);
    }
    return histImage;
}

void Show(Mat image1, Mat image2, Mat image3, Mat image4)
{
    imshow("Original",image1);
    imshow("Histograma_O",image2);
    imshow("Modificada",image3);
    imshow("Histograma_M",image4);

    cv::moveWindow("Original", 150, 50);
    cv::moveWindow("Histograma_O", image1.cols+150, 50);
    cv::moveWindow("Modificada", 150, image2.rows+100);
    cv::moveWindow("Histograma_M", image1.cols+150, image2.rows+100);
}

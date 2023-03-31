#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Image {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;

    bool Compare(Image &image);
    void Add(string, int);
    void Scale(string, int);
    void IsolateChannel(string value);
    void SetDimension(int, int);

    struct Pixel {
        unsigned char red;
        unsigned char green;
        unsigned char blue;

    };

    vector<Pixel> pixels;
};

    Image readFile(string file) {
        Image headerObject;
        ifstream inFile(file, ios_base::binary);

        inFile.read( &headerObject.idLength, sizeof(headerObject.idLength));
        inFile.read( &headerObject.colorMapType, sizeof(headerObject.colorMapType));
        inFile.read( &headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
        inFile.read((char*) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
        inFile.read((char*) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
        inFile.read((char*) &headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
        inFile.read((char*) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
        inFile.read((char*) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
        inFile.read((char*) &headerObject.width, sizeof(headerObject.width));
        inFile.read((char*) &headerObject.height, sizeof(headerObject.height));
        inFile.read((char*) &headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
        inFile.read((char*) &headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

        for(int i = 0; i < headerObject.height * headerObject.width; i++) {
            Image::Pixel temp;
            inFile.read((char*) &temp.blue, sizeof(temp.blue));
            inFile.read((char*) &temp.green, sizeof(temp.green));
            inFile.read((char*) &temp.red, sizeof(temp.red));
            headerObject.pixels.push_back(temp);
        }
        inFile.close();
        return headerObject;
    }

    void writeFile(string file, Image headerObject) {
        ofstream outFile(file, ios_base::binary);
        if(outFile.is_open()) {
            outFile.write((char*) &headerObject.idLength, sizeof(headerObject.idLength));
            outFile.write((char*) &headerObject.colorMapType, sizeof(headerObject.colorMapType));
            outFile.write((char*) &headerObject.dataTypeCode, sizeof(headerObject.dataTypeCode));
            outFile.write((char*) &headerObject.colorMapOrigin, sizeof(headerObject.colorMapOrigin));
            outFile.write((char*) &headerObject.colorMapLength, sizeof(headerObject.colorMapLength));
            outFile.write((char*) &headerObject.colorMapDepth, sizeof(headerObject.colorMapDepth));
            outFile.write((char*) &headerObject.xOrigin, sizeof(headerObject.xOrigin));
            outFile.write((char*) &headerObject.yOrigin, sizeof(headerObject.yOrigin));
            outFile.write((char*) &headerObject.width, sizeof(headerObject.width));
            outFile.write((char*) &headerObject.height, sizeof(headerObject.height));
            outFile.write((char*) &headerObject.bitsPerPixel, sizeof(headerObject.bitsPerPixel));
            outFile.write((char*) &headerObject.imageDescriptor, sizeof(headerObject.imageDescriptor));

            for (unsigned int i = 0; i < headerObject.pixels.size(); i++) {
                outFile.write((char*) &headerObject.pixels[i].blue, 1);
                outFile.write((char*) &headerObject.pixels[i].green, 1);
                outFile.write((char*) &headerObject.pixels[i].red, 1);
            }
        }
    }

    void printInfo(Image headerObject) {
        cout << "ID Length: " << headerObject.idLength << endl;
        cout << "Color Map Type: " << headerObject.colorMapType << endl;
        cout << "Data Type Code: " << headerObject.dataTypeCode << endl;
        cout << "Color Map Origin: " << headerObject.colorMapOrigin << endl;
        cout << "Color Map Length: " << headerObject.colorMapLength << endl;
        cout << "Color Map Depth: " << headerObject.colorMapDepth << endl;
        cout << "X Origin: " << headerObject.xOrigin << endl;
        cout << "Y Origin: " << headerObject.yOrigin << endl;
        cout << "Width: " << headerObject.width << endl;
        cout << "Height: " << headerObject.height << endl;
        cout << "Bits Per Pixel: " << headerObject.bitsPerPixel << endl;
        cout << "Image Descriptor: " << headerObject.imageDescriptor << endl;
    }

    bool Image::Compare(Image &image) {
        bool same = true;
        if(this->idLength != image.idLength) {
            same = false;
            cout << "idLength does not match" << endl;
        }
        if(this->colorMapType != image.colorMapType) {
            same = false;
            cout << "colorMapType does not match" << endl;
        }
        if(this->dataTypeCode != image.dataTypeCode) {
            same = false;
            cout << "dataTypeCode does not match" << endl;
        }
        if(this->colorMapOrigin != image.colorMapOrigin) {
            same = false;
            cout << "colorMapOrigin does not match" << endl;
        }
        if(this->colorMapLength != image.colorMapLength) {
            same = false;
            cout << "colorMapLength does not match" << endl;
        }
        if(this->colorMapDepth != image.colorMapDepth) {
            same = false;
            cout << "colorMapDepth does not match" << endl;
        }
        if(this->xOrigin != image.xOrigin) {
            same = false;
            cout << "xOrigin does not match" << endl;
        }
        if(this->yOrigin != image.yOrigin) {
            same = false;
            cout << "yOrigin does not match" << endl;
        }
        if(this->width != image.width) {
            same = false;
            cout << "width does not match" << endl;
        }
        if(this->height != image.height) {
            same = false;
            cout << "height does not match" << endl;
        }
        if(this->bitsPerPixel != image.bitsPerPixel) {
            same = false;
            cout << "bitsPerPixel does not match" << endl;
        }
        if(this->imageDescriptor != image.imageDescriptor) {
            same = false;
            cout << "imageDescriptor does not match" << endl;
        }
        if(pixels.size() != image.pixels.size()) {
            same = false;
            cout << "Pixels not the same" << endl;
        }
        return same;
    }

    void Image::Add(string channel, int value) {
        if (channel == "blue") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].blue + value) > 255) {
                    pixels[i].blue = 255;
                }
                else {
                    pixels[i].blue += value;
                }
            }
        }
        if (channel == "green") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].green + value) > 255) {
                    pixels[i].green = 255;
                }
                else {
                    pixels[i].green += value;
                }
            }
        }
        if (channel == "red") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].red + value) > 255) {
                    pixels[i].red = 255;
                }
                else {
                    pixels[i].red += value;
                }
            }
        }
    }

    void Image::Scale(string channel, int value) {
        if (channel == "blue") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].blue * value) > 255) {
                    pixels[i].blue = 255;
                }
                else {
                    pixels[i].blue *= value;
                }
            }
        }
        if (channel == "green") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].green * value) > 255) {
                    pixels[i].green = 255;
                }
                else {
                    pixels[i].green *= value;
                }
            }
        }
        if (channel == "red") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                if((pixels[i].red * value) > 255) {
                    pixels[i].red = 255;
                }
                else {
                    pixels[i].red *= value;
                }
            }
        }
    }

    void Image::IsolateChannel(string channel) {
        int value;
        if(channel == "blue") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                value = pixels[i].blue;
                pixels[i].green = value;
                pixels[i].red = value;
            }
        }
        if(channel == "green") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                value = pixels[i].green;
                pixels[i].blue = value;
                pixels[i].red = value;
            }
        }
        if(channel == "red") {
            for(unsigned int i = 0; i < pixels.size(); i++) {
                value = pixels[i].red;
                pixels[i].green = value;
                pixels[i].blue = value;
            }
        }
    }

    void Image::SetDimension(int height, int width) {
        this->height = height;
        this->width = width;
    }

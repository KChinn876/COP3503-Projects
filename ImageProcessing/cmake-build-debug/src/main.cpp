#include <iostream>
#include "Image.h"
using namespace std;

float Normalize(int value) {
    return (value/255.0f);
}

float Clamp(float value){
    if(value > 255) { value = 255;}
    if(value < 0) { value = 0;}
    return value;
}

void Multiply(Image &a, Image &b) {
    for(unsigned int i = 0; i < a.pixels.size(); i++) {
        a.pixels[i].blue = (unsigned char) ((((float) a.pixels[i].blue * (float) b.pixels[i].blue) / 255.0f) + 0.5f);
        a.pixels[i].green = (unsigned char) ((((float) a.pixels[i].green * (float) b.pixels[i].green) / 255.0f) + 0.5f);
        a.pixels[i].red = (unsigned char) ((((float) a.pixels[i].red * (float) b.pixels[i].red) / 255.0f) + 0.5f);
    }
}

void Screen(Image &a, Image &b) {
    float blue;
    float green;
    float red;
    for(unsigned int i = 0; i < a.pixels.size(); i++) {
        blue = (1.0f - (1.0f - Normalize(a.pixels[i].blue)) * (1.0 - Normalize(b.pixels[i].blue)));
        green = (1.0f - (1.0f - Normalize(a.pixels[i].green)) * (1.0 - Normalize(b.pixels[i].green)));
        red = (1.0f - (1.0f - Normalize(a.pixels[i].red)) * (1.0 - Normalize(b.pixels[i].red)));

        a.pixels[i].blue = (unsigned char)Clamp((blue * 255.0) + 0.5f);
        a.pixels[i].green = (unsigned char)Clamp((green * 255.0) + 0.5f);
        a.pixels[i].red = (unsigned char)Clamp((red * 255.0) + 0.5f);
    }
}

void Subtract(Image &a, Image &b) {
    float blue;
    float green;
    float red;
    for(unsigned int i = 0; i < a.pixels.size(); i++) {
        blue = ((float)b.pixels[i].blue - (float)a.pixels[i].blue);
        green = ((float)b.pixels[i].green - (float)a.pixels[i].green);
        red = ((float)b.pixels[i].red - (float)a.pixels[i].red);

        blue = Clamp(blue);
        green = Clamp(green);
        red = Clamp(red);

        a.pixels[i].blue = (unsigned char)blue;
        a.pixels[i].green = (unsigned char)green;
        a.pixels[i].red = (unsigned char)red;
    }
}

void ScaleRed(Image &red, int value) {
    for(unsigned int i = 0; i < red.pixels.size(); i++) {
        int r = red.pixels[i].red;
        r *= value;
        red.pixels[i].red = (unsigned char)Clamp(r);
    }
}

void ScaleBlue(Image &blue, int value) {
    for(unsigned int i = 0; i < blue.pixels.size(); i++) {
        int b = blue.pixels[i].blue;
        b *= value;
        blue.pixels[i].blue = (unsigned char)Clamp(b);
    }
}

void Overlay(Image &top, Image &bottom) {
    for(int i = 0; i < top.pixels.size(); i++) {
        float r, g, b;
        if(bottom.pixels[i].red < 128) {
            r = ((2 * (Normalize(top.pixels[i].red) * Normalize(bottom.pixels[i].red))) * 255) + 0.5f;
        }
        else {
            r = ((1 - 2 * (1 - Normalize(top.pixels[i].red)) * (1 - Normalize(bottom.pixels[i].red))) * 255) + 0.5f;
        }
        if(bottom.pixels[i].green < 128) {
            g = ((2 * (Normalize(top.pixels[i].green) * Normalize(bottom.pixels[i].green))) * 255) + 0.5f;
        }
        else {
            g = ((1 - 2 * (1 - Normalize(top.pixels[i].green)) * (1 - Normalize(bottom.pixels[i].green))) * 255) + 0.5f;
        }
        if(bottom.pixels[i].blue < 128) {
            b = ((2 * (Normalize(top.pixels[i].blue) * Normalize(bottom.pixels[i].blue))) * 255) + 0.5f;
        }
        else {
            b = ((1 - 2 * (1 - Normalize(top.pixels[i].blue)) * (1 - Normalize(bottom.pixels[i].blue))) * 255) + 0.5f;
        }
        top.pixels[i].blue = (unsigned char)Clamp(b);
        top.pixels[i].green = (unsigned char)Clamp(g);
        top.pixels[i].red = (unsigned char)Clamp(r);
    }
}

void Combine(Image &red, Image &green, Image &blue) {
    for(unsigned int i = 0; i < red.pixels.size(); i++) {
        red.pixels[i].green = green.pixels[i].green;
        red.pixels[i].blue = blue.pixels[i].blue;
    }
}

void Rotate(Image &a, Image &b) {
    int num = 0;
    for(unsigned int i = a.pixels.size() - 1; i > 0; i--) {
        b.pixels[i] = a.pixels[num];
        num++;
    }
}

void StitchHorizontal(Image &a, Image &b) {
    int totalWidth = a.width + b.width;
    int height = a.height;
    int width = a.width;
    bool goLeft = true;
    vector<Image::Pixel> pixel;
    for(unsigned int i = 0; i < height; i++) {
        int index = 0;
        while(goLeft) {
            if(index == width) {
                goLeft = false;
                break;
            }
            pixel.push_back(a.pixels[i * height + index]);
            index++;
        }
        index = 0;
        while(!goLeft) {
            if(index == width) {
                goLeft = true;
                break;
            }
            pixel.push_back(b.pixels[i * height + index]);
            index++;
        }
    }
    a.SetDimension(height, totalWidth);
    a.pixels = pixel;
}

void StitchVertical(Image &a, Image &b) {
    int totalHeight = a.height + b.height;
    int width = a.width;

    a.SetDimension(totalHeight, width);
    vector<Image::Pixel> pixel;
    for(unsigned int i = 0; i < b.pixels.size(); i++) {
        pixel.push_back(b.pixels[i]);
    }
    for(unsigned int i = 0; i < a.pixels.size(); i++) {
        pixel.push_back(a.pixels[i]);
    }
    a.pixels = pixel;
}

int main() {

// Import Examples
    Image example1 = readFile("examples/EXAMPLE_part1.tga");
    Image example2 = readFile("examples/EXAMPLE_part2.tga");
    Image example3 = readFile("examples/EXAMPLE_part3.tga");
    Image example4 = readFile("examples/EXAMPLE_part4.tga");
    Image example5 = readFile("examples/EXAMPLE_part5.tga");
    Image example6 = readFile("examples/EXAMPLE_part6.tga");
    Image example7 = readFile("examples/EXAMPLE_part7.tga");
    Image example8b = readFile("examples/EXAMPLE_part8_b.tga");
    Image example8g = readFile("examples/EXAMPLE_part8_g.tga");
    Image example8r = readFile("examples/EXAMPLE_part8_r.tga");
    Image example9 = readFile("examples/EXAMPLE_part9.tga");
    Image example10 = readFile("examples/EXAMPLE_part10.tga");
    Image exampleEC = readFile("examples/EXAMPLE_extracredit.tga");


// Import Input Files
    Image layer1 = readFile("input/layer1.tga");
    Image pattern1 = readFile("input/pattern1.tga");
    Image layer2 = readFile("input/layer2.tga");
    Image car = readFile("input/car.tga");
    Image _layer1 = readFile("input/layer1.tga");
    Image pattern2 = readFile("input/pattern2.tga");
    Image text1 = readFile("input/text.tga");
    Image _layer2 = readFile("input/layer2.tga");
    Image circles = readFile("input/circles.tga");
    Image _pattern2 = readFile("input/pattern2.tga");
    Image layerOne = readFile("input/layer1.tga");
    Image patternOne = readFile("input/pattern1.tga");
    Image layerRed = readFile("input/layer_red.tga");
    Image layerGreen = readFile("input/layer_green.tga");
    Image layerBlue = readFile("input/layer_blue.tga");
    Image text2 = readFile("input/text2.tga");
    Image car_red = readFile("input/car.tga");
    Image car_green = readFile("input/car.tga");
    Image car_blue = readFile("input/car.tga");
    Image carEC = readFile("input/car.tga");
    Image circlesEC = readFile("input/circles.tga");
    Image pattern1EC = readFile("input/pattern1.tga");
    Image textEC = readFile("input/text.tga");
    Image ECTop = readFile("output/ECTop.tga");
    Image ECBottom = readFile("output/ECBottom.tga");


// Test 1

     cout << "\n+=+=+=Test 1=+=+=+" << endl;
    Multiply(layer1, pattern1);
    cout << "Multiplied layer1.tga and pattern1.tga" << endl;
    writeFile("output/part1.tga", layer1);
    cout << "Output: part1.tga" << endl;
    Image part1 = readFile("output/part1.tga");
    // Compare
    if(part1.Compare(example1)) {
        cout << "Test 1 Passed" << endl << endl;
    } else {
        cout << "Test 1 Failed" << endl << endl;
    }

// Test 2

    cout << "+=+=+=Test 2=+=+=+" << endl;
    Subtract(layer2, car);
    cout << "Subtracted layer2.tga from car.tga" << endl;
    writeFile("output/part2.tga", layer2);
    cout << "Output: part2.tga" << endl;
    Image part2 = readFile("output/part2.tga");
    // Compare
    if(part2.Compare(example2)) {
        cout << "Test 2 Passed" << endl << endl;
    } else {
        cout << "Test 2 Failed" << endl << endl;
    }

// Test 3

    cout << "+=+=+=Test 3=+=+=+" << endl;
    Multiply(_layer1, pattern2);
    cout << "Multiplied layer1 and pattern2" << endl;
    writeFile("output/part3.tga", _layer1);
    Image part3 = readFile("output/part3.tga");
    cout << "Loaded part3.tga" << endl;
    Screen(_layer1, text1);
    cout << "Screen: text.tga and layer1.tga" << endl;
    writeFile("output/part3.tga", _layer1);
    cout << "Output: part3.tga" << endl;
    // Compare
    if(_layer1.Compare(example3)) {
        cout << "Test 3 Passed" << endl << endl;
    } else {
        cout << "Test 3 Failed" << endl << endl;
    }

// Test 4

    cout << "+=+=+=Test 4=+=+=+" << endl;
    Multiply(_layer2, circles);
    cout << "Multiplied layer2.tga and circles.tga" << endl;
    writeFile("output/part4.tga", _layer2);
    cout << "Output: part4.tga" << endl;
    Image part4 = readFile("output/part4.tga");
    cout << "Loaded part4.tga" << endl;
    Subtract(_pattern2, part4);
    cout << "Subtracted pattern2.tga from part4.tga" << endl;
    writeFile("output/part4.tga", _pattern2);
    cout << "Output: part4.tga" << endl;
    // Compare
    if(part4.Compare(example4)) {
        cout << "Test 4 Passed" << endl << endl;
    } else {
        cout << "Test 4 Failed" << endl << endl;
    }

// Test 5

    cout << "+=+=+=Test 5=+=+=+" << endl;
    Image testLayer1 = readFile("input/layer1.tga");
    Image testPattern1 = readFile("input/pattern1.tga");
    Overlay(testLayer1, testPattern1);
    cout << "Overlay: layer1.tga and pattern1.tga" << endl;
    writeFile("output/part5.tga", testLayer1);
    cout << "Output: part5.tga" << endl;
    Image part5 = readFile("output/part5.tga");
    // Compare
    if(part5.Compare(example5)) {
        cout << "Test 5 Passed" << endl << endl;
    } else {
        cout << "Test 5 Failed" << endl << endl;
    }

// Test 6

    cout << "+=+=+=Test 6=+=+=+" << endl;
    car.Add("green", 200);
    cout << "Added 200 to green channel in car.tga" << endl;
    writeFile("output/part6.tga", car);
    cout << "Output: part6.tga" << endl;
    Image part6 = readFile("output/part6.tga");
    // Compare
    if(part6.Compare(example6)) {
        cout << "Test 6 Passed" << endl << endl;
    } else {
        cout << "Test 6 Failed" << endl << endl;
    }

// Test 7

    cout << "+=+=+=Test 7=+=+=+" << endl;
    //car.Scale("red", 4);
    Image _car = readFile("input/car.tga");
    ScaleRed(_car, 4);
    cout << "Scaled red channel by 4 in car.tga" << endl;
    //car.Scale("blue", 0);
    ScaleBlue(_car, 0);
    cout << "Scaled blue channel by 0 in car.tga" << endl;
    writeFile("output/part7.tga", _car);
    cout << "Output: part7.tga" << endl;
    Image part7 = readFile("output/part7.tga");
    // Compare
    if(part7.Compare(example7)) {
        cout << "Test 7 Passed" << endl << endl;
    } else {
        cout << "Test 7 Failed" << endl << endl;
    }

// Test 8

    // Red

    cout << "+=+=+=Test 8=+=+=+" << endl;
    car_red.IsolateChannel("red");
    writeFile("output/part8_r.tga", car_red);
    cout << "Output: part8_r.tga" << endl;
    Image part8_r = readFile("output/part8_r.tga");
    // Compare
    if(part8_r.Compare(example8r)) {
        cout << "Test 8r Passed" << endl << endl;
    } else {
        cout << "Test 8r Failed" << endl << endl;
    }

    // Green

    car_green.IsolateChannel("green");
    writeFile("output/part8_g.tga", car_green);
    cout << "Output: part8_g.tga" << endl;
    Image part8_g = readFile("output/part8_g.tga");
    // Compare
    if(part8_g.Compare(example8g)) {
        cout << "Test 8g Passed" << endl << endl;
    } else {
        cout << "Test 8g Failed" << endl << endl;
    }

    // Blue

    car_blue.IsolateChannel("blue");
    writeFile("output/part8_b.tga", car_blue);
    cout << "Output: part8_b.tga" << endl;
    Image part8_b = readFile("output/part8_b.tga");
    // Compare
    if(part8_b.Compare(example8b)) {
        cout << "Test 8b Passed" << endl << endl;
    } else {
        cout << "Test 8b Failed" << endl << endl;
    }

// Test 9

    cout << "+=+=+=Test 9=+=+=+" << endl;
    Combine(layerRed, layerGreen, layerBlue);
    cout << "Combined layer_blue.tga, layer_green.tga, and layer_red.tga" << endl;
    writeFile("output/part9.tga", layerRed);
    cout << "Output: part9.tga" << endl;
    Image part9 = readFile("output/part9.tga");
    // Compare
    if(part9.Compare(example9)) {
        cout << "Test 9 Passed" << endl << endl;
    } else {
        cout << "Test 9 Failed" << endl << endl;
    }

// Test 10

    cout << "+=+=+=Test 10=+=+=+" << endl;
    Image temp10 = text2;
    Rotate(temp10, text2);
    cout << "Rotated text2.tga" << endl;
    writeFile("output/part10.tga", text2);
    cout << "Output: part10.tga" << endl;
    Image part10 = readFile("output/part10.tga");
    // Compare
    if(part10.Compare(example10)) {
        cout << "Test 10 Passed" << endl << endl;
    } else {
        cout << "Test 10 Failed" << endl << endl;
    }

// Test ExtraCredit

    cout << "+=+=+=Extra Credit=+=+=+" << endl;
    StitchHorizontal(carEC, circlesEC);
    cout << "Stitched car.tga and circles.tga" << endl;
    writeFile("output/ECTop.tga", carEC);
    cout << "Output: ECTop.tga" << endl;
    StitchHorizontal(textEC, pattern1EC);
    cout << "Stitched text.tga and pattern1.tga" << endl;
    writeFile("output/ECBottom.tga", textEC);
    cout << "Output: ECBottom.tga" << endl;
    StitchVertical(ECTop, ECBottom);
    cout << "Stitched ECTop.tga and ECBottom.tga" << endl;
    writeFile("output/extracredit.tga", ECTop);
    cout << "Output: extracredit.tga" << endl;
    Image extraCredit = readFile("output/extracredit.tga");
    // Compare
    if(extraCredit.Compare(exampleEC)) {
        cout << "Extra Credit Test Passed" << endl << endl;
    } else {
        cout << "Extra Credit Test Failed" << endl << endl;
    }

    return 0;
}
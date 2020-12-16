#include "AudioProcessor.h"
#include <iostream>

int main() {

    AudioProcessor processor;
    std::vector<short> audioSamples1{1, 2, 5, 6, 10, 0, -2, -5, -5, -8};
    std::vector<short> audioSamples2{ 1, 2, 5, 6, -4, 4, 10, 0, -2, -5, -4};
    std::vector<short> audioSamples3{ 1, 2, 5, 6, -4, 4, -2, -5, 10, 0, -4 };
    //std::vector<short> audioSamples3{1, 4, 23, -2, -28, 10};
    //std::vector<short> audioSamples4 {1, 3, -2, 5, -4, 0};
    //std::vector<short> audioSamples5 {-1, -30, 3, 15, 16, -7};
    //std::vector<short> compressedAudio;
    std::vector<short> silencedAudio;
    //std::vector<short> stretchedAudio;
    //std::vector<short> normalizedAudio;
    /*
    compressedAudio = processor.Compress(audioSamples1, 10, 1.5);
    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples1.size(); i++) {
       std::cout<<audioSamples1[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Compressed Format: ";
    for (int i = 0; i < compressedAudio.size(); i++) {
       std::cout<<compressedAudio[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    //compressedAudio = processor.Compress(audioSamples1, 10, 0.5);
    //compressedAudio = processor.Compress(audioSamples1, -8, 1.5);
    */

    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples1.size(); i++) {
       std::cout<<audioSamples1[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Silenced Format: ";
    silencedAudio = processor.CutOutSilence(audioSamples1, 5, 4);
    for (int i = 0; i < silencedAudio.size(); i++) {
       std::cout<<silencedAudio[i]<<" "; 
    }

    std::cout<<std::endl;
    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples2.size(); i++) {
       std::cout<<audioSamples2[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Silenced Format: ";
    silencedAudio = processor.CutOutSilence(audioSamples2, 5, 3);
    for (int i = 0; i < silencedAudio.size(); i++) {
       std::cout<<silencedAudio[i]<<" "; 
    }

    std::cout<<std::endl;
    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples3.size(); i++) {
       std::cout<<audioSamples3[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Silenced Format: ";
    silencedAudio = processor.CutOutSilence(audioSamples3, 5, 4);
    for (int i = 0; i < silencedAudio.size(); i++) {
       std::cout<<silencedAudio[i]<<" "; 
    }
    /*
    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples3.size(); i++) {
       std::cout<<audioSamples3[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Stretched Format: ";
    stretchedAudio = processor.StretchTwice(audioSamples3);
    for (int i = 0; i < stretchedAudio.size(); i++) {
       std::cout<<stretchedAudio[i]<<" "; 
    }

    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples4.size(); i++) {
       std::cout<<audioSamples4[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Normalized Format: ";
    normalizedAudio = processor.Normalize(audioSamples4, 10);
    for (int i = 0; i < normalizedAudio.size(); i++) {
       std::cout<<normalizedAudio[i]<<" "; 
    }

    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Original Format: ";
    for (int i = 0; i < audioSamples5.size(); i++) {
       std::cout<<audioSamples5[i]<<" "; 
    }
    std::cout<<std::endl;
    std::cout<<"Normalized Format: ";
    normalizedAudio = processor.Normalize(audioSamples5, 20);
    for (int i = 0; i < normalizedAudio.size(); i++) {
       std::cout<<normalizedAudio[i]<<" "; 
    }
    */
    return 0;
}

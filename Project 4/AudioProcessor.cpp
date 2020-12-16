#include "AudioProcessor.h"
#include <iostream>
#include <algorithm>
#include <cmath>

//Utility function for compressing. Pretty self-explanatory
short utilityCompression(short input, short threshold, float rate) {    

    bool negative = false;

    if (input < 0) {
        input *= -1;
        negative = true;
    }

    float inputFloat = float (input);
    float thresholdFloat = float (threshold);
    float result = round(((inputFloat - thresholdFloat)/rate) + thresholdFloat);

    if (negative == true) {
        result *= -1;
    }

    short shortResult = short (result);
    return shortResult;
}

//This function combines vectors. This is for the cut-out silence method
void combineVectors(std::vector<short>& vector1, std::vector<short>& vector2) {
    for (int i = 0; i < vector2.size(); i++) {
        vector1.push_back(vector2[i]);
    }
}

short calculateMean(short input1, short input2) {

    float floatInput1 = float (input1);
    float floatInput2 = float (input2);
    float result = round((floatInput1 + floatInput2)/2);
    short shortResult = short (result);
    return shortResult;
}

std::vector<short>AudioProcessor::Compress (const std::vector<short>& audio, short threshold, float rate) {

    if (audio.size() == 0) {
        return audio;
    }

    if (threshold < 0 || rate < 1.0) {
        throw std::invalid_argument("Invalid argument");
    }

    if (compressedAudio.size() > 0) {
        compressedAudio.clear();
    }

    for (int i = 0; i < audio.size(); i++) {
        if (abs(audio[i]) > threshold) {
            compressedAudio.push_back(utilityCompression(audio[i], threshold, rate));
        } else {
            compressedAudio.push_back(audio[i]);
        }
    }

    return compressedAudio;
}

std::vector<short>AudioProcessor::CutOutSilence (const std::vector<short>& audio, short level, int silenceLength) {

    if (audio.size() == 0) {
        return audio;
    }

    if (silenceLength < 1 || level < 0) {
        throw std::invalid_argument("Invalid argument");
    }

    if (silencedAudio.size() > 0) {
        silencedAudio.clear();
    }

    int silenceThreshold = 0;
    std::vector<short>tempVector;
    //This code seperates the values that are below threshold. If the silence length is reached, they are discarded from the temporary vector
    //If not, the temporary vector's contents are merged with the main vector.
    for (int i = 0; i < audio.size(); i++) {

        if (abs(audio[i]) <= level) {
            tempVector.push_back(audio[i]);
            silenceThreshold++;
        } else {
            if (silenceThreshold < silenceLength) {
                combineVectors(silencedAudio, tempVector);           
            }
            tempVector.clear();
            silenceThreshold = 0;
            silencedAudio.push_back(audio[i]); 
        }
        //std::cout<<"Silence threshold: "<<silenceThreshold<<", for value: "<<audio[i]<<std::endl;
    }

    if (silenceThreshold < silenceLength) {
        combineVectors(silencedAudio, tempVector);
    }

    return silencedAudio;
}


std::vector<short>AudioProcessor::StretchTwice(const std::vector<short>&audio) {

    if (audio.size() == 0) {
        return audio;
    }

    if (stretchedAudio.size() > 0) {
        stretchedAudio.clear();
    }
    
    int pointer1 = 0;
    int pointer2 = 1;
    short average;

    for (int i = 0; i < audio.size(); i++) {

        stretchedAudio.push_back(audio[i]);

        if (pointer2 < audio.size()) {
            average = calculateMean(audio[pointer1], audio[pointer2]);
            stretchedAudio.push_back(average);
        }
        pointer1++;
        pointer2++;
    }

    return stretchedAudio;
}


std::vector<short>AudioProcessor::Normalize(const std::vector<short>& audio, short normalizeTarget) {

    if (audio.size() == 0) {
        return audio;
    }

    if (normalizeTarget < 1) {
        throw std::invalid_argument("Invalid argument");
    }

    if (normalizedAudio.size() > 0) {
        normalizedAudio.clear();
    }

    std::vector<short>tempVector = audio;
    for (int i = 0; i < tempVector.size(); i++) {
        tempVector[i] = abs(tempVector[i]);
    }

    std::sort(tempVector.begin(), tempVector.end());
    if (tempVector.back() == 0) {
        return audio;
    }
    float multiplier = float(normalizeTarget)/float(tempVector.back());
    float result;

    for (int i = 0; i < audio.size(); i++) {
        result = round(float(audio[i])*multiplier);
        normalizedAudio.push_back(short(result));
    }

    return normalizedAudio;
}

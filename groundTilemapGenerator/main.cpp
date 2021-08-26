#include "main.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <bitset>


sf::Sprite baseLayer, corners[8], result[256], endResult;
sf::Texture TbaseLayer, tCorners[8];
sf::RenderTexture tResult[256], tEndResult;
bool tilePainted[256] = { false };

void loadAndSetTextures() {

    if (TbaseLayer.loadFromFile("textures/baseTexture/base.png")) {
        baseLayer.setTexture(TbaseLayer);
    }
    else {
       std::cout << "Error loading: textures/baseTexture/base.png" <<std::endl;
    }

    for (int i = 0; i < 8; i++) {
        std::stringstream filename;
        filename << "textures/corners/" << i << ".png";
        if (tCorners[i].loadFromFile(filename.str())) {
            corners[i].setTexture(tCorners[i]);
        }
    }

    for (int i = 0; i < 256; i++) {
        tResult[i].create(64, 128); //static for now could make it adjust to size of baseLayer
    }
}

void renderSingleTexture(std::bitset<8> bitcode, int textureId ) {

    tResult[textureId].draw(baseLayer);
    for (int i = 0; i < 8; i++) {
        if (bitcode[i] == 1) {
            tResult[textureId].draw(corners[i]);
        }
    }
    std::stringstream filename;
    filename << "output/" << textureId << ".png";
    tResult[textureId].getTexture().copyToImage().saveToFile(filename.str());
    tilePainted[textureId] = true;
}

bool advanceBitsetByOne(std::bitset<8>& currentSet) {
    std::bitset<8> tempSet(currentSet.to_ulong() + 1);
    if (tempSet.to_ulong() != 255) {
        currentSet = tempSet;
        return false;
    }
    else {
        currentSet = tempSet;
        return true;
    }
}

bool advanceBitset(std::bitset<8>& currentSet) {
    bool nextUnpaintedTileReached = false;
    bool endReached = false;
    while (!nextUnpaintedTileReached && !endReached) {
        endReached = advanceBitsetByOne(currentSet);
        nextUnpaintedTileReached = !tilePainted[currentSet.to_ulong()];
    }
    return !nextUnpaintedTileReached;
}

void renderAllPossibleTilesToTexture() {
    std::bitset<8> currentSet = { 0 };
    bool endReached = false;
    while (!endReached) {
        renderSingleTexture(currentSet, currentSet.to_ulong());
        endReached = advanceBitset(currentSet);
    }
}

void createEndResult() {
    tEndResult.create(16 * 64, 16 * 128); //The square root of 256 is 16 so we create a tileset of 16*16 tiles
    for (int spriteId = 0; spriteId < 256; spriteId++) {
        int x = spriteId;
        int y = 0;
        while (x >= 16) {
            x -= 16;
            y++;
        }
        x = x * 64;
        y = y * 128; 
        result[spriteId].setTexture(tResult[spriteId].getTexture());
        result[spriteId].setPosition(x, y);
        tEndResult.draw(result[spriteId]);
    }
    tEndResult.getTexture().copyToImage().saveToFile("output/tada.png");
    endResult.setTexture(tEndResult.getTexture());
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 2048), "SFML works!");
    loadAndSetTextures();
    renderAllPossibleTilesToTexture();
    createEndResult();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(endResult);
        window.display();
    }

    return 0;
}
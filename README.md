# groundTilemapGenerator
Generates tilemap based on base image and 8 border pieces.


The why
I planned on adding smoothed edges for my sand and water tiles for my isometric RTS game. So while doing some prototyping I concluded that for the complexity of the effect of an adjacent tile I would need 2^8 different tiles per category to cover all possible tile arrangement.

Since I only have limited time there was no way I would sit down and create all these assets myself. So I set out to write a little program that could do it for me. And the idea for groundTilemapGenerator was formed.

It will generate a 16*16 tilemap of a category of ground/water. By switching a specific border on and off. Each tile wil have a 8-bit number (0-256) and if I use the same code to generate the same 8bit bitmask ingame it will allow me to show the pixels of the exact same tile number. 


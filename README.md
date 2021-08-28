# groundTilemapGenerator
Generates tilemap based on base image and 8 border pieces.

## Why
I planned on adding smoothed edges for my sand and water tiles for my isometric RTS game. So while doing some prototyping I concluded that for the complexity of the effect of an adjacent tile I would need 2^8 different tiles per category to cover all possible tile arrangement.

Since I only have limited time there was no way I would sit down and create all these assets myself. So I set out to write a little program that could do it for me. And the idea for groundTilemapGenerator was formed.

## How
It will generate a 16*16 tilemap of a category of ground/water. By switching a specific border on and off. Each tile wil have a 8-bit number (0-256) and if I use the same code to generate the same 8bit bitmask ingame it will allow me to show the pixels of the exact same tile number. 

We have created the following square:
![Image of square](https://gamesdust.nl/uploads/0a6fec3b16aae39029f41159582d0d9d.png)
The numbers in the square represent to order at wich we check them to be another tile an need a border. 1 is true and 0 is false in our bitmask. Example grass in tile 0 but sand in all other tiles will result in bitmap: 00000001 and thus image number of 1 corresponding with the second image on the first row of the output file. (0 being the first one)
	
There are 48 possible tiles. (actually 2^8=256, but luckely most will look the same) We should take action when sand is bordering a grass tile
Water bordering land is handeld by the water tile to keep it simple


## Example output
![Image of Example output](https://gamesdust.nl/uploads/f9ab2f498c937f0759c2c013497e4051.png)


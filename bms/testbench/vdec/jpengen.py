#!/usr/bin/env python3
import argparse
from PIL import Image, ImageDraw
import random

def generate_random_color_image(width, height, filename, blocks, show):
    img = Image.new('RGB', (width, height))
    draw = ImageDraw.Draw(img)
    block_width = width // blocks
    block_height = height // blocks

    for x in range(0, width, block_width):
        for y in range(0, height, block_height):
            random_color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
            draw.rectangle([x, y, x+block_width, y+block_height], fill=random_color)

    img.save(filename)
    if show:
        img.show()

def main():
    parser = argparse.ArgumentParser(description="Generate a random color image.")
    parser.add_argument("-w", "--width", type=int, required=True, help="Width of the image")
    parser.add_argument("-e", "--height", type=int, required=True, help="Height of the image")
    parser.add_argument("-f", "--filename", type=str, default="output.jpeg", help="Filename to save the image")
    parser.add_argument("-b", "--blocks", type=int, default=16, help="Number of blocks per row and column")
    parser.add_argument("-s", "--show", action='store_true', help="Show generated image")
    
    args = parser.parse_args()
    
    generate_random_color_image(args.width, args.height, args.filename, args.blocks, args.show)
    print(f"Generated image saved as {args.filename}")

if __name__ == "__main__":
    main()


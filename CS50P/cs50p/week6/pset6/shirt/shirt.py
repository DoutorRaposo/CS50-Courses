import sys
import os
from PIL import Image, ImageOps


def main():
    if len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")

    if len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")

    input_ext = os.path.splitext(sys.argv[1])[-1].lower()
    output_ext = os.path.splitext(sys.argv[2])[-1].lower()

    supported_formats = (".jpeg", ".jpg", ".png")

    if output_ext not in supported_formats:
        sys.exit("Invalid output")

    if input_ext not in supported_formats:
        sys.exit("Invalid input")

    if input_ext != output_ext:
        sys.exit("Input and output have different extensions")

    if not os.path.isfile(sys.argv[1]):
        sys.exit("Input does not exist")

    shirt = Image.open("shirt.png")
    photo = Image.open(sys.argv[1])
    photo_resized = ImageOps.fit(photo, shirt.size)
    photo_resized.paste(shirt, shirt)
    photo_resized.save(sys.argv[2])

if __name__ == "__main__":
    main()

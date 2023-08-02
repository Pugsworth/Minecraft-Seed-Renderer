import numpy as np
from equilib import cube2equi
from PIL import Image

np.bool = bool

def resize_image(image, new_width, new_height):
    return image.resize((new_width, new_height), Image.LANCZOS)

def main():
    raw_images = [
        Image.open("panorama_0.png"),
        Image.open("panorama_1.png"),
        Image.open("panorama_2.png"),
        Image.open("panorama_3.png"),
        Image.open("panorama_4.png"),
        Image.open("panorama_5.png")
    ]

    images = tuple([resize_image(img, 1024, 1024) for img in raw_images])
    w = images[0].width
    h = images[0].height
    print(w, h)

    cubemaps = [np.transpose(np.asarray(img), (2, 0, 1)) for img in images]

    arr = cube2equi(cubemaps, "list", h, w*2)
    Image.fromarray(np.transpose(arr, (1, 2, 0))).save("equi.png")
    

if __name__ == '__main__':
    main()
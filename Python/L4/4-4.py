from PIL import Image
def signature():
    img = Image.open("signature.jpg").convert("RGB")
    width, height = img.size
    target_color = (211, 207, 198)
    tolerance = 50  # 颜色容差范围

    result_img = Image.new("RGB", (width, height))

    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))

            if (abs(r - target_color[0]) <= tolerance and
                    abs(g - target_color[1]) <= tolerance and
                    abs(b - target_color[2]) <= tolerance):
                result_img.putpixel((x, y), (255, 255, 255))
            else:
                result_img.putpixel((x, y), (0, 0, 0))

    resized_img = result_img.resize((300, 100), Image.LANCZOS)
    resized_img.save("sign.jpg")

if __name__ == "__main__":
    signature()
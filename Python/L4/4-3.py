from PIL import Image
def selfie():
    img = Image.open("2451317.jpg")

    width, height = img.size
    # print(f"原始图像信息: 宽度={width}, 高度={height}, 格式={img.format}, 模式={img.mode}")
    rgb_img = img.convert('RGB')
    half_height = height // 2
    lower_half = (0, half_height, width, height)
    crop_img = rgb_img.crop(lower_half)
    gray_crop = crop_img.convert('L')
    result_img = Image.new('RGB', (width, height))
    result_img.paste(rgb_img.crop((0, 0, width, half_height)), (0, 0))
    result_img.paste(gray_crop.convert('RGB'), (0, half_height))

    result_img.save("冯久恒.jpg", "JPEG")

    result_img = Image.open("冯久恒.jpg")
    print(f"宽度={result_img.width}\n高度={result_img.height}\n格式={result_img.format}\n模式={result_img.mode}")

if __name__ == "__main__":
    selfie()
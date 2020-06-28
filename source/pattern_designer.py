import cv2 as cv


image_width_in_frames = 4
image_height_in_frames = 16

## Read in image as BGR
image = cv.imread("animation_2.png", cv.IMREAD_COLOR)

frames = []

scanlines = ["11111110", "11111101", "11111011", "11110111", "11101111", "11011111", "10111111", "01111111"]

for w in range(image_height_in_frames):
    for h in range(image_width_in_frames):
        frame = (image[(w*8):((w*8)+8), (h*8):((h*8)+8)])

        frame_scanline_list = []
        for s, scan in enumerate(frame):
            output_scanline = ''
            for pixel in scan:
                if pixel[0] > 128:
                    B = '0'
                else:
                    B = '1'
                if pixel[1] > 128:
                    G = '0'
                else:
                    G = '1'
                if pixel[2] > 128:
                    R = '0'
                else:
                    R = '1'
                output_scanline += R+G+B
            output_scanline += scanlines[s]
            frame_scanline_list.append(hex(int(output_scanline, 2)))
        frames.append('{' + ','.join(frame_scanline_list) + '}')


print('{' + ',\n'.join(frames) + '}')

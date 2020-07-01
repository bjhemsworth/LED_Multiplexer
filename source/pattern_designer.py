import cv2 as cv


image_width_in_frames = 1
image_height_in_frames = 1

## Read in image as BGR
image = cv.imread("blue_colour_test.png", cv.IMREAD_COLOR)

frames = []

scanlines = ["11111110", "11111101", "11111011", "11110111", "11101111", "11011111", "10111111", "01111111"]

for w in range(image_height_in_frames):
    for h in range(image_width_in_frames):
        frame = (image[(w*8):((w*8)+8), (h*8):((h*8)+8)])

        frame_scanline_list_field1 = []
        frame_scanline_list_field2 = []
        for s, scan in enumerate(frame):

            output_scanline_field1 = ''
            output_scanline_field2 = ''

            for pixel in scan:
                if pixel[0] > 192:
                    B1 = '0'
                    B2 = '0'
                elif pixel[0] > 64:
                    B1 = '0'
                    B2 = '1'
                else:
                    B1 = '1'
                    B2 = '1'

                if pixel[1] > 192:
                    G1 = '0'
                    G2 = '0'
                elif pixel[1] > 64:
                    G1 = '0'
                    G2 = '1'
                else:
                    G1 = '1'
                    G2 = '1'

                if pixel[2] > 192:
                    R1 = '0'
                    R2 = '0'
                elif pixel[2] > 64:
                    R1 = '0'
                    R2 = '1'
                else:
                    R1 = '1'
                    R2 = '1'

                output_scanline_field1 += R1+G1+B1
                output_scanline_field2 += R2+G2+B2

            output_scanline_field1 += scanlines[s]
            output_scanline_field2 += scanlines[s]

            frame_scanline_list_field1.append(hex(int(output_scanline_field1, 2)))
            frame_scanline_list_field2.append(hex(int(output_scanline_field2, 2)))

        frames.append('{{' + ','.join(frame_scanline_list_field1) + '},{' + ','.join(frame_scanline_list_field2) + '}}')


print('{' + ',\n'.join(frames) + '}')

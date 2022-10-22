from PIL import Image

f = open("res/texture.raw", 'wb')
img = Image.open("res/uno.png")

colors = 0

for y in range(0, img.width):
	for x in range(0, img.height):
		d = img.getpixel((x, y))
		for c in img.getpixel((x, y)):
			f.write(c.to_bytes(1, 'little'))
			colors += 1

print("Wrote " + str(colors) + " colors")
f.close()
img.close()
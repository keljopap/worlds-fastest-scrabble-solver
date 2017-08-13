import Image
from tesseract import image_to_string

def main():
	print image_to_string(Image.open('olivia.JPG'))
	print image_to_string(Image.open('olivia.JPG'), lang='eng')

if __name__ == "__main__":
	main()

#!/usr/bin/python

'''
 (C) Benjamin Hugo, 
 February 2015
'''

import argparse
import numpy as np
from matplotlib import pyplot as plt

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="A small utility to plot RAW greyscale images")
	parser.add_argument("input_image_name", help="Name of the raw image file", type=str)
	parser.add_argument("width", help="Width of the image", type=int)
	parser.add_argument("height", help="Height of the image",type=int)
	parser_args = vars(parser.parse_args())	
	
	'''
	load up data (assumed 8 bit unsigned)
	'''
	my_img = np.fromfile(parser_args["input_image_name"],dtype=np.uint8) #this loads up unsigned chars (8 bit)
	if len(my_img) != parser_args["width"] * parser_args["height"]:
		raise argparse.ArgumentTypeError("Invalid width and height specified. Does not match amount of data read")
	my_img = my_img.reshape([parser_args["height"],parser_args["width"]])
	'''
	loading successful: let's go make a color map of the data... will be good enough as a viewer
	there is a bunch of color maps defined here: http://matplotlib.org/examples/color/colormaps_reference.html
	'''
	plt.figure()
	plt.imshow(my_img,cmap=plt.get_cmap("cubehelix"))
	plt.colorbar()
	plt.show()

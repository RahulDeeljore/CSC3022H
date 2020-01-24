#!/usr/bin/python

'''
 (C) Benjamin Hugo, 
 February 2015
'''

import argparse
import numpy as np
from matplotlib import pyplot as plt

if __name__ == "__main__":
	parser = argparse.ArgumentParser(description="A small utility to plot a diffmap between RAW greyscale images")
	parser.add_argument("input_image_name_1", help="Name of the raw image file", type=str)
	parser.add_argument("input_image_name_2", help="Name of the second raw image file", type=str)
	parser.add_argument("width", help="Width of the image", type=int)
	parser.add_argument("height", help="Height of the image",type=int)
	parser.add_argument("output_image", help="Name of output diffmap", type=str)
	parser_args = vars(parser.parse_args())	
	
	'''
	load up data (assumed 8 bit unsigned)
	'''
	my_img_1 = np.fromfile(parser_args["input_image_name_1"],dtype=np.uint8) #this loads up unsigned chars (8 bit)
	if len(my_img_1) != parser_args["width"] * parser_args["height"]:
		raise argparse.ArgumentTypeError("Invalid width and height specified. Does not match amount of data read from image 1")
	my_img_1 = my_img_1.reshape([parser_args["height"],parser_args["width"]])
	
	my_img_2 = np.fromfile(parser_args["input_image_name_2"],dtype=np.uint8) #this loads up unsigned chars (8 bit)
	if len(my_img_2) != parser_args["width"] * parser_args["height"]:
		raise argparse.ArgumentTypeError("Invalid width and height specified. Does not match amount of data read from image 2")
	my_img_2 = my_img_2.reshape([parser_args["height"],parser_args["width"]])

	diffmap = (np.abs(my_img_1.astype(np.float32) - my_img_2.astype(np.float32))/2).astype(np.uint8)
	diffmap.tofile(parser_args["output_image"])
	'''
	loading successful: let's go make a color map of the data... will be good enough as a viewer
	there is a bunch of color maps defined here: http://matplotlib.org/examples/color/colormaps_reference.html
	'''
	plt.figure()
	plt.title(parser_args["input_image_name_1"])
	plt.imshow(my_img_1,cmap=plt.get_cmap("cubehelix"))
	plt.colorbar()
	plt.figure()
	plt.title(parser_args["input_image_name_2"])
	plt.imshow(my_img_2,cmap=plt.get_cmap("cubehelix"))
	plt.colorbar()
	plt.figure()
	plt.title(parser_args["output_image"] + " --- abs(img1 - img2)")
	plt.imshow(diffmap,cmap=plt.get_cmap("cubehelix"))
	plt.colorbar()
	plt.show()


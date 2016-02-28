#!BPY

"""
Name: 'Rogi Model Export'
Blender: 243
Group: 'Export'
Tooltip: 'Rogi Model Exporter'
"""

import Blender
from Blender import *

from struct import *

def writemodel(filepath):

	out = file(filepath, 'wb')

	scene = Blender.Scene.GetCurrent()
	objects = scene.objects.selected

	if objects[0].getType() != 'Mesh':
		return -1
		
	model = objects[0].data

	out.write(pack('=I', len(model.materials)))
	print("%ld materials;" %(len(model.materials)))

	for material in model.materials:
		out.write(pack('=4f', material.R, material.G, material.B, material.alpha))
		out.write(pack('=4f', material.R, material.G, material.B, material.alpha))
		out.write(pack('=4f', material.specR, material.specG, material.specB, material.alpha))
		#out.write(pack('=4f', material.specR, material.specG, material.specB, material.alpha))
		out.write(pack('=1f', material.spec))
		out.write(pack('=4f', 0, 0, 0, 1))
		#out.write(pack('=4f', material.R, material.G, material.B, material.alpha))

	out.write(pack('=L', len(model.faces)))
	print("%ld polygons;" %(len(model.faces)))

	for face in model.faces:
		out.write(pack('=I', len(face.v)))

		for vert in face.v:
			out.write(pack('=3d', vert.co[0], vert.co[1], vert.co[2]))
			out.write(pack('=3d', vert.no[0], vert.no[1], vert.no[2]))

		out.write(pack('=3d', face.no[0], face.no[1], face.no[2]))

		out.write(pack('=I', face.mat))
#		out.write(pack('=L', 0))
#		out.write(pack('=L', face.image))
#		out.write(pack('=L', face.uv))
		out.write(pack('=6d', 0, 0, 0, 0, 0, 0))

	return 0

Blender.Window.FileSelector(writemodel, 'Export', 'model.r3m')

"""
Made for converting tiled maps with rectangles to points to be use in Tiled2GBA
"""

import os
from glob import glob
import xml.etree.ElementTree as ET
import shutil

OUTPUT_DIR = os.getcwd() + "/asset/build/map"

copiedDirs = []

def replacePoints():
    #get all .tmx files
    files = [y for x in os.walk(os.getcwd()) for y in glob(os.path.join(x[0], '*.tmx'))]

    for file in files:

        # Don't run on files already in build dir
        if (file.split("/")[-3] == "build"):
            continue


        #parse xml
        tree = ET.parse(file)
        root = tree.getroot()

        groups = root.findall("objectgroup")


        #update tilemaps
        filename = file.split("/")[-1]

        fileDir = file.split(filename)[0]

        #get tsx from tmx
        tilesets = root.findall("tileset")

        for tileset in tilesets:
            source = tileset.get("source")

            dir = fileDir + source

            tileset.set("source", dir)

            
        #output
        print(OUTPUT_DIR + "/" + file.split("/")[-1])

    

        for group in groups:
            objects = group.findall("object")

            for object in objects:

                #check if rectangle
                if (
                    object.get("x") and 
                    object.get("y") and 
                    object.get("width") and 
                    object.get("height") and 
                    object.find("ellipse") == None #No elipse tag within so must be rect
                ):
                    print("Found rect with ID:", object.get("id"))
                    point1 = ET.Element("object")
                    point2 = ET.Element("object")

                    point1.set("x", object.get("x"))
                    point1.set("y", object.get("y"))

                    point2.set("x", str(float(object.get("x")) + float(object.get("width"))))
                    point2.set("y", str(float(object.get("y")) + float(object.get("height"))))

                    group.append(point1)
                    group.append(point2)

                    group.remove(object)


    

        #write to build folder
        tree.write(OUTPUT_DIR + "/" + file.split("/")[-1])
                    
                    
                    

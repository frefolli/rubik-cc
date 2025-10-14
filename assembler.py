from __future__ import annotations
import os
import json
from PIL import Image
import numpy

Size=tuple[int, int]
Box=tuple[int, int, int, int]
Boxes=dict[str, Box]

def read_json(path: str) -> dict:
 with open(path, 'r') as file:
   return json.load(file)

class Template:
  def __init__(self, size: Size, boxes: Boxes, objx: str, mtlx: str) -> None:
    self.size = size
    self.boxes = boxes
    self.objx = objx
    self.mtlx = mtlx

  def start(self) -> Sketch:
    return Sketch(self)

  @staticmethod
  def load(size: Size, boxes: Boxes, id: str) -> Template:
    objx_path = os.path.join('./templates', '%s.objx' % id)
    mtlx_path = os.path.join('./templates', '%s.mtlx' % id)
    objx = ""
    mtlx = ""
    with open(objx_path) as objx_file:
      objx = objx_file.read()
    with open(mtlx_path) as mtlx_file:
      mtlx = mtlx_file.read()
    return Template(size, boxes, objx, mtlx)

class Sketch:
  def __init__(self, template: Template) -> None:
    self.template = template
    self.image = Image.new(mode='RGBA', size=self.template.size, color=(0,0,0,0))

  def cover_with_tile(self, tile: Image.Image) -> Sketch:
    for _, box in self.template.boxes.items():
      size = (box[2] - box[0], box[3] - box[1])
      frame = tile.resize(size)
      self.image.paste(frame, box[:2])
    return self

  def apply_tiles(self, tiles: dict[str, Image.Image]) -> Sketch:
    for key, tile in tiles.items():
      box = self.template.boxes[key]
      size = (box[2] - box[0], box[3] - box[1])
      frame = tile.resize(size)
      self.image.paste(frame, box[:2], frame)
    return self

  def apply_colors(self, colors: dict[str, tuple[int, int, int, int]]) -> Sketch:
    for key, color in colors.items():
      box = self.template.boxes[key]
      size = (box[2] - box[0], box[3] - box[1])
      frame = Image.new(mode='RGBA', size=size, color=color)
      self.image.paste(frame, box[:2])
    return self

  def save(self, id: str):
    obj_path = os.path.join('./assets', '%s.obj' % id)
    mtl_path = os.path.join('./assets', '%s.mtl' % id)
    png_path = os.path.join('./assets', '%s.png' % id)
    obj = self.template.objx.replace('{{MTL_PATH}}', os.path.basename(mtl_path))
    mtl = self.template.mtlx.replace('{{PNG_PATH}}', os.path.basename(png_path))
    with open(obj_path, 'w') as obj_file:
      obj_file.write(obj)
    with open(mtl_path, 'w') as mtl_file:
      mtl_file.write(mtl)
    self.image.save(png_path)

"""
  U
L N R
  D
  S
"""

"""
  E
S D N
  W
  U
"""

# template = Template((320, 320), {
#   'south': (0, 80, 80, 160),
#   'down':  (80, 80, 160, 160),
#   'north': (160, 80, 240, 160),
#   'east':  (80, 0, 160, 80),
#   'west':  (80, 160, 160, 240),
#   'up':    (80, 240, 160, 320)
# })

RED=(255, 0, 0, 255)
GREEN=(0, 255, 0, 255)
BLUE=(0, 0, 255, 255)
WHITE=(255, 255, 255, 255)
BLACK=(0, 0, 0, 255)
YELLOW=(255, 255, 0, 255)
ORANGE=(255, 110, 0, 255)

template = Template.load((64, 64), {
  'south': (0, 16, 16, 32),
  'down':  (16, 16, 32, 32),
  'north': (32, 16, 48, 32),
  'east':  (16, 0, 32, 16),
  'west':  (16, 32, 32, 48),
  'up':    (16, 48, 32, 64)
}, 'cube')

base: Boxes = {
  'south': BLACK,
  'down':  BLACK,
  'north': BLACK,
  'east':  BLACK,
  'west':  BLACK,
  'up':    BLACK
}

entries = [
    {'south': RED, 'west': GREEN, 'up': WHITE},
    {'south': RED, 'up': WHITE},
    {'south': RED, 'east': BLUE, 'up': WHITE},
    {'west': GREEN, 'up': WHITE},
    {'up': WHITE},
    {'east': BLUE, 'up': WHITE},
    {'north': ORANGE, 'west': GREEN, 'up': WHITE},
    {'north': ORANGE, 'up': WHITE},
    {'north': ORANGE, 'east': BLUE, 'up': WHITE},

    {'south': RED, 'west': GREEN},
    {'south': RED},
    {'south': RED, 'east': BLUE},
    {'west': GREEN},
    {},
    {'east': BLUE},
    {'north': ORANGE, 'west': GREEN},
    {'north': ORANGE},
    {'north': ORANGE, 'east': BLUE},

    {'south': RED, 'west': GREEN, 'down': YELLOW},
    {'south': RED, 'down': YELLOW},
    {'south': RED, 'east': BLUE, 'down': YELLOW},
    {'west': GREEN, 'down': YELLOW},
    {'down': YELLOW},
    {'east': BLUE, 'down': YELLOW},
    {'north': ORANGE, 'west': GREEN, 'down': YELLOW},
    {'north': ORANGE, 'down': YELLOW},
    {'north': ORANGE, 'east': BLUE, 'down': YELLOW},
]

for idx, entry in enumerate(entries):
  colors = {}
  sketch = template.start().apply_colors(base).apply_colors(entry).save(str(idx))

#  sketch = template.start().apply_colors({
#    'south': RED,
#    'down':  YELLOW,
#    'north': ORANGE,
#    'east':  BLUE,
#    'west':  GREEN,
#    'up':    BLACK
#  })
